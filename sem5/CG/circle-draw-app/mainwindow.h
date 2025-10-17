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
    void onRadiusChanged(); // New slot for radius input
    // draw
    void drawCirclePolar();
    void drawCircleMidpoint();
    void drawCircleCartesian();
    void compareExecutionTimes();
    void stepAnimation();

private:
    // helpers
    int  currentRadius() const;
    void setStatus(const QString& s);
    void beginAnimation(const QVector<QPoint>& frames, const QBrush& brush, int msStep);
    static QVector<QPoint> eightSymmetry(const QPoint& c, int x, int y);
    // circle point sequences (first-octant stepping, each expanded to 8)
    QVector<QPoint> buildPolarFrames(const QPoint& c, int r);
    QVector<QPoint> buildMidpointFrames(const QPoint& c, int r);
    QVector<QPoint> buildCartesianFrames(const QPoint& c, int r);

private:
    Ui::MainWindow *ui;

    GridScene* scene = nullptr;
    GridView*  view  = nullptr;

    // radius input
    QLineEdit* radiusInput = nullptr;

    // click state: only center point needed
    bool   haveCenter = false;
    QPoint centerCell;

    // animation state
    QTimer animTimer;
    QVector<QPoint> animFrames;
    int animIndex = 0;
    QBrush animBrush = Qt::blue;
};
