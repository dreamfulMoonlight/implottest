#include "openglcontainer.hpp"
#include <GL/glu.h>
#include <GL/glut.h>
#include <QMouseEvent>
#include <QString>
#include <iostream>

// Help methods and data structures
static void normalizeAngle(double &angle)
{
    while (angle < 0.)
        angle += 360. * 16;
    while (angle > 360.)
        angle -= 360. * 16;
}

struct point
{
    GLfloat x;
    GLfloat y;
};

OpenGLContainer::OpenGLContainer(QWidget *parent) : QOpenGLWidget(parent)
{
    viewMode = 0;
    xRot = 0.;
    yRot = 0.;
    zRot = 0.;
    xTrans = 0.;
    yTrans = 0.;
    zZoom = -2.;
    toggleTranslation = false;
}

void OpenGLContainer::initializeGL()
{
    initializeOpenGLFunctions();  // It is very important that initializeGLFunctions() is at this location in the code
    setGeometry(0, 0, 640, 480);  //设置窗口初始位置和大小
    glClearColor(1.0, 1.0, 1.0, 0);  //改变窗口的背景颜色，不过我这里貌似设置后并没有什么效果
    gluOrtho2D(0.0, 600.0, 0.0, 500.0);
}

void OpenGLContainer::paintGL()
{
    GLint dataValue[12] = {452, 368, 214, 543, 328, 193, 322, 436, 257, 268, 473, 467};

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glLineWidth(4);
    glVertex2i(20, 20);  // y轴
    glVertex2i(20, 600);

    //    glVertex2i(15, 15);  // 100
    //    glVertex2i(30, 30);

    //    glVertex2i(30, 30);  // 200
    //    glVertex2i(45, 50);

    //    glVertex2i(45, 50);  // 300
    //    glVertex2i(55, 350);

    glVertex2i(20, 20);  // x轴
    glVertex2i(630, 20);

    glEnd();
    //    glPointSize(4.5);
    //    glColor3f(0.0, 0.0, 0.0);
    //    glBegin(GL_POINTS);

    //    for (int k = 0; k < 6; k++)
    //    {
    //        glVertex2i(120 + k * 70, dataValue[k]);
    //    }
    //    glEnd();

    glColor3f(0, 0, 1);
    glLineWidth(2);
    //绘制折线图
    glBegin(GL_LINE_STRIP);
    {
        for (int i = 0; i < 12; i++)
        {
            glVertex2i(i * 30 + 20, dataValue[i] / 20 + 20);
        }
    }
    glEnd();

    //    //polygon
    //    for (int k = 0; k < 6; k++)
    //    {
    //        glColor3f(0.0, 0.3, 0.7);
    //        glBegin(GL_POLYGON);

    //        glVertex2i(110 + k * 70, 50);
    //        glVertex2i(130 + k * 70, 50);
    //        glVertex2i(130 + k * 70, dataValue[k] - 40);
    //        glVertex2i(110 + k * 70, dataValue[k] - 40);

    //        glEnd();
    //    }

    glFlush();
}

void OpenGLContainer::resizeGL(int w, int h)
{
    //    glViewport(0, 0, w, h);
    //    glMatrixMode(GL_PROJECTION);
    //    glLoadIdentity();
    //    gluPerspective(45, (float)w / h, .01, 100.);
    //    glMatrixMode(GL_MODELVIEW);
    //    glLoadIdentity();
    //    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
}

void OpenGLContainer::changeViewMode(int mode)
{
    viewMode = mode;
    switch (mode)
    {
        case 0:
            glDisable(GL_CULL_FACE);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            std::cout << "View mode set to solid" << std::endl;
            break;
        case 1:
            glEnable(GL_CULL_FACE);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            std::cout << "View mode set to wireframe (with back culling)" << std::endl;
            break;
        case 2:
            glDisable(GL_CULL_FACE);
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            std::cout << "View mode set to dots" << std::endl;
    }
    update();
}

void OpenGLContainer::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();

    if (event->buttons() & Qt::MiddleButton)
        toggleTranslation = true;
    else
        toggleTranslation = false;
}

void OpenGLContainer::mouseMoveEvent(QMouseEvent *event)
{
    // Size of dx and dy represent the speed of movement along the respective axis
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton)
    {
        setXRotation(xRot + 8. * dy);
        setYRotation(yRot + 8. * dx);
    }
    else if (event->buttons() & Qt::RightButton)
    {
        setXRotation(xRot + 8. * dy);
        setZRotation(zRot + 8. * dx);
    }

    lastPos = event->pos();

    // Translate camera horizontally and vertically
    if (toggleTranslation)
        setXYTranslation(dx, dy);
}

void OpenGLContainer::wheelEvent(QWheelEvent *event)
{
    int numDegrees = event->delta() / 8;
    int numSteps = numDegrees / 15;  // Usually numSteps here is declared outside the function and is used for tracking
                                     // the number of steps the wheel has been rolled. However here we use it only to
                                     // determine the direction of the scroll of the wheel

    // TODO After the settings dialog is added make the zoom factor changable
    if (numSteps == 1)
        zZoom += .01;
    else if (numSteps == -1)
        zZoom -= .01;

    setZoom(numSteps);

    /*if((event->buttons() & Qt::MiddleButton) != 0) {
      std::cout << "MouseWheelEven: wheel pressed" << std::endl;
    }*/
}

void OpenGLContainer::setXRotation(double angle)
{
    normalizeAngle(angle);
    if (angle != xRot)
    {
        xRot = angle;
        emit xRotationChanged(angle);
        update();
    }
}

void OpenGLContainer::setYRotation(double angle)
{
    normalizeAngle(angle);
    if (angle != yRot)
    {
        yRot = angle;
        emit yRotationChanged(angle);
        update();
    }
}

void OpenGLContainer::setZRotation(double angle)
{
    normalizeAngle(angle);
    if (angle != zRot)
    {
        zRot = angle;
        emit zRotationChanged(angle);
        update();
    }
}

void OpenGLContainer::setXYTranslation(int speedX, int speedY)
{
    // Covers both positive and negative values for y
    // TODO After the settings dialog is added make the defaul translation factor (here: .01) changable
    // I've noticed that the more zoomed out the scene is the less noticable the translation is if I use a constant
    // factor (here: .01). However if I combine this factor with the zoom level the translation speed gradually
    // increases the more zoomed out the scene is (and decreases upon zoom in), which leads to a very nice adaptive
    // navigation
    xTrans += .01 * speedX * zZoom;
    // The multiplication with -1 inverts the movement so that moving the mouse cursor upwards translates upwards
    yTrans += .01 * speedY * zZoom * (-1);
    std::cout << "(x: " << QString::number(xTrans, 'g', 3).toUtf8().constData()
              << "; y: " << QString::number(yTrans, 'g', 3).toUtf8().constData() << ")" << std::endl;
    emit xTranslationChanged(xTrans);
    emit yTranslationChanged(yTrans);
    update();
}

void OpenGLContainer::setZoom(int zoomDirection)
{
    // We increase the Z distance (the axis which points outwards the scene in the direction of the user)
    // based on the direction
    if (zoomDirection == 1)
        zoomIn();
    else if (zoomDirection == -1)
        zoomOut();
}

void OpenGLContainer::zoomIn()
{
    zZoom += .1;
    std::cout << "Zoom in to " << QString::number(zZoom, 'g', 3).toUtf8().constData() << std::endl;
    emit zTranslationChanged(zZoom);
    update();
}

void OpenGLContainer::zoomOut()
{
    zZoom -= .1;
    std::cout << "Zoom out to " << QString::number(zZoom, 'g', 3).toUtf8().constData() << std::endl;
    emit zTranslationChanged(zZoom);
    update();
}

void OpenGLContainer::zoomReset()
{
    zZoom = -2.0;
    std::cout << "Zoom level reset to " << QString::number(zZoom, 'g', 3).toUtf8().constData() << std::endl;
    update();
}

void OpenGLContainer::resetRotation()
{
    xRot = yRot = zRot = 0.;
    std::cout << "Rotation reset" << std::endl;
    update();
}

void OpenGLContainer::resetTranslation()
{
    xTrans = 0.;
    yTrans = 0.;
    std::cout << "Translation reset to (x: " << QString::number(xTrans, 'g', 3).toUtf8().constData()
              << "; y: " << QString::number(yTrans, 'g', 3).toUtf8().constData() << ")" << std::endl;
    update();
}
