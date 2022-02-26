#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GraphicsPlotItem.h"
#include <QGraphicsView>
#include <QMainWindow>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QWidget>
QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MyWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);

    void lineSegment();
    // QGLWidget interface

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
};

class MyView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit MyView(QWidget *parent = 0);

    void minAixMove(int dx);
    void maxAixMove(int dx);

public:
    QGraphicsScene *m_scene{nullptr};

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;

private:
    QPointF transformPoint(QPointF input);

public:
    QGraphicsItem *m_aix_min{nullptr}, *m_aix_max{nullptr};

private:
    QWidget *m_parent_widget{nullptr};
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void show2DHistogram();
    void show2DPolyItem();
    void showOpenglWidget();

    void resetMinMaxLine(QPoint point);

    QPointF transformPoint(QPointF input);

    void setMinInEdit(int value);
    void setMaxInEdit(int value);

    void setData();

private:
    void setCoordinateRange(double min, double max);
    void setAbsScissRange(double min, double max);
    void setMinAixX();
    void setMaxAixX();

public:
    double m_cord_ratio, m_abss_ratio;

private:
    MyView *m_view{nullptr};
    GraphicsPlotItem *m_plot{nullptr};
    Graphics2DGraphItem *m_data_item{nullptr};
    int m_min_x, m_max_x;
    struct Range
    {
        Range() {}
        Range(double min, double max) : min(min), max(max) {}
        double min, max;
    };
    Range m_cord_range, m_abss_range;
    Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
