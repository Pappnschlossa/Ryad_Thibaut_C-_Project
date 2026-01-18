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
    Fruit(int t) :  type(1)
    {
        for (int i = 1; i < t; i++) {
            growFruit();
        }
    }
    Fruit(float radius,float inMass) :  rad(abs(radius)), mass(abs(inMass))
    {
    }
    Fruit() {

    };

    ~Fruit() {
       // std :: cout << " Fruit of id " << id << " at adress "  << this << " was destroyed " << std::endl ;
    }



    void accelerate(const float& dt){
        v = v + accel;
    }

    void animate(const float& dt) {
        moveP(v,dt);
    }

    void moveP(const Vector& args,float dt){
        //prevP = p ;
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

    std :: string print() {
        return  "Fruit of id "  +  std::to_string(id)  + " and radius " + std::to_string(rad) +  "\n" ;
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
    void setRadius(float r) {
        rad = r ;
    }
    int getFruitType() {
        return type;
    }
    void growFruit() {
        type += 1;
        loseCondition += static_cast<int>(rad);
        rad = rad*1.2;
        loseCondition -= static_cast<int>(rad);
        mass = mass + 10 ;
        if (type == 12)
        {
            std::cout << "Bien joué !" << std::endl;
        }
    }
    float getSpawnX() {
        return spawnX;
    }
    void setSpawnX(float value) {
        spawnX = value;
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
        v = (p_exp - p)*(1/dt) + accel*(1/dt) ;

    }

    void nonElasticWallBounce(const Vector& p_exp,const float& dt)  {
        v = (p_exp - p);
    }


    float colliding(Fruit& ball,float dt) {
        return   sqrt((ball.getP() - v*dt - p ).getSquaredLength()) - (rad + ball.getRadius()) ;
    }



    void collideWith(Fruit& ball, const float C,const float& dt) {
        if ( (ball.getP().getY() + ball.getRadius() - p.getY() - rad  >= - dt )) {
            Vector newP = p + v*dt ;
            Vector d =   newP - ball.getP() ;
            float n = sqrt(d.getSquaredLength()) ;

            float sig = ( (1/mass)/( (1/mass) + (1/ball.getMass()) ) )*C ;
            Vector delta = d * (-sig/n) ;

            nonElasticBounce(p + delta,dt,ball);
            p.setCoords(newP + delta ) ;
        }
    }

    void setAllowAccel(const bool b) {
        allowAccel = b ;
    }

    int id = 0 ;

    void setValid(bool b) {
        valid = b ;
    }

    bool getValid() const {
        return valid ;
    }

    void setLoseCondition(float f)
    {
        loseCondition = static_cast<int>(f);
    }

    int getLoseCondition() const
    {
        return loseCondition;
    }

private:
    float g = 30;

    bool valid = true;


    float mass = 100;
    Vector accel = Vector(0,g);
    Vector v = Vector(0,0);
    Vector p =  Vector(10,10);;
    float rad = 25;
    int type = 1;
    float spawnX = 0.0F;
    bool allowAccel = true ;
    int loseCondition = -10000;

};

#endif // FRUIT_H
