#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void show2DHistogram();
    void show2DPolyItem();
    void showOpenglWidget();

private:
    Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
