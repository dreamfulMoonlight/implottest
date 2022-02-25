#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "GraphicsPlotItem.h"
#include <QDebug>
#include <QGraphicsView>
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
    plot->setAbscissaRange(0, 255);
    plot->setOrdinateRange(0, 10000);
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
