#include "mainwindow.h"
#include "mapa.h"
#include "ui_mainwindow.h"

#include <QMainWindow>
#include <QPainter>
#include <QGraphicsItem>
#include <QRectF>
#include <QDesktopWidget>
#include <QDebug>
#include <QGraphicsScene>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Niveles = new Mapa();
    Niveles->setSceneRect(0,0,ui->graphicsView->width()-2,ui->graphicsView->height()-2);

    ui->graphicsView->setScene(Niveles);
}

MainWindow::~MainWindow()
{
    delete ui;
}


