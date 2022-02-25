#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "GraphicsPlotItem.h"
#include <QDebug>
#include <QGraphicsView>
#include <QOpenGLContext>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::show2DHistogram()
{
    // QGraphicsView graphicsView;
    QGraphicsScene *scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setGeometry(0, 0, 520, 520);

    Graphics2DHistogramItem *histogramm = new Graphics2DHistogramItem();
    histogramm->setBrush(QBrush(Qt::red));
    QList<float> absciss, ordinate;
    for (int i = 0; i <= 10; ++i)
    {
        absciss.append(-20 + 2 * i);
        ordinate.append(-30 + 2 * i);
    }

    histogramm->setData(absciss, ordinate);

    scene->addItem(histogramm);
    histogramm->setScale(4);
}

void MainWindow::show2DPolyItem()
{
    QGraphicsScene *scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    // ui->graphicsView->setGeometry(0, 0, 520, 520);
    GraphicsPlotItem *plot = new GraphicsPlotItem();
    scene->addItem(plot);
    plot->setRect(QRect(0, 0, 500, 500));
    //    plot->setTitle(QString("Test title"));
    plot->setAxisText(0, QString("x"));
    plot->setAxisText(1, QString("y"));
    // plot->setAutoGrid(false);
    plot->setAbscissaRange(0, 10);
    plot->setOrdinateRange(0, 100);
    auto bounding_rect = plot->boundingRect();
    scene->setSceneRect(
        QRect(bounding_rect.x() + 127, bounding_rect.y() - 500, bounding_rect.width(), bounding_rect.height()));
    QVector<double> absciss = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    QVector<double> ordinate = {12, 45, 34, 56, 76, 34, 56, 12, 4, 56};

    Graphics2DGraphItem *dataItem = new Graphics2DGraphItem();
    dataItem->setPen(QColor(Qt::blue));
    dataItem->setData(absciss, ordinate);

    plot->addDataItem(dataItem);
}

void MainWindow::showOpenglWidget()
{
    //    auto widget = new MyWidget();
    //    ui->verticalLayout_2->addWidget(widget);
}

MyWidget::MyWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    // initializeGL();
}

void MyWidget::lineSegment()
{
    // paintGL();
}

void MyWidget::initializeGL()
{
    initializeOpenGLFunctions();
    // initializeGLContext();
    setGeometry(0, 0, 640, 480);     //设置窗口初始位置和大小
    glClearColor(1.0, 1.0, 1.0, 0);  //改变窗口的背景颜色，不过我这里貌似设置后并没有什么效果
    glEnable(GL_DEPTH_TEST);         //允许深度测试
    glDepthFunc(GL_LEQUAL);          //设置深度测试类型
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,
           GL_NICEST);   //进行透视校正
    glEnable(GL_BLEND);  //打开混合
    glBlendFunc(GL_SRC_ALPHA,
                GL_ONE_MINUS_SRC_ALPHA);  //设置颜色混合，用于透明
}

void MyWidget::resizeGL(int w, int h)
{
    //    if (0 == h)
    //        h = 1;                             //防止一条边为0
    //    glViewport(0, 0, (GLint)w, (GLint)h);  //重置当前视口，本身不是重置窗口的，只不过是这里被Qt给封装好了
    //    glMatrixMode(GL_PROJECTION);  //选择投影矩阵

    //    glLoadIdentity();            //重置选择好的投影矩阵
    //    glMatrixMode(GL_MODELVIEW);  //以下2句和上面出现的解释一样
    //    glLoadIdentity();
}

void MyWidget::paintGL()
{
    GLint dataValue[12] = {452, 368, 214, 543, 328, 193, 322, 436, 257, 268, 473, 467};

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);

    glVertex2i(20, 20);  // y轴
    glVertex2i(20, 450);

    //    glVertex2i(15, 15);  // 100
    //    glVertex2i(30, 30);

    //    glVertex2i(30, 30);  // 200
    //    glVertex2i(45, 50);

    //    glVertex2i(45, 50);  // 300
    //    glVertex2i(55, 350);

    glVertex2i(10, 30);  // x轴
    glVertex2i(530, 30);

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
            glVertex2i(i * 3 + 30, dataValue[i] / 20 + 20);
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
