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
      ball(30),
      bucketRect(-250,-300,500,600)
{
    ui->setupUi(this);
    //setMinimumSize(BASE_WIDTH, BASE_HEIGHT);
    //QObject :: connect(ui -> but2, SIGNAL(clicked()), this,SLOT(setText("Oui")));
    //QObject :: connect(ui -> pushButton, SIGNAL(clicked()), this,SLOT(revFall())); // Old method : push button to make a ball fall



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow :: setText(QString s){
    float maxR = ball.getRadius();

    ui -> label->setText(s);

}

void MainWindow::revFall(QPointF pos){
    ball.getP().setCoords(pos.x()-width()/2,-height()/2);
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
    // QRect  screenGeometry = screen->geometry();
    int maxHeight = bucketRect.height()-height()/2;
    int maxWidth = bucketRect.width();

    float r = ball.getRadius();

    //setText(QString(std::to_string(cos(1)).data() ) );
    if(ball.getP().getY() + 2*r  >  maxHeight && ball.getV().getX() == 0){
        if (ball.getV().getY() > 0) {
            float theta = M_PI/2 - 0.01;
            ball.bounce(Vector(cos(theta),sin(theta)));
        }
    } else {
        if (ball.getV().getY() > 0 && ball.getP().getY() + 2*r  >  maxHeight) {
            setText(ball.bounce(Vector(0,-1)).data());
        }else {
            ball.accelerate();
        }
    }

    if(ball.getP().getX() + r > maxWidth || ball.getP().getX() < r) {
        ball.getV().setX(-ball.getV().getX());
    }
    QPainterPath OuterPath;

    OuterPath.setFillRule(Qt::WindingFill);
    OuterPath.addEllipse(QPointF(ball.getP().getX() - r,ball.getP().getY() - r), 2*r, 2*r);
    QPainterPath FillPath = OuterPath;

    QPainter Painter(this);

    float scaleX = width()/float(BASE_WIDTH);
    float scaleY = height()/float(BASE_WIDTH);
    float scale = qMin(scaleX, scaleY);

    Painter.translate(width() / 2.0, height() / 2.0);

    Painter.scale(scale, scale);

    Painter.setRenderHint(QPainter::Antialiasing);

    Painter.fillPath(FillPath, Qt::blue);

    if (ball.getP().getY() + r > maxHeight ) {
        ball.getAccel().setY(0);
    }else {
        ball.getAccel().setY(ball.getG());
    }

    ball.moveP(ball.getV());
}


void MainWindow :: paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    float scaleX = width()/float(BASE_WIDTH);
    float scaleY = height()/float(BASE_WIDTH);
    float scale = qMin(scaleX, scaleY);

    painter.translate(width() / 2.0, height() / 2.0);

    painter.scale(scale, scale);

    QPen pen(Qt::black);
    pen.setWidth(6);
    painter.setPen(pen);

    painter.drawLine(bucketRect.topLeft(), bucketRect.bottomLeft());
    painter.drawLine(bucketRect.bottomLeft(), bucketRect.bottomRight());
    painter.drawLine(bucketRect.bottomRight(), bucketRect.topRight());

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


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        revFall(event->pos());
    }
}