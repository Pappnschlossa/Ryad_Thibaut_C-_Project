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
   // float maxR = constraints->constraints->getFruit(i).getRadius();

    ui -> label->setText(s);

}

void MainWindow :: revFall() {

    Fruit fruit = Fruit(50,100) ;
    fruit.getP().setCoords(300,500);
    fruit.getV().setCoords(1,0);
    fruit.id = constraints->getNbFruits() ;
    constraints->addFruit(fruit);

    //std :: cout << constraints->constraints->getFruit(i).getV();
    if (constraints->getNbFruits() == 1){

        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::update));
        timer->start(10);

    }
    //constraints->addFruit(fruit2);

    update();
}




void MainWindow :: moveBall(){
    
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    float maxHeight = 3*screenGeometry.height()/4;
    float maxWidth = screenGeometry.width();
   // std:: cout << "ball0 was : " << constraints->constraints->getFruit(0).getP() << "\n" ;
    constraints->runSimulation(maxHeight,maxWidth, 0.95);
    //std:: cout << "ball0 is : " << constraints->constraints->getFruit(0).getP() << "\n" ;

    for (int i = 0; i < constraints->getNbFruits() ; i++) {

        QPainterPath OuterPath;

        OuterPath.setFillRule(Qt::WindingFill);
        //std:: cout << "ball i  is at  : " << constraints->constraints->getFruit(i).getP() << "\n" ;
        OuterPath.addEllipse(QPointF(constraints->getFruit(i).getP().getX(),constraints->getFruit(i).getP().getY() ), constraints->getFruit(i).getRadius(), constraints->getFruit(i).getRadius());
        QPainterPath FillPath = OuterPath;
    
        QPainter Painter(this);



        Painter.setRenderHint(QPainter::Antialiasing);

        Painter.fillPath(FillPath, QColor(i*50 % 255,100,0));

        //if (constraints->getFruit(i).id == 1) {
            
            Painter.setPen(QPen(Qt::black, 2));
            Painter.drawLine(constraints->getFruit(i).getP().getX(), constraints->getFruit(i).getP().getY(), constraints->getFruit(i).getP().getX() + 10*constraints->getFruit(i).getV().getX(), constraints->getFruit(i).getP().getY() + 10*constraints->getFruit(i).getV().getY());
        //}


    }
}


void MainWindow :: paintEvent(QPaintEvent *event)
{
    moveBall();
}




