#ifndef FRUIT_H
#define FRUIT_H

#include <math.h>


class Fruit
{
public:
    Fruit(const float radius){
        float def[2] = {0,1};
        setAccel(def);
        def[1] =  0 ;
        def[0] = 5 ;
        setV(def);
        rad = radius;
    }



    void accelerate(){
        v[0] += accel[0] ;
        v[1] += accel[1] ;
    }
    void setV(const float* args){
        v[0] = args[0];
        v[1] = args[1];
    }
    void setAccel(const float* args){
        accel[0] = args[0];
        accel[1] = args[1];
    }
    void setP(const float* args){
        p[0] = args[0];
        p[1] = args[1];
    }
    void moveP(const float* args){
        p[0] += args[0];
        p[1] += args[1];
    }
    void changeV(float* u){
        float normV = sqrt(getV()[0]*getV()[0] + getV()[1]*getV()[1]);
        float newV[2] = { normV * u[0], normV * u[1]};
        setV(newV);
    }
    float normV (){
        return sqrt(getV()[0]*getV()[0] + getV()[1]*getV()[1]); ;
    }
    const float * getV(){
        return v ;
    }
    const float *getP(){
        return p ;
    }
    const float getRadius(){
        return rad;
    }

private:
    float* accel = new float[2];
    float* v = new float[2];
    float* p = new float[2];
    float rad;
};

#endif // FRUIT_H
