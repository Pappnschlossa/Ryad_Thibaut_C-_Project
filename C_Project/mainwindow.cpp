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
    , ball(30)
{
    ui->setupUi(this);
    //QObject :: connect(ui -> but2, SIGNAL(clicked()), this,SLOT(setText("Oui")));
    QObject :: connect(ui -> pushButton, SIGNAL(clicked()), this,SLOT(revFall()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow :: setText(QString s){
    float maxR = ball.getRadius();

    ui -> label->setText(s);

}

void MainWindow :: revFall(){
    ball.getP().setCoords(660,100);
    ball.getV().setCoords(0,0);
    //std :: cout << ball.getV();

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::update));
    falling = !falling;
    timer->start(10);
    update();
}




void MainWindow :: moveBall(Fruit& ball){
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int maxHeight = screenGeometry.height();
    int maxWidth = screenGeometry.width();

    float r = ball.getRadius();


    if(ball.getP().getY() + 2*r >  maxHeight ){
        if (ball.getV().getY() > 0) {
            ball.getV().setY(- ball.getV().getY() ) ;
            setText((ball.getV().toString() + ball.getP().toString() + std::to_string(maxHeight)).data() );

            //setText(ball.bounce(Vector(1/sqrt(2),-1/sqrt(2))).data() );
        }
    }

    if(ball.getP().getX() + r > maxWidth || ball.getP().getX() < r){
        ball.getV().setX(-ball.getV().getX());
    }
    QPainterPath OuterPath;

    OuterPath.setFillRule(Qt::WindingFill);
    OuterPath.addEllipse(QPointF(ball.getP().getX() - r,ball.getP().getY() - r), 2*r, 2*r);
    QPainterPath FillPath = OuterPath;

    QPainter Painter(this);

    Painter.setRenderHint(QPainter::Antialiasing);

    Painter.fillPath(FillPath, Qt::blue);

    if (ball.getP().getY() + r > maxHeight ) {
        ball.getAccel().setY(0);
    }else {
        ball.getAccel().setY(ball.getG());
    }
    ball.accelerate();

    ball.moveP(ball.getV());
}


void MainWindow :: paintEvent(QPaintEvent *event)
{

    if(falling){

        moveBall(ball);
        //setText(ball.getV().toString().data());


        /**moveBall(ball2);
        if(isTouching(ball,ball2)){
            float dist = ball.getRadius();
            float newX[2]  = {ball.getP()[0]-  dist, ball.getP()[1]};
            ball.setP(newX);
            unitaryDir(ball,ball2);
            unitaryDir(ball2,ball);
            setText("touched! ");
        }*/
        // sleep 5s

    }
}


