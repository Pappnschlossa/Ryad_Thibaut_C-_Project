#ifndef FRUIT_H
#define FRUIT_H

#include <math.h>
#include "Vector.h"

class Fruit
{
public:
    Fruit(const float dt, const float radius,Vector& velocity , Vector& accel  , Vector& position ) :
    v(velocity) , accel(accel) , p(position),rad(abs(radius)),dt(dt)
    {

    }
    Fruit(Vector position) : p(position)
    {

    }
    Fruit(float dt) : dt(dt)
    {
    }
    Fruit(float dt,float radius) : dt(dt), rad(abs(radius))
    {
    }
    Fruit(float dt,float radius,float inMass) : dt(dt), rad(abs(radius)), mass(abs(inMass))
    {
    }
    Fruit() {

    };



    void accelerate(){
        v = v + accel*dt ;
    }

    void animate() {
        moveP(v);
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
    float getMass() {
        return mass ;
    }
    void bounce(const Vector& n)  {

        v = v - n * 2 * (v*n) ;
    }
    void nonElasticBounce(const Vector& p_exp)  {
        v = (p_exp - p)*(1/dt) ;
    }



    bool collides(Fruit& ball) {
        if ( sqrt((p - ball.getP()).getSquaredLength() ) < rad + ball.getRadius() ) {
            return true;
        }
        return false;
    }
    float colliding(Fruit& ball) {
        return   sqrt((ball.getP() - p ).getSquaredLength()) - (rad + ball.getRadius()) ;
    }


    void collideWith(Fruit& ball, const float C) {
        Vector d =  p - ball.getP() ;
        float n = sqrt(d.getSquaredLength()) ;
        float sig = ((1/mass)/(1/mass + 1/ball.getMass()))*C ;
        Vector delta = d * (-sig/n) ;
        nonElasticBounce(p + delta);
        //p.setCoords(p + delta ) ;
        animate();
    }





private:
    float g = 20000;
    float dt;
    float mass = 1;
    Vector accel = Vector(0,g);
    Vector v = Vector(0,0);
    Vector p =  Vector(10,10);;
    float rad = 10;


};

#endif // FRUIT_H
