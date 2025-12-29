#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "Fruit.h"
#include <QMainWindow>
#include <math.h>
#include <QPainter>
#include "ConstraintsManager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



public slots:
    void setText(QString s);

    void revFall(QPointF pos);

    void paintEvent(QPaintEvent *event);

    bool isTouching(Fruit ball, Fruit ball2){
        float maxR = ball.getRadius();
        if(abs(ball.getP().getX() - ball2.getP().getX()) < maxR && abs(ball.getP().getY() - ball2.getP().getY()) < maxR ){
            return true;
        }
        return false;
    }


    void moveBall(QPainter &Painter);

    void drawLine() {
        QPainter painter(this);
        painter.setPen(QPen(Qt::black, 12, Qt::DashDotLine, Qt::RoundCap));
        painter.drawLine(0, 0, 200, 200);
    }





private:
    Ui::MainWindow *ui;

    int y;

    int x ;

    bool falling = false;

    void createConstraintsManager() {
        constraints  =  new ConstraintsManager(*this,nb_balls);
    }

    //float ballsRotation[100];

    int nb_balls = 0 ;
    ConstraintsManager* constraints ;
    int i = 0 ;
    //Fruit ball2;

    int BASE_WIDTH  = 800;
    int BASE_HEIGHT = 600;
    QRect bucketRect;
    void mousePressEvent(QMouseEvent *event) override;


};
#endif // MAINWINDOW_H
