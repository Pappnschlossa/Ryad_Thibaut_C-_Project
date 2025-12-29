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
    //QObject :: connect(ui -> pushButton, SIGNAL(clicked()), this,SLOT(revFall())); // Old method : push button to make a ball fall



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow :: setText(QString s){
   // float maxR = ball.getRadius();

    ui -> label->setText(s);

}

void MainWindow::revFall(QPointF pos) {
    ballsRotation[nb_balls] = 0;
    balls[nb_balls] = Fruit(0.01, 60 + nb_balls,50 + nb_balls);
    balls[nb_balls].getP().setCoords(pos.x()-width()/2,-height()/2);
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

void MainWindow :: moveBall(Fruit& ball, int ballIndex){
    // QScreen *screen = QGuiApplication::primaryScreen();
    // QRect  screenGeometry = screen->geometry();
    float maxHeight = bucketRect.height()-height()/2 + 60 ; // 60 correspond à r (si on lance une balle)
    float maxWidth = bucketRect.width();

    int col = 0 ;
    float C = 0 ;
    float r = ball.getRadius();
    if (ball.getV().getY() > 0 && ball.getP().getY() + r  >  maxHeight) {
        printf("touched 1\n");
        //ball.bounce(Vector(0,-1));
        ball.nonElasticBounce(Vector(ball.getP().getX() ,maxHeight -  r ));
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

    if(ball.getP().getX() + r > maxWidth || ball.getP().getX() < r) {
        ball.getV().setX(-ball.getV().getX());
    }
    QPainterPath OuterPath;

    OuterPath.setFillRule(Qt::WindingFill);
    OuterPath.addEllipse(QPointF(ball.getP().getX() - r,ball.getP().getY() - r), r, r);
    QPainterPath FillPath = OuterPath;

    QPainter Painter(this);

    float scaleX = width()/float(BASE_WIDTH);
    float scaleY = height()/float(BASE_WIDTH);
    float scale = qMin(scaleX, scaleY);

    Painter.translate(width() / 2.0, height() / 2.0);

    Painter.scale(scale, scale);

    QPixmap pixmap("../assets/placeholder.png");

    ballsRotation[ballIndex] -= ball.getV().getX()/100;
    //Painter.save();
    Painter.translate(ball.getP().getX() + r, ball.getP().getY() + r);
    Painter.rotate(ballsRotation[ballIndex]);
    Painter.drawPixmap(-r,  -r, 2*r, 2*r, pixmap);
    //Painter.restore();
    //Painter.fillPath(FillPath, QColor(ballIndex*50 % 255,100,0));


    ball.moveP(ball.getV());
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

    for (int i = 0; i  < nb_balls; i++) {
        moveBall(balls[i],i);
    }
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        revFall(event->pos());
    }
}