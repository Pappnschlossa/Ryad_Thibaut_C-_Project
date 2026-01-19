//
// Created by ryadg on 16/12/2025.
//

#include "ConstraintsManager.h"



void ConstraintsManager::runSimulation(float maxHeight, float maxWidth) {
   int banSize = 0 ;
   float C = 0 ;

   int fill = _fruits.getFill() ;
   for (int i = 0 ; i < fill ; ++i){
    if (i < fill && _fruits[i]->getValid() ) {
     _fruits[i]->getAccel().setY(_fruits[i]->getG()) ;


     collidePlan(*_fruits[i],Vector(0,maxHeight), Vector(0,-1) , true) ;

      _fruits[i]->accelerate(dt);

      bool validMove = true ;


      for (int j = 0; j < fill ; j++) {
       if (i != j && j < fill && _fruits[j]->getValid() ) {
        C = _fruits[i]->colliding(*_fruits[j],dt) ;
        if (C < 0) {

         if (_fruits[i]->getFruitType() == _fruits[j]->getFruitType()) {
          int max = std :: max(i,j) ;
          int min = std :: min(i,j) ;
          banList.add(max) ;
          banSize++ ;
          _fruits[max]->setValid(false);

          _fruits[min]->growFruit();
          if (_fruits[min]->getFruitType() >= 12)
          {
           RestartBox box(parentWidget(), true);
           box.exec();
          }

          validMove = false ;
         }else {

                _fruits[i]->collideWith(*_fruits[j],C,dt);
                if ( (collidePlan(*_fruits[i],Vector(0,maxHeight), Vector(0,-1) , false)
                || collidePlan(*_fruits[i],Vector(-maxWidth/2,0), Vector(1,0),false )
                || collidePlan(*_fruits[i],Vector(maxWidth/2,0), Vector(-1,0) , false))
                 && _fruits[i]->getRadius() / _fruits[j]->getRadius() < 1/(1.5) ) {
                       _fruits[i]->getV().setY(_fruits[i]->getV().getY() + 10  );
                }
                float v_scal = sqrt(_fruits[i]->getV().getSquaredLength()) ;
                if (v_scal > dt) {
                      _fruits[i]->getV()= _fruits[i]->getV()* ((std :: min(v_scal,_fruits[i]->getRadius()*100))/v_scal) ;

          }
         }
        }
       }

      }
      if (validMove) {
       _fruits[i]->moveP(_fruits[i]->getV(),dt);
       if (_fruits[i]->getP().getY() < _fruits[i]->getLoseCondition())
       {
        RestartBox box(parentWidget(), false);
        box.exec();
       }
      }

     collidePlan(*_fruits[i],Vector(-maxWidth/2,0), Vector(1,0),true ) ;
     collidePlan(*_fruits[i],Vector(maxWidth/2,0), Vector(-1,0) , true) ;
    }


   }

   for (int i = 0 ; i < banSize ; i++) {
      _fruits.removeIndex(*banList[i]) ;

   }
   banList.resetFill() ;

  }

