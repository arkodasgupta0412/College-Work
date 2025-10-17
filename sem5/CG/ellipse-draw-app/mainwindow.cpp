#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gridscene.h"
#include "gridview.h"

#include <QElapsedTimer>
#include <QtMath>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QIntValidator>
#include <QDebug>

static QBrush kPolarBrush = QBrush(QColor(220, 20, 60));
static QBrush kMidBrush = QBrush(QColor(0, 90, 255));

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget *central = new QWidget(this);
    auto *mainLayout = new QVBoxLayout(central);

    scene = new GridScene(this);
    view  = new GridView(this);
    view->setScene(scene);
    scene->setSceneRect(-500, -500, 1000, 1000);

    // Create input row for ellipse axes
    auto *inputRow = new QHBoxLayout;
    auto *aLabel = new QLabel("Semi-Major Axis (a):");
    aInput = new QLineEdit();
    aInput->setValidator(new QIntValidator(1, 1000, this));
    aInput->setPlaceholderText("Enter a");
    aInput->setMaximumWidth(100);

    auto *bLabel = new QLabel("Semi-Minor Axis (b):");
    bInput = new QLineEdit();
    bInput->setValidator(new QIntValidator(1, 1000, this));
    bInput->setPlaceholderText("Enter b");
    bInput->setMaximumWidth(100);

    inputRow->addWidget(aLabel);
    inputRow->addWidget(aInput);
    inputRow->addWidget(bLabel);
    inputRow->addWidget(bInput);
    inputRow->addStretch();

    // Create button row
    auto *btnRow = new QHBoxLayout;
    auto *btnPolar = new QPushButton("Draw Ellipse (Polar)");
    auto *btnMid   = new QPushButton("Draw Ellipse (Midpoint)");
    auto *btnClear = new QPushButton("Clear");
    auto *btnPerf  = new QPushButton("Compare Times");

    btnRow->addWidget(btnPolar);
    btnRow->addWidget(btnMid);
    btnRow->addWidget(btnPerf);
    btnRow->addStretch();
    btnRow->addWidget(btnClear);

    mainLayout->addLayout(inputRow);
    mainLayout->addWidget(view);
    mainLayout->addLayout(btnRow);
    setCentralWidget(central);

    // wire signals
    connect(scene, &GridScene::cellClicked, this, &MainWindow::onCellClicked);
    connect(aInput, &QLineEdit::textChanged, this, &MainWindow::onAxesChanged);
    connect(bInput, &QLineEdit::textChanged, this, &MainWindow::onAxesChanged);
    connect(btnPolar, &QPushButton::clicked, this, &MainWindow::drawEllipsePolar);
    connect(btnMid, &QPushButton::clicked, this, &MainWindow::drawEllipseMidpoint);
    connect(btnPerf, &QPushButton::clicked, this, &MainWindow::compareExecutionTimes);
    connect(btnClear, &QPushButton::clicked, scene, &GridScene::clearCells);

    // animation timer
    animTimer.setSingleShot(false);
    connect(&animTimer, &QTimer::timeout, this, &MainWindow::stepAnimation);

    setStatus("Click to select center point, then enter axes lengths and click draw.");
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::setStatus(const QString& s) { statusBar()->showMessage(s, 5000); }

void MainWindow::onCellClicked(const QPoint& cell) {
    centerCell = cell;
    haveCenter = true;
    scene->clearCells();
    scene->paintCell(centerCell, QBrush(Qt::blue));
    setStatus(QString("Center set at (%1,%2). Enter axes lengths and click draw.").arg(cell.x()).arg(cell.y()));
}

void MainWindow::onAxesChanged() {
    QString aText = aInput->text();
    QString bText = bInput->text();
    if (!aText.isEmpty() && !bText.isEmpty()) {
        int a = aText.toInt();
        int b = bText.toInt();
        setStatus(QString("Axes: a=%1, b=%2. Click draw button to render ellipse.").arg(a).arg(b));
    }
}

int MainWindow::currentA() const {
    QString text = aInput->text();
    if (text.isEmpty()) {
        return 20; // Default semi-major axis
    }
    return text.toInt();
}

int MainWindow::currentB() const {
    QString text = bInput->text();
    if (text.isEmpty()) {
        return 10; // Default semi-minor axis
    }
    return text.toInt();
}

// ------------- Four-way symmetry for ellipse -------------
QVector<QPoint> MainWindow::fourSymmetry(const QPoint& c, int x, int y) {
    return {
        {c.x() + x, c.y() + y},
        {c.x() - x, c.y() + y},
        {c.x() + x, c.y() - y},
        {c.x() - x, c.y() - y}
    };
}

// ------------- Build frames: POLAR ellipse -------------
QVector<QPoint> MainWindow::buildPolarFrames(const QPoint& c, int a, int b) {
    QVector<QPoint> frames;

    // Step through angles from 0 to 2π
    double dtheta = 1.0 / (a + b); // Adjust step size based on larger axis
    for (double theta = 0.0; theta <= M_PI / 2.0 + 1e-9; theta += dtheta) {
        int x = (int)qRound(a * qCos(theta));
        int y = (int)qRound(b * qSin(theta));
        auto sym = fourSymmetry(c, x, y);
        frames += sym;
    }
    qDebug() << "Number of pixels coloured (Polar Method): " << frames.size() << "\n";

    return frames;
}

// ------------- Build frames: Midpoint Ellipse Algorithm -------------
QVector<QPoint> MainWindow::buildMidpointFrames(const QPoint& c, int a, int b) {
    QVector<QPoint> frames;
    int x = 0;
    int y = b;

    // Region 1 parameters
    double d1 = b*b - a*a*b + 0.25*a*a;
    int a2 = a*a;
    int b2 = b*b;

    // Region 1: Slope > -1
    while ((2 * b2 * x) <= (2 * a2 * y)) {
        auto sym = fourSymmetry(c, x, y);
        frames += sym;

        if (d1 < 0) {
            // Move to E
            d1 += b2*(2*x + 3);
        } else {
            // Move to SE
            d1 += b2*(2*x + 3) + a2*(-2*y + 2);
            y--;
        }
        x++;
    }

    // Region 2 parameters
    double d2 = b2*(x + 0.5)*(x + 0.5) + a2*(y - 1)*(y - 1) - a2*b2;

    // Region 2: Slope <= -1
    while (y >= 0) {
        auto sym = fourSymmetry(c, x, y);
        frames += sym;

        if (d2 < 0) {
            // Move to SE
            d2 += b2*(2*x + 2) + a2*(-2*y + 3);
            x++;
        } else {
            // Move to S
            d2 += a2*(-2*y + 3);
        }
        y--;
    }

    qDebug() << "Number of pixels coloured (Midpoint Method): " << frames.size() << "\n";
    return frames;
}

// ------------- Animation harness -------------
void MainWindow::beginAnimation(const QVector<QPoint>& frames, const QBrush& brush, int msStep) {
    if (!haveCenter) {
        setStatus("Please select a center point first!");
        return;
    }

    QString aText = aInput->text();
    QString bText = bInput->text();
    if (aText.isEmpty() || bText.isEmpty()) {
        setStatus("Please enter both axis values!");
        return;
    }

    animTimer.stop();
    animFrames = frames;
    animIndex  = 0;
    animBrush  = brush;

    scene->paintCell(centerCell, QBrush(Qt::blue));

    if (!animFrames.isEmpty()) {
        animTimer.start(msStep);
    }
}

void MainWindow::stepAnimation() {
    if (animIndex >= animFrames.size()) {
        animTimer.stop();
        return;
    }
    scene->paintCell(animFrames[animIndex++], animBrush);
}

// ------------- Draw buttons -------------
void MainWindow::drawEllipsePolar() {
    int a = currentA();
    int b = currentB();
    auto frames = buildPolarFrames(centerCell, a, b);
    beginAnimation(frames, kPolarBrush, 10);
}

void MainWindow::drawEllipseMidpoint() {
    int a = currentA();
    int b = currentB();
    auto frames = buildMidpointFrames(centerCell, a, b);
    beginAnimation(frames, kMidBrush, 5);
}

// ------------- Timing comparison -------------
void MainWindow::compareExecutionTimes() {
    if (!haveCenter) {
        setStatus("Please select a center point first!");
        return;
    }

    QString aText = aInput->text();
    QString bText = bInput->text();
    if (aText.isEmpty() || bText.isEmpty()) {
        setStatus("Please enter both axis values!");
        return;
    }

    int a = currentA();
    int b = currentB();
    const int iters = 200;

    QElapsedTimer t;
    qint64 tp = 0, tm = 0;

    t.start();
    for (int i=0;i<iters;++i) volatile auto v = buildPolarFrames(centerCell, a, b);
    tp = t.nsecsElapsed();

    t.restart();
    for (int i=0;i<iters;++i) volatile auto v = buildMidpointFrames(centerCell, a, b);
    tm = t.nsecsElapsed();

    setStatus(QString("Avg per iteration (ns): Polar %1 | Midpoint %2").arg(tp/iters).arg(tm/iters));
}
