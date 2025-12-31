#ifndef FRUIT_H
#define FRUIT_H

#include <math.h>

#include "Vector.h"
#include <queue>
class Fruit
{
public:
    Fruit( const float radius,Vector& velocity , Vector& accel  , Vector& position ) :
    v(velocity) , accel(accel) , p(position),rad(abs(radius))
    {
    }
    Fruit(Vector position) : p(position)
    {

    }
    Fruit(float radius) :  rad(abs(radius))
    {
    }
    Fruit(float radius,float inMass) :  rad(abs(radius)), mass(abs(inMass))
    {
    }
    Fruit() {

    };

    ~Fruit() {

    }



    void accelerate(const float& dt){
        v = v + accel*dt ;
    }

    void animate(const float& dt) {
        moveP(v,dt);
    }

    void moveP(const Vector& args,float dt){
        prevP = p ;
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
    void nonElasticBounce(const Vector& p_exp,const float& dt, Fruit& ball)  {
        v = (p_exp - p)*(1/dt) ;
        Vector d = ball.getP() - p ;
        d = Vector(-d.getY(), d.getX());
        float n = sqrt(d.getSquaredLength()) ;
        d = d*(1/(n)) ;
        Vector ortV = d*(v * d) ;
        v = v + ortV + accel*dt;

    }

    void nonElasticWallBounce(const Vector& p_exp,const float& dt)  {
        v = (p_exp - p)*(1/dt) ;
    }


    bool collides(Fruit& ball) {
        if ( sqrt((p - ball.getP()).getSquaredLength() ) < rad + ball.getRadius() ) {
            return true;
        }
        return false;
    }
    float colliding(Fruit& ball,float dt) {
        return   sqrt((ball.getP() + v*dt - p ).getSquaredLength()) - (rad + ball.getRadius()) ;
    }



    void collideWith(Fruit& ball, const float C,const float& dt) {
        Vector newP = p + v*dt ;
        Vector d =   newP - ball.getP() ;
        float n = sqrt(d.getSquaredLength()) ;
        float sig = ( (1/mass)/( (1/mass) + (1/ball.getMass()) ) )*C ;
        Vector delta = d * (-sig/n) ;
        float dist = (p + delta - prevP).getSquaredLength() - (p - prevP).getSquaredLength() ;
            //if (dist > 0) {
                nonElasticBounce(p + delta,dt,ball);
                p.setCoords(newP + delta ) ;
            //}else {
              //  v = v - v ;
            //}

        //accel.setY(0);
    }

    void setAllowAccel(const bool b) {
        allowAccel = b ;
    }

    int id = 0 ;


private:
    float g = 100;

    float mass = 1;
    Vector accel = Vector(0,g);
    Vector v = Vector(0,0);
    Vector p =  Vector(10,10);;
    float rad = 10;
    bool allowAccel = true ;
    Vector prevP = p ;
};

#endif // FRUIT_H
