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


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow :: setText(QString s){
   // float maxR = ball.getRadius();

    ui -> label->setText(s);

}

void MainWindow :: revFall() {

    balls[nb_balls] = Fruit(0.01, 60 + nb_balls,50 + nb_balls);
    balls[nb_balls].getP().setCoords(400,300);
    balls[nb_balls].getV().setCoords(10,0);
    //std :: cout << ball.getV();
    nb_balls += 1;
    if (nb_balls == 1){
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::update));
        timer->start(10);
    }
    update();
}




void MainWindow :: moveBall(Fruit& ball,int ballIndex){
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    float maxHeight = screenGeometry.height();
    float maxWidth = screenGeometry.width();

    int col = 0 ;
    float C = 0 ;
    float r = ball.getRadius();

    if (ball.getV().getY() > 0 && ball.getP().getY() + r  >  maxHeight) {
        //ball.bounce(Vector(0,-1));
        ball.nonElasticBounce(Vector( ball.getP().getX() ,maxHeight -  r ));
        ball.getP().setY(maxHeight - r);
    }else {
        ball.accelerate();
        for (int j = 0; j < nb_balls ; j++) {
            //std :: cout << C ;
            //setText(("C is : " + std::to_string(C) ).data()) ;
            if (ballIndex != j) {
                C = ball.colliding(balls[j]) ;
                if (C < 0){
                    ball.collideWith(balls[j],C);
                    balls[j].collideWith(ball,C) ;
                    ball.accelerate();
                    col = 255 ;
                }
            }
        }
    }

//}

    if(ball.getP().getX() + r > maxWidth || ball.getP().getX() < r) {
        ball.getV().setX(-ball.getV().getX());
    }
    QPainterPath OuterPath;

    OuterPath.setFillRule(Qt::WindingFill);
    OuterPath.addEllipse(QPointF(ball.getP().getX() - r,ball.getP().getY() - r), r, r);
    QPainterPath FillPath = OuterPath;

    QPainter Painter(this);

    Painter.setRenderHint(QPainter::Antialiasing);

    Painter.fillPath(FillPath, QColor(ballIndex*50 % 255,100,0));


    ball.moveP(ball.getV());
}


void MainWindow :: paintEvent(QPaintEvent *event)
{
    for (int i = 0; i  < nb_balls; i++) {
        moveBall(balls[i],i);
    }


}


