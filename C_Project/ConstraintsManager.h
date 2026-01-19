 //
// Created by ryadg on 16/12/2025.
//

#ifndef C_PROJECT_CONSTAINTSMANAGER_H
#define C_PROJECT_CONSTAINTSMANAGER_H

#include "Fruit.h"
#include <QMainWindow>
#include <QPainter>
#include <vector>

#include "Array.h"
#include "RestartBox.h"


class ConstraintsManager : public QWidget {
public:
 ConstraintsManager( const QMainWindow& context ,  int nbF )
 {
  dt = 0.00005;
 }

  ConstraintsManager();


  Fruit& getFruit(int index) {
   if (index < _fruits.getFill()) {
    return *_fruits[index];
   }
  }

  void addFruit(Fruit& fruit) {
   _fruits.add( fruit );
  }

  const int getNbFruits() const {
   return _fruits.getFill();
  }


  void runSimulation(float maxHeight, float maxWidth) ;



  float getDt() const {
   return dt;
  }

private:
  Array<Fruit>  _fruits =   Array<Fruit>(200);
  Array<int> banList = Array<int>(200) ;


  float dt ;


  bool collidePlan(Fruit& fruit,const Vector& p ,const Vector& n,bool handle) {
   Vector nextP = fruit.getP() + fruit.getV()*dt ;
   if ((nextP - p )*n - fruit.getRadius() < 0 ) {
    if (handle) {
     handleCollision( nextP,  n,  p,  fruit) ;
    }
    return true;
   }
    if ((nextP - p )*n - fruit.getRadius() < 1 ) {
     fruit.getAccel() = fruit.getAccel() -  n*(fruit.getAccel()*n) ;
    }
   return false;
  }


  void handleCollision(Vector& nextP, const Vector& n, const Vector& p, Fruit& fruit){
   Vector q = nextP - n*((nextP - p)*n );
   float C = (nextP - q) * n - fruit.getRadius() ;
   Vector delta = n*(-C) ;


    fruit.nonElasticWallBounce(nextP + delta);
    //Needs to have full speed to get out the wall properly

    fruit.getP().setCoords(nextP + delta);
    fruit.getAccel() = fruit.getAccel() -  n*(fruit.getAccel()*n) ;

  }
};
#endif //C_PROJECT_CONSTAINTSMANAGER_H
