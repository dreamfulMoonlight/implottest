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

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

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

private:
    MyView *m_view{nullptr};
    GraphicsPlotItem *m_plot{nullptr};
    Graphics2DGraphItem *m_data_item{nullptr};
    Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
