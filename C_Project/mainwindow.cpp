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
    , anim(30)
{
    ui->setupUi(this);
    //QObject :: connect(ui -> but2, SIGNAL(clicked()), this,SLOT(setText("Oui")));
    QObject :: connect(ui -> pushButton, SIGNAL(clicked()), this,SLOT(revFall()));

    anim.setP(new float[] {60,60});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow :: setText(QString s){
    float maxR = anim.getRadius();

    ui -> label->setText(ui -> label->text() + s);

}

void MainWindow :: revFall(){

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::update));
    falling = !falling;
    timer->start(10);
    update();
}



void MainWindow :: moveBall(Fruit anim){
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int maxHeight = screenGeometry.height();
    int maxWidth = screenGeometry.width();

    float r = anim.getRadius();


    if(anim.getP()[1] + r > maxHeight){
        const float * v = anim.getV();
        float newV[2] = {v[0],-v[1] - 1};
        anim.setV(newV);
    }

    if(anim.getP()[0] + r > maxWidth || anim.getP()[0] < r){
        const float * v = anim.getV();
        float newV[2] = {-v[0],v[1]};
        anim.setV(newV);
    }
    QPainterPath OuterPath;

    OuterPath.setFillRule(Qt::WindingFill);
    OuterPath.addEllipse(QPointF(anim.getP()[0] - r,anim.getP()[1] - r), 2*r, 2*r);
    QPainterPath FillPath = OuterPath;

    QPainter Painter(this);

    Painter.setRenderHint(QPainter::Antialiasing);

    Painter.fillPath(FillPath, Qt::blue);

    anim.accelerate();
    //    std :: cout << "a is : " << accel[0] << " , " << accel[1] << "\n";
    //std :: cout << "v is : " << anim.getV()[0] << " , " << anim.getV()[1] << " r is " << r << "\n";

    anim.moveP(anim.getV());
}


void MainWindow :: paintEvent(QPaintEvent *event)
{

    if(falling){

        moveBall(anim);
        /**moveBall(anim2);
        if(isTouching(anim,anim2)){
            float dist = anim.getRadius();
            float newX[2]  = {anim.getP()[0]-  dist, anim.getP()[1]};
            anim.setP(newX);
            unitaryDir(anim,anim2);
            unitaryDir(anim2,anim);
            setText("touched! ");
        }*/
        // sleep 5s

    }
}


