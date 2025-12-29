 //
// Created by ryadg on 16/12/2025.
//

#ifndef C_PROJECT_CONSTAINTSMANAGER_H
#define C_PROJECT_CONSTAINTSMANAGER_H

#include "Fruit.h"
#include <QMainWindow>
#include <QPainter>


 class ConstraintsManager {
public:
 ConstraintsManager( const QMainWindow& context ,  int nbF )
  : nbFruits(nbF) {
  dt = 0.1;
  _fruits = new Fruit[100] ;

 }

  ConstraintsManager();


  Fruit& getFruit(int index) {
   if (index < nbFruits) {
    return _fruits[index];
   }
  }

  void addFruit(const Fruit& fruit) {
     _fruits[nbFruits] = fruit;
   nbFruits += 1 ;
  }

  const int getNbFruits() const {
   return nbFruits;
  }


  void runSimulation(float maxHeight, float maxWidth) {
   int col= 0 ;

   float C = 0 ;
   for (int i = 0 ; i < nbFruits; ++i){
    _fruits[i].getAccel().setY(_fruits[i].getG()) ;

    //checks the collision and handles it
     if( !collidePlan(_fruits[i],Vector(0,0), Vector(1,0),true )
      && !collidePlan(_fruits[i],Vector(maxWidth,0), Vector(-1,0) , true)
      && !collidePlan(_fruits[i],Vector(0,maxHeight), Vector(0,-1) , true)) {
      _fruits[i].accelerate(dt);
      _fruits[i].moveP(_fruits[i].getV(),dt);

      for (int j = 0; j < nbFruits ; j++) {
       if (i != j) {
        C = _fruits[i].colliding(_fruits[j],dt) ;
        if (C < 0) {
         _fruits[i].collideWith(_fruits[j],C,dt);

         if( !collidePlan(_fruits[j],Vector(0,0), Vector(1,0),true )
          && !collidePlan(_fruits[j],Vector(maxWidth,0), Vector(-1,0) , true)
          && !collidePlan(_fruits[j],Vector(0,maxHeight), Vector(0,-1) , true)) {
               _fruits[j].collideWith(_fruits[i],C,dt) ;
         }


         col = 255 ;
        }
       }

        }
      }

   }


  }




  float getDt() const {
   return dt;
  }

private:
 Fruit* _fruits ;
  int nbFruits = 0;
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

   fruit.nonElasticWallBounce(nextP + delta, dt);
   //Needs to have full speed to get out the wall properly

   fruit.getP().setCoords(nextP + delta);
   fruit.getAccel() = fruit.getAccel() -  n*(fruit.getAccel()*n) ;
  }
};
#endif //C_PROJECT_CONSTAINTSMANAGER_H
