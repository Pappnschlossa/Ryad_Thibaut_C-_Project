#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "Fruit.h"
#include <QMainWindow>
#include <math.h>

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

    void revFall();

    void paintEvent(QPaintEvent *event);

    bool isTouching(Fruit anim, Fruit anim2){
        float maxR = anim.getRadius();
        if(abs(anim.getP()[0] - anim2.getP()[0]) < maxR && abs(anim.getP()[1] - anim2.getP()[1]) < maxR ){
            return true;
        }
        return false;
    }


    void moveBall(Fruit anim);

    float distance(Fruit a, Fruit b){
        const float* p_a = a.getP();
        const float* p_b = b.getP();
        const float X[2] = {p_b[0] - p_a[0], p_b[1] - p_a[1]};
        return sqrt(X[0]*X[0] + X[1]*X[1]);
    }

    void unitaryDir(Fruit a, Fruit b){
        const float* p_a = a.getP();
        const float* p_b = b.getP();
        float d = distance(a,b) + 10;
        float coef_a = a.normV()/d;
        float X[2] = {-(p_b[0] - p_a[0])*coef_a + a.getV()[0], -(p_b[1] - p_a[1])*coef_a + a.getV()[1]};
        a.setV(X);

    }



private:
    Ui::MainWindow *ui;

    int y;

    int x ;

    bool falling = false;


    Fruit anim;
    //Fruit anim2;



};
#endif // MAINWINDOW_H
