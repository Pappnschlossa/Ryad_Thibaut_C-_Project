#ifndef FRUIT_H
#define FRUIT_H

#include <math.h>
#include "Vector.h"

class Fruit
{
public:
    Fruit(const float dt, const float radius,Vector& velocity , Vector& accel  , Vector& position ) :
    v(velocity) , accel(accel) , p(position),rad(radius),dt(dt)
    {

    }
    Fruit(Vector position) : p(position)
    {

    }
    Fruit(float dt) : dt(dt)
    {
    }



    void accelerate(){
        v = v + accel*dt ;
    }

    void moveP(const Vector& args){
        p = p + args * dt ;
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

    void bounce(const Vector& n)  {

        v = v - n * 2 * (v*n) ;
    }
    void nonElasticBounce(const Vector& p_exp)  {
        v = (p_exp - p)*(1/dt) ;
    }
    


private:
    float g = 9.81;
    float dt;
    Vector accel = Vector(0,g);
    Vector v = Vector(0,0);
    Vector p =  Vector(10,10);;
    float rad = 10;

};

#endif // FRUIT_H
