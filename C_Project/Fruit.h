#ifndef FRUIT_H
#define FRUIT_H

#include <math.h>
#include "Vector.h"

class Fruit
{
public:
    Fruit(const float radius,Vector& velocity , Vector& accel  , Vector& position,float dt ) :
    v(velocity) , accel(accel) , p(position),rad(radius),dt(dt)
    {

    }
    Fruit(Vector position) : p(position)
    {

    }
    Fruit(float radius) : rad(radius)
    {

    }



    void accelerate(){
        v = v + accel ;
    }

    void moveP(const Vector& args){
        p = p + args ;
    }

    const Vector& getAccel() const {
        return accel ;
    }
    const Vector& getV() const {
        return v ;
    }
    const Vector& getP() const{
        return p ;
    }

    Vector& getAccel() {
        return accel ;
    }
    Vector& getV() {
        return v ;
    }
    Vector& getP(){
        return p ;
    }
    const float getRadius(){
        return rad;
    }

    const float getG() const {
        return g;
    }

    std :: string bounce(Vector n) {

        std :: string s ;
        s +=  v.toString() + " is v \n" ;
        float sc = v*n ;
        v = v - n * 2 * sc ;
        s += n.toString() + " is n \n" ;
        s+= v.toString() + " is v after \n" ;
        return s;

    }

private:
    float g = 1;
    float dt;
    Vector accel = Vector(0,g);
    Vector v = Vector(0,0);
    Vector p =  Vector(10,10);;
    float rad = 10;

};

#endif // FRUIT_H
