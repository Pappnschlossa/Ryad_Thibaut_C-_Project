#ifndef FRUIT_H
#define FRUIT_H

#include <math.h>
#include "Vector.h"

class Fruit
{
public:
    Fruit(const float radius,Vector& velocity , Vector& accel  , Vector& position ) :
    v(velocity) , accel(accel) , p(position),rad(radius)
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
    /**void setV(const Vector& a) {
        v.setCoords(a);
    }
    void setAccel(const Vector& a){
        accel.setCoords(a);
    }
    void setP(const Vector& a){
        p.setCoords(a);
    }*/
    void moveP(const Vector& args){
        p = p + args ;
    }
    /**void changeV(float* u){
        float normV = sqrt(getV()[0]*getV()[0] + getV()[1]*getV()[1]);
        float newV[2] = { normV * u[0], normV * u[1]};
        setV(newV);
    }*/
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

private:
    float g = 1;
    Vector accel = Vector(0,g);
    Vector v = Vector(0,0);
    Vector p =  Vector(10,10);;
    float rad = 10;

};

#endif // FRUIT_H
