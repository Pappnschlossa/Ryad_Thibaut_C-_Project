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
    Fruit fruit = Fruit(50,100) ;
    fruit.getP().setCoords(pos.x()-width()/2,-height()/2);
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
    float maxHeight = bucketRect.height()-height()/2 + 60 ; // 60 correspond à r (si on lance une balle)
    float maxWidth = bucketRect.width();
    constraints->runSimulation(maxHeight,maxWidth);

    for (int i = 0; i < constraints->getNbFruits() ; i++) {

        QPainterPath OuterPath;

        OuterPath.setFillRule(Qt::WindingFill);
        //std:: cout << "ball i  is at  : " << constraints->constraints->getFruit(i).getP() << "\n" ;
        OuterPath.addEllipse(QPointF(constraints->getFruit(i).getP().getX(), constraints->getFruit(i).getP().getY()),
                             constraints->getFruit(i).getRadius(), constraints->getFruit(i).getRadius());
        QPainterPath FillPath = OuterPath;

        QPixmap pixmap("../assets/placeholder.png");

        //ballsRotation[ballIndex] -= ball.getV().getX()/100;
        float temp_merge_r = 50;
        float r = temp_merge_r;
        Painter.save();
        Painter.translate(constraints->getFruit(i).getP().getX() + r, constraints->getFruit(i).getP().getY() + r);
        //Painter.rotate(ballsRotation[ballIndex]);
        Painter.drawPixmap(-r,  -r, 2*r, 2*r, pixmap);

        Painter.fillPath(FillPath, QColor(i*50 % 255,100,0));

        Painter.setPen(QPen(Qt::black, 5));
        Painter.drawLine(constraints->getFruit(i).getP().getX(), constraints->getFruit(i).getP().getY(),
                         constraints->getFruit(i).getP().getX() + 10 * constraints->getFruit(i).getV().getX(),
                         constraints->getFruit(i).getP().getY() + 10 * constraints->getFruit(i).getV().getY());

        Painter.restore();
    }
}


void MainWindow :: paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // Center the "world"
    float scale = std::min(
        width()/float(BASE_WIDTH),
        height()/float(BASE_WIDTH)
        );

    painter.translate(width() / 2.0, height() / 2.0);
    painter.scale(scale, scale);

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
        revFall(event->pos());
    }
}