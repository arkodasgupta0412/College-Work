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

static QBrush kPolarBrush = QBrush(QColor(220, 20, 60));
static QBrush kMidBrush = QBrush(QColor(0, 90, 255));
static QBrush kOverlapBrush = QBrush(QColor(180, 0, 180));

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

    // Create input row
    auto *inputRow = new QHBoxLayout;
    auto *radiusLabel = new QLabel("Radius:");
    radiusInput = new QLineEdit();
    radiusInput->setValidator(new QIntValidator(1, 1000, this));
    radiusInput->setPlaceholderText("Enter radius");
    radiusInput->setMaximumWidth(100);

    inputRow->addWidget(radiusLabel);
    inputRow->addWidget(radiusInput);
    inputRow->addStretch();

    // Create button row
    auto *btnRow = new QHBoxLayout;
    auto *btnPolar = new QPushButton("Draw Circle (Polar)");
    auto *btnMid   = new QPushButton("Draw Circle (Midpoint)");
    auto *btnCart  = new QPushButton("Draw Circle (Cartesian)");
    auto *btnClear = new QPushButton("Clear");
    auto *btnPerf  = new QPushButton("Compare Times");

    btnRow->addWidget(btnPolar);
    btnRow->addWidget(btnMid);
    btnRow->addWidget(btnCart);
    btnRow->addWidget(btnPerf);
    btnRow->addStretch();
    btnRow->addWidget(btnClear);

    mainLayout->addLayout(inputRow);    // Add input row first
    mainLayout->addWidget(view);
    mainLayout->addLayout(btnRow);
    setCentralWidget(central);

    // wire signals
    connect(scene, &GridScene::cellClicked, this, &MainWindow::onCellClicked);
    connect(radiusInput, &QLineEdit::textChanged, this, &MainWindow::onRadiusChanged);
    connect(btnPolar, &QPushButton::clicked, this, &MainWindow::drawCirclePolar);
    connect(btnMid, &QPushButton::clicked, this, &MainWindow::drawCircleMidpoint);
    connect(btnCart, &QPushButton::clicked, this, &MainWindow::drawCircleCartesian);
    connect(btnPerf, &QPushButton::clicked, this, &MainWindow::compareExecutionTimes);
    connect(btnClear, &QPushButton::clicked, scene, &GridScene::clearCells);

    // animation timer
    animTimer.setSingleShot(false);
    connect(&animTimer, &QTimer::timeout, this, &MainWindow::stepAnimation);

    setStatus("Click to select center point, then enter radius and click draw.");
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::setStatus(const QString& s) { statusBar()->showMessage(s, 5000); }

void MainWindow::onCellClicked(const QPoint& cell) {
    centerCell = cell;
    haveCenter = true;
    scene->clearCells();
    scene->paintCell(centerCell, QBrush(Qt::blue));
    setStatus(QString("Center set at (%1,%2). Enter radius and click draw.").arg(cell.x()).arg(cell.y()));
}

void MainWindow::onRadiusChanged() {
    // Optional: You can add real-time validation or preview here
    QString text = radiusInput->text();
    if (!text.isEmpty()) {
        int radius = text.toInt();
        setStatus(QString("Radius: %1. Click draw button to render circle.").arg(radius));
    }
}

int MainWindow::currentRadius() const {
    QString text = radiusInput->text();
    if (text.isEmpty()) {
        return 10;
    }
    return text.toInt();
}

// ------------- Eight-way symmetry -------------
QVector<QPoint> MainWindow::eightSymmetry(const QPoint& c, int x, int y) {
    return {
        {c.x() + x, c.y() + y},
        {c.x() - x, c.y() + y},
        {c.x() + x, c.y() - y},
        {c.x() - x, c.y() - y},
        {c.x() + y, c.y() + x},
        {c.x() - y, c.y() + x},
        {c.x() + y, c.y() - x},
        {c.x() - y, c.y() - x}
    };
}

// ------------- Build frames: POLAR (θ stepping in first octant) -------------
QVector<QPoint> MainWindow::buildPolarFrames(const QPoint& c, int r) {
    QVector<QPoint> frames;
    // step angle so adjacent pixels change ~1 cell
    double dtheta = 1.0 / qMax(1, r);
    for (double theta = 0.0; theta <= M_PI/4.0 + 1e-9; theta += dtheta) {
        int x = (int)qRound(r * qCos(theta));
        int y = (int)qRound(r * qSin(theta));
        auto oct = eightSymmetry(c, x, y);
        frames += oct;
    }
    return frames;
}

// ------------- Build frames: Midpoint/Bresenham -------------
QVector<QPoint> MainWindow::buildMidpointFrames(const QPoint& c, int r) {
    QVector<QPoint> frames;
    int x = 0;
    int y = r;
    int p = 1 - r;

    while (x <= y) {
        // Plot all eight symmetric points
        auto oct = eightSymmetry(c, x, y);
        frames += oct;

        x++;

        if (p < 0) {
            p = p + 2 * x + 1;
        } else {
            y--;
            p = p + 2 * (x - y) + 1;
        }
    }
    return frames;
}

// ------------- Optional: Cartesian (x from 0..r) -------------
QVector<QPoint> MainWindow::buildCartesianFrames(const QPoint& c, int r) {
    QVector<QPoint> frames;
    for (int x = 0; x <= r; ++x) {
        int y = (int)qRound(qSqrt(double(r*r - x*x)));
        auto oct = eightSymmetry(c, x, y);
        frames += oct;
    }
    return frames;
}

// ------------- Animation harness -------------
void MainWindow::beginAnimation(const QVector<QPoint>& frames, const QBrush& brush, int msStep) {
    if (!haveCenter) {
        setStatus("Please select a center point first!");
        return;
    }

    QString radiusText = radiusInput->text();
    if (radiusText.isEmpty()) {
        setStatus("Please enter a radius value!");
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
void MainWindow::drawCirclePolar() {
    int r = currentRadius();
    auto frames = buildPolarFrames(centerCell, r);
    qDebug() << "Number of pixels coloured (Polar Method):" << frames.size();
    beginAnimation(frames, kPolarBrush, 15);
}

void MainWindow::drawCircleMidpoint() {
    int r = currentRadius();
    auto frames = buildMidpointFrames(centerCell, r);
    qDebug() << "Number of pixels coloured (Midpoint Method):" << frames.size();
    beginAnimation(frames, kMidBrush, 10);
}

void MainWindow::drawCircleCartesian() {
    int r = currentRadius();
    auto frames = buildCartesianFrames(centerCell, r);
    qDebug() << "Number of pixels coloured (Cartesian Method):" << frames.size();
    beginAnimation(frames, QBrush(QColor(10, 160, 10)), 12);
}


// ------------- Optional: timing compare (computation only) -------------
void MainWindow::compareExecutionTimes() {
    if (!haveCenter) {
        setStatus("Please select a center point first!");
        return;
    }

    QString radiusText = radiusInput->text();
    if (radiusText.isEmpty()) {
        setStatus("Please enter a radius value!");
        return;
    }

    int r = currentRadius();
    const int iters = 200;

    QElapsedTimer t;
    qint64 tp = 0, tm = 0, tc = 0;

    t.start();
    for (int i=0;i<iters;++i) volatile auto v = buildPolarFrames(centerCell, r);
    tp = t.nsecsElapsed();

    t.restart();
    for (int i=0;i<iters;++i) volatile auto v = buildMidpointFrames(centerCell, r);
    tm = t.nsecsElapsed();

    t.restart();
    for (int i=0;i<iters;++i) volatile auto v = buildCartesianFrames(centerCell, r);
    tc = t.nsecsElapsed();

    setStatus(QString("Avg per iteration (ns): Polar %1 | Midpoint %2 | Cartesian %3").arg(tp/iters).arg(tm/iters).arg(tc/iters));
}
