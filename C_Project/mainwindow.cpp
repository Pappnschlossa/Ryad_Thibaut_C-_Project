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
    if (startPosX < r - (float) bucketRect.width()/2 + 1) {startPosX = r - (float) bucketRect.width()/2 + 1;}
    if (startPosX > (float) bucketRect.width()/2 - r - 1) {startPosX = (float) bucketRect.width()/2 - r - 1;}
    fruit.getP().setCoords(startPosX,-maxHeightOffset-r);
    fruit.setLoseCondition(-maxHeightOffset-2*r);
    fruit.getV().setCoords(1,0);
    fruit.setSpawnX(startPosX);
    fruit.id = constraints->getNbFruits() ;
    constraints->addFruit(fruit);

    // Ici on détermine le type du prochain fruit (souvent petit au début de la partie)
    int nbFruits = round(constraints->getNbFruits());
    nextFruitType = rand()%std::min(nbFruits,15) / 3 + 1;

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
        if (constraints->getFruit(i).getValid()) {
            QString pathStart = "../assets/";
            QString pathEnd = ".png"; // Change to svg to have fruits instead of numbers. Warning : Fruit svgs are not well scaled yet.
            int power = pow(2, constraints->getFruit(i).getFruitType());
            QString path = pathStart + QString::number(power) + pathEnd;
            QPixmap pixmap(path);


            float r = constraints->getFruit(i).getRadius();
            Painter.save();
            Painter.translate(constraints->getFruit(i).getP().getX(), constraints->getFruit(i).getP().getY());
            double rotation = 1.5*(constraints->getFruit(i).getP().getX()-constraints->getFruit(i).getSpawnX());
            Painter.rotate(rotation);
            Painter.drawPixmap(-r, -r, 2*r, 2*r, pixmap);

            Painter.rotate(-rotation); // to rotate back
            // Painter.setPen(QPen(Qt::black, 5));
            // Painter.drawLine(0, 0, constraints->getFruit(i).getV().getX(),  constraints->getFruit(i).getV().getY());

            Painter.restore();
        }else {
            std:: cout << "Warning, invalid balls are still loaded in memory ! \n" ;
        }
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
    QPen penGray(Qt::gray);
    penGray.setWidth(15);
    painter.setPen(penGray);

    painter.drawLine(bucketRect.topLeft(), bucketRect.topRight());

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
        if (clickTimer.elapsed() >= 300) {
            clickTimer.restart();
            dropFruit(screenToWorld.map(event->pos()));
        }
    }
}


/**
void MainWindow::keyPressEvent(QKeyEvent * event)
{
    if (event->key() == Qt::Key_Space) {
        revFall(screenToWorld.map( QPoint( 100,100) ));
    }
}*/