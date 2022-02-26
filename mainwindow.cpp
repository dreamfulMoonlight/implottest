#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QGraphicsView>
#include <QLabel>
#include <QMouseEvent>
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
    m_view->setScene(scene);
    m_view->setGeometry(0, 0, 520, 520);

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
    m_view = new MyView(this);
    ui->verticalLayout_2->addWidget(m_view);
    m_view->setScene(scene);
    m_view->m_scene = scene;
    // ui->graphicsView->setGeometry(0, 0, 520, 520);
    // m_plot = new GraphicsPlotItem();
    // scene->addItem(m_plot);
    // m_plot->setRect(QRect(0, 0, 200, 200));
    //    //    plot->setTitle(QString("Test title"));
    //    m_plot->setAxisText(0, QString("x"));
    //    m_plot->setAxisText(1, QString("y"));
    //    // plot->setAutoGrid(false);
    //    m_plot->setAbscissaRange(0, 15);
    //    m_plot->setOrdinateRange(0, 100);
    // auto bounding_rect = m_plot->boundingRect();
    // scene->setSceneRect(QRect(bounding_rect.x(), bounding_rect.y(), bounding_rect.width(), bounding_rect.height()));
    //    int scene_width = 800, scene_height = 200;
    //    scene->setSceneRect(QRect(0, 0, scene_width, scene_height));

    QVector<double> absciss = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    QVector<double> ordinate = {12, 45, 34, 56, 76, 34, 56, 12, 4, 56};

    setData();

    //    m_data_item = new Graphics2DGraphItem();
    //    scene->addItem(m_data_item);
    //    m_data_item->setPen(QColor(Qt::blue));
    //    m_data_item->setData(absciss, ordinate);

    //    m_plot->addDataItem(m_data_item);
}

void MainWindow::showOpenglWidget()
{
    //    auto widget = new MyWidget();
    //    ui->verticalLayout_2->addWidget(widget);
}

void MainWindow::resetMinMaxLine(QPoint point)
{
    auto min_aix = m_view->m_aix_min->scenePos();
    auto max_aix = m_view->m_aix_max->scenePos();
    if (min_aix.x() > max_aix.x())
    {
        auto last_min = m_view->m_aix_min;
        m_view->m_aix_min = m_view->m_aix_max;
        m_view->m_aix_max = last_min;
    }
    if (abs(point.x() - min_aix.x()) <= 4)
    {
        auto dx = point.x() - min_aix.x();
        m_view->minAixMove(dx);
    }
    else if (abs(point.x() - max_aix.x()) <= 4)
    {
        auto dx = point.x() - max_aix.x();
        m_view->maxAixMove(dx);
    }
    else
    {
    }
}

void MainWindow::setData()
{
    m_view->scene()->clear();
    QVector<double> absciss = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    QVector<double> ordinate = {12, 45, 34, 56, 76, 34, 56, 12, 4, 196};

    auto abs_sciss_max = std::max_element(absciss.begin(), absciss.end());
    auto abs_sciss_min = std::min_element(absciss.begin(), absciss.end());
    auto ordinate_max = std::max_element(ordinate.begin(), ordinate.end());
    auto ordinate_min = std::min_element(ordinate.begin(), ordinate.end());

    setAbsScissRange(*abs_sciss_min, *abs_sciss_max);
    setCoordinateRange(*ordinate_min, *ordinate_max);

    setMaxInEdit(*abs_sciss_max);
    setMinInEdit(*abs_sciss_min);

    m_min_x = *abs_sciss_min, m_max_x = *abs_sciss_max;

    auto points_size = std::min(absciss.size(), ordinate.size());
    for (int point_index = 0; point_index < points_size; point_index++)
    {
        auto m_dash_line = new QGraphicsLineItem();
        auto left_x = absciss[point_index], right_x = absciss[point_index];
        auto left_y = 0.0, right_y = ordinate[point_index];
        auto left_point = transformPoint(QPointF(left_x, left_y));
        auto right_point = transformPoint(QPointF(right_x, right_y));
        m_dash_line->setLine(0, 0, right_point.x() - left_point.x(), right_point.y() - left_point.y());
        m_dash_line->setPos(QPointF(left_point.x(), left_point.y()));
        qDebug() << "set pos" << QPointF(left_point.x(), left_point.y()) << m_view->sceneRect().height()
                 << m_view->size();
        QPen *pen_dash = new QPen(QColor("red"), 2);
        m_dash_line->setPen(*pen_dash);
        m_view->scene()->addItem(m_dash_line);
    }

    setMaxAixX();
    setMinAixX();
    // m_view->scene()->update();
}

void MainWindow::setCoordinateRange(double min, double max)
{
    m_cord_range = Range(min, max);
    auto scene_rect = m_view->sceneRect();
    if (max > min)
        m_cord_ratio = (scene_rect.height() / (max));
}

void MainWindow::setAbsScissRange(double min, double max)
{
    m_abss_range = Range(min, max);
    auto scene_rect = m_view->scene()->sceneRect();
    qDebug() << "abs sciss range" << scene_rect;
    if (max > min)
        m_abss_ratio = (scene_rect.width() / (max));
}

QPointF MainWindow::transformPoint(QPointF input)
{
    auto x = input.x(), y = input.y();
    QPointF output;
    output.setX(x * m_abss_ratio);
    output.setY(m_view->sceneRect().height() - y * m_cord_ratio);
    return output;
}

void MainWindow::setMinInEdit(int value)
{
    ui->lineEdit->setText(QString::number(value));
}

void MainWindow::setMaxInEdit(int value)
{
    ui->lineEdit_2->setText(QString::number(value));
}

void MainWindow::setMinAixX()
{
    auto m_dash_line = new QGraphicsLineItem();
    auto left_point = transformPoint(QPointF(m_abss_range.min, 0));
    auto right_point = transformPoint(QPointF(m_abss_range.min, m_cord_range.max));
    m_dash_line->setLine(0, 0, right_point.x() - left_point.x(), right_point.y() - left_point.y());
    m_dash_line->setPos(QPointF(left_point.x(), left_point.y()));
    QPen *pen_dash = new QPen(QColor("black"), 2);
    m_dash_line->setPen(*pen_dash);
    m_view->scene()->addItem(m_dash_line);

    m_view->m_aix_min = m_dash_line;
}

void MainWindow::setMaxAixX()
{
    auto m_dash_line = new QGraphicsLineItem();
    m_view->scene()->addItem(m_dash_line);
    auto left_point = transformPoint(QPointF(m_abss_range.max, 0));
    auto right_point = transformPoint(QPointF(m_abss_range.max, m_cord_range.max));
    m_dash_line->setLine(0, 0, right_point.x() - left_point.x(), right_point.y() - left_point.y());
    m_dash_line->setPos(QPointF(left_point.x(), left_point.y()));
    QPen *pen_dash = new QPen(QColor("black"), 2);
    m_dash_line->setPen(*pen_dash);
    m_view->m_aix_max = m_dash_line;
    qDebug() << "max aix" << m_view->m_aix_max->scenePos();
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

MyView::MyView(QWidget *parent) : QGraphicsView(parent)
{
    m_parent_widget = parent;
}

void MyView::mouseMoveEvent(QMouseEvent *event)
{
    auto pos = event->pos();
    auto m_point = QPoint(mapToScene(pos).x(), mapToScene(pos).y());
    if ((event->buttons() != Qt::LeftButton))
        return;
    auto widget = dynamic_cast<MainWindow *>(m_parent_widget);
    if (widget)
        widget->resetMinMaxLine(m_point);
    QGraphicsView::mouseMoveEvent(event);
}

void MyView::mousePressEvent(QMouseEvent *event)
{
    auto pos = event->pos();
    qDebug() << "press" << pos;
    auto m_point = QPointF(mapToScene(pos).x(), mapToScene(pos).y());
    m_point = transformPoint(m_point);
    qDebug() << "map to scene" << m_point << size();
    QGraphicsView::mousePressEvent(event);
}

void MyView::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "release";
    QGraphicsView::mouseReleaseEvent(event);
}

void MyView::resizeEvent(QResizeEvent *event)
{
    qDebug() << "Resize Event";
    scene()->setSceneRect(QRect(0, 0, size().width(), size().height()));
    auto widget = dynamic_cast<MainWindow *>(m_parent_widget);
    if (widget)
        widget->setData();
    fitInView(scene()->sceneRect());
    QGraphicsView::resizeEvent(event);
}

QPointF MyView::transformPoint(QPointF input)
{
    QPointF output;
    output.setX(input.x());
    output.setY(scene()->height() - input.y());
    return output;
}

void MyView::minAixMove(int dx)
{
    auto lastPos = m_aix_min->scenePos();
    m_aix_min->setPos(lastPos.x() + dx, lastPos.y());
    auto widget = dynamic_cast<MainWindow *>(m_parent_widget);
    if (widget)
        widget->setMinInEdit(int((lastPos.x() + dx) / widget->m_abss_ratio));
}

void MyView::maxAixMove(int dx)
{
    auto lastPos = m_aix_max->scenePos();
    m_aix_max->setPos(lastPos.x() + dx, lastPos.y());
    auto widget = dynamic_cast<MainWindow *>(m_parent_widget);
    if (widget)
        widget->setMaxInEdit(int((lastPos.x() + dx) / widget->m_abss_ratio));
}
