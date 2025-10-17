#pragma once
#include <QMainWindow>
#include <QPoint>
#include <QVector>
#include <QTimer>
#include <QLineEdit>

class GridScene;
class GridView;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onCellClicked(const QPoint& cell);
    void onAxesChanged(); // New slot for axis input changes
    // draw
    void drawEllipsePolar();
    void drawEllipseMidpoint();
    void compareExecutionTimes();
    void stepAnimation();

private:
    // helpers
    int  currentA() const;
    int  currentB() const;
    void setStatus(const QString& s);
    void beginAnimation(const QVector<QPoint>& frames, const QBrush& brush, int msStep);
    static QVector<QPoint> fourSymmetry(const QPoint& c, int x, int y);
    // ellipse point sequences
    QVector<QPoint> buildPolarFrames(const QPoint& c, int a, int b);
    QVector<QPoint> buildMidpointFrames(const QPoint& c, int a, int b);

private:
    Ui::MainWindow *ui;

    GridScene* scene = nullptr;
    GridView*  view  = nullptr;

    // radius input
    QLineEdit* aInput = nullptr; // semi-major axis
    QLineEdit* bInput = nullptr; // semi-minor axis

    // click state: only center point needed
    bool   haveCenter = false;
    QPoint centerCell;

    // animation state
    QTimer animTimer;
    QVector<QPoint> animFrames;
    int animIndex = 0;
    QBrush animBrush = Qt::blue;
};
