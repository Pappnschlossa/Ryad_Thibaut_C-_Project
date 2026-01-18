#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include <QPainterPath>
#include <QPainter>
#include <QScreen>

#include <math.h>

#include <QTimer>
#include <QMouseEvent>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      bucketRect(-250,-300,500,600)
{
    ui->setupUi(this);
    //QObject :: connect(ui -> but2, SIGNAL(clicked()), this,SLOT(setText("Oui")));
    //QObject :: connect(ui -> pushButton, SIGNAL(clicked()), this,SLOT(revFall()));
    createConstraintsManager();
    maxHeightOffset = height()/2;
    widthOffset = width()/2;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow :: setText(QString s){
   // float maxR = constraints->constraints->getFruit(i).getRadius();
    ui -> label->setText(s);
}

void MainWindow::revFall(QPointF pos) {
    int t = 1;
    Fruit fruit = Fruit(t);
    float r = fruit.getRadius();
    float startPosX = pos.x();
    if (startPosX < r - (float) bucketRect.width()/2) {startPosX = r - (float) bucketRect.width()/2;}
    if (startPosX > (float) bucketRect.width()/2 - r) {startPosX = (float) bucketRect.width()/2 - r;}
    fruit.getP().setCoords(startPosX,-maxHeightOffset);
    fruit.getV().setCoords(1,0);
    fruit.id = constraints->getNbFruits() ;
    constraints->addFruit(fruit);

    //std :: cout << constraints->constraints->getFruit(i).getV();
    if (constraints->getNbFruits() == 1){
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::update));
        timer->start(10);
    }
    update();
}




void MainWindow :: moveBall(QPainter &Painter){
    float maxHeight = bucketRect.height()-maxHeightOffset;
    float maxWidth = bucketRect.width();
    for (int i = 0 ; i < simulationCycles ; ++i) {
        constraints->runSimulation(maxHeight,maxWidth, 0.95);

    }


    for (int i = 0; i < constraints->getNbFruits() ; i++) {
        QString pathStart = "../assets/";
        QString pathEnd = ".png";
        int power = pow(2, constraints->getFruit(i).getFruitType());
        QString path = pathStart + QString::number(power) + pathEnd;
        QPixmap pixmap(path); // Il y a tous les multiples de 2 jusqu'à 2048. (4.png, 8.png, ..., 2048.png)

        float r = constraints->getFruit(i).getRadius();
        Painter.save();
        Painter.translate(constraints->getFruit(i).getP().getX(), constraints->getFruit(i).getP().getY());
        Painter.drawPixmap(-r, -r, 2*r, 2*r, pixmap);

        Painter.setPen(QPen(Qt::black, 5));
        Painter.drawLine(0, 0, constraints->getFruit(i).getV().getX(),  constraints->getFruit(i).getV().getY());

        Painter.restore();
    }
}

void MainWindow :: setupWorldTransform(QPainter &painter)
{
    // Center the "world"
    float scale = std::min(
        width()/float(BASE_WIDTH),
        height()/float(BASE_WIDTH)
        );

    painter.translate(width() / 2.0, height() / 2.0);
    painter.scale(scale, scale);
    worldToScreen.translate(-BASE_WIDTH / 2.0, -BASE_HEIGHT / 2.0);
};

void MainWindow :: paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    setupWorldTransform(painter);

    worldToScreen = painter.transform();
    screenToWorld = worldToScreen.inverted();

    // Draw in "world" coordinates
    QPen pen(Qt::black);
    pen.setWidth(15);
    painter.setPen(pen);

    painter.drawLine(bucketRect.topLeft(), bucketRect.bottomLeft());
    painter.drawLine(bucketRect.bottomLeft(), bucketRect.bottomRight());
    painter.drawLine(bucketRect.bottomRight(), bucketRect.topRight());

    moveBall(painter);
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        revFall(screenToWorld.map(event->pos()));
    }
}


/**
void MainWindow::keyPressEvent(QKeyEvent * event)
{
    if (event->key() == Qt::Key_Space) {
        revFall(screenToWorld.map( QPoint( 100,100) ));
    }
}*/