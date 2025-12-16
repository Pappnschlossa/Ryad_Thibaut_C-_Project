#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include <QPainterPath>
#include <QPainter>
#include <QScreen>

#include <math.h>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //QObject :: connect(ui -> but2, SIGNAL(clicked()), this,SLOT(setText("Oui")));
    QObject :: connect(ui -> pushButton, SIGNAL(clicked()), this,SLOT(revFall()));
    createConstraintsManager();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow :: setText(QString s){
   // float maxR = constraints->getFruit(i).getRadius();

    ui -> label->setText(s);

}

void MainWindow :: revFall() {

    Fruit fruit = Fruit(60 + constraints->getNbFruits(),50 + constraints->getNbFruits()) ;

    fruit.getP().setCoords(400,300);
    fruit.getV().setCoords(1,0);
    constraints->addFruit(fruit);
    //std :: cout << constraints->getFruit(i).getV();
    if (constraints->getNbFruits() == 1){

        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::update));
        timer->start(10);

    }
    update();
}




void MainWindow :: moveBall(){
    
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    float maxHeight = screenGeometry.height();
    float maxWidth = screenGeometry.width();
   // std:: cout << "ball0 was : " << constraints->getFruit(0).getP() << "\n" ;
    constraints->runSimulation(maxHeight,maxWidth);
    //std:: cout << "ball0 is : " << constraints->getFruit(0).getP() << "\n" ;

    for (int i = 0; i < constraints->getNbFruits() ; i++) {

        QPainterPath OuterPath;

        OuterPath.setFillRule(Qt::WindingFill);
        std:: cout << "ball i  is at  : " << constraints->getFruit(i).getP() << "\n" ;
        OuterPath.addEllipse(QPointF(constraints->getFruit(i).getP().getX() - constraints->getFruit(i).getRadius(),constraints->getFruit(i).getP().getY() - constraints->getFruit(i).getRadius()), constraints->getFruit(i).getRadius(), constraints->getFruit(i).getRadius());
        QPainterPath FillPath = OuterPath;
    
        QPainter Painter(this);

        Painter.setRenderHint(QPainter::Antialiasing);

        Painter.fillPath(FillPath, QColor(i*50 % 255,100,0));



    }
}


void MainWindow :: paintEvent(QPaintEvent *event)
{
    moveBall();
}


