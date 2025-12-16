 //
// Created by ryadg on 16/12/2025.
//

#ifndef C_PROJECT_CONSTAINTSMANAGER_H
#define C_PROJECT_CONSTAINTSMANAGER_H

#include "Fruit.h"
#include <QMainWindow>


 class ConstraintsManager {
public:
 ConstraintsManager( const QMainWindow& context ,  int nbF )
  : nbFruits(nbF) {
  dt = 0.01;
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
    if (_fruits[i].getV().getY() > 0 && _fruits[i].getP().getY() +_fruits[i].getRadius() >  maxHeight) {
     //_fruits[i].bounce(Vector(0,-1));
     _fruits[i].nonElasticBounce(Vector( _fruits[i].getP().getX() ,maxHeight - _fruits[i].getRadius()), dt);
     _fruits[i].getP().setY(maxHeight - _fruits[i].getRadius());
    }else {
     _fruits[i].accelerate(dt);
     for (int j = 0; j < nbFruits ; j++) {
      //std :: cout << C ;
      //setText(("C is : " + std::to_string(C) ).data()) ;
      if (i != j) {
       C = _fruits[i].colliding(_fruits[j]) ;
       if (C < 0){
        _fruits[i].collideWith(_fruits[j],C,dt);
        _fruits[j].collideWith(_fruits[i],C,dt) ;
        _fruits[i].accelerate(dt);
        col = 255 ;
       }
      }
     }
    }

    //}

    if(_fruits[i].getP().getX() +_fruits[i].getRadius()> maxWidth || _fruits[i].getP().getX() < _fruits[i].getRadius()) {
     _fruits[i].getV().setX(-_fruits[i].getV().getX());
    }
     
    _fruits[i].moveP(_fruits[i].getV(),dt);

    //_fruits[i].moveP(_fruits[i].getV(),dt);
   }


  }




  float getDt() const {
   return dt;
  }

private:
 Fruit* _fruits ;
  int nbFruits = 0;
  float dt ;
  
};
#endif //C_PROJECT_CONSTAINTSMANAGER_H
