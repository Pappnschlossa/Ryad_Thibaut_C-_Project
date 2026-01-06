#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include <QPainterPath>
#include <QPainter>
#include <QScreen>

#include <math.h>
#include <cmath>

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
    clickTimer.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow :: setText(QString s){
   // float maxR = constraints->constraints->getFruit(i).getRadius();
    ui -> label->setText(s);
}

void MainWindow::dropFruit(QPointF pos) {
    srand(time(NULL));
    Fruit fruit = Fruit(nextFruitType);
    float r = fruit.getRadius();
    float startPosX = pos.x();
    if (startPosX < r - (float) bucketRect.width()/2) {startPosX = r - (float) bucketRect.width()/2;}
    if (startPosX > (float) bucketRect.width()/2 - r) {startPosX = (float) bucketRect.width()/2 - r;}
    fruit.getP().setCoords(startPosX,-maxHeightOffset-r-50);
    fruit.getV().setCoords(1,0);
    fruit.id = constraints->getNbFruits() ;
    constraints->addFruit(fruit);

    // Ici on détermine le type du prochain fruit (souvent petit au début de la partie)
    int nbFruits = round(constraints->getNbFruits());
    nextFruitType = rand()%std::min(nbFruits,16) / 4 + 1;

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
    constraints->runSimulation(maxHeight,maxWidth, 0.95);

    for (int i = 0; i < constraints->getNbFruits() ; i++) {
        QString pathStart = "../assets/";
        QString pathEnd = ".png";
        int power = pow(2, constraints->getFruit(i).getFruitType());
        QString path = pathStart + QString::number(power) + pathEnd;
        QPixmap pixmap(path);

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

    // draw the Bucket
    painter.drawLine(bucketRect.topLeft(), bucketRect.bottomLeft());
    painter.drawLine(bucketRect.bottomLeft(), bucketRect.bottomRight());
    painter.drawLine(bucketRect.bottomRight(), bucketRect.topRight());

    // draw the next Ball
    QString pathStart = "../assets/";
    QString pathEnd = ".png";
    int power = pow(2, nextFruitType);
    QString path = pathStart + QString::number(power) + pathEnd;
    QPixmap pixmap(path);
    QPixmap pixmapSign("../assets/sign.png");
    float r = 30;
    painter.save();
    painter.translate(bucketRect.topRight());
    painter.translate(4*r, 2*r);
    painter.drawPixmap(-2*r, -2*r, 4*r, 4*r, pixmapSign);
    painter.drawPixmap(-r, -r, 2*r, 2*r, pixmap);
    painter.restore();

    moveBall(painter);
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (clickTimer.elapsed() >= 500) {
            clickTimer.restart();
            dropFruit(screenToWorld.map(event->pos()));
        }
    }
}