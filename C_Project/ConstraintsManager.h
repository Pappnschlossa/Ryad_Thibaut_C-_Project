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


 class ConstraintsManager {
public:
 ConstraintsManager( const QMainWindow& context ,  int nbF )
  : nbFruits(nbF) {
  dt = 0.01;
 }

  ConstraintsManager();


  Fruit& getFruit(int index) {
   if (index < nbFruits) {
    return *_fruits[index];
   }
  }

  void addFruit(Fruit& fruit) {
   _fruits.add( fruit );
   nbFruits += 1 ;
  }

  const int getNbFruits() const {
   return nbFruits;
  }


  void runSimulation(float maxHeight, float maxWidth,float frot) {
   int col= 0 ;

   float C = 0 ;
   for (int i = 0 ; i < nbFruits; ++i){
    _fruits[i]->getAccel().setY(_fruits[i]->getG()) ;

    //checks the collision and handles it
     if( !collidePlan(*_fruits[i],Vector(-maxWidth/2,0), Vector(1,0),true )
      && !collidePlan(*_fruits[i],Vector(maxWidth/2,0), Vector(-1,0) , true)
      && !collidePlan(*_fruits[i],Vector(0,maxHeight), Vector(0,-1) , true)) {
      _fruits[i]->accelerate(dt);

      //_fruits[i]->getV() =       _fruits[i]->getV()*frot ;

      //_fruits.shuffle(1);

      for (int j = 0; j < nbFruits ; j++) {
       if (i != j) {
        C = _fruits[i]->colliding(*_fruits[j],dt) ;
        if (C < 0) {
         _fruits[i]->collideWith(*_fruits[j],C,dt);

         if( !collidePlan(*_fruits[j],Vector(-maxWidth/2,0), Vector(1,0),true )
          && !collidePlan(*_fruits[j],Vector(maxWidth/2,0), Vector(-1,0) , true)
          && !collidePlan(*_fruits[j],Vector(0,maxHeight), Vector(0,-1) , true)) {
               /**_fruits[j]->collideWith(*_fruits[i],C,dt) ;

               float v_scal = sqrt(_fruits[j]->getV().getSquaredLength()) ;
               if (v_scal > dt) {
                _fruits[j]->getV()= _fruits[j]->getV()* ((std :: min(v_scal,_fruits[j]->getRadius()/2))/(v_scal)) ;
               }*/
         }
         float v_scal = sqrt(_fruits[i]->getV().getSquaredLength()) ;
         if (v_scal > dt) {
          _fruits[i]->getV()= _fruits[i]->getV()* ((std :: min(v_scal,_fruits[i]->getRadius()/2))/v_scal) ;
         }



         col = 255 ;
        }
       }

        }
      _fruits[i]->moveP(_fruits[i]->getV(),dt);
      }

   }


  }




  float getDt() const {
   return dt;
  }

private:
  Array<Fruit>  _fruits =  Array<Fruit>(100);
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
