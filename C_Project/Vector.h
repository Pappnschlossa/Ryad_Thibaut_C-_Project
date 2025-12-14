//
// Created by ryadg on 07/12/2025.
//

#ifndef C_PROJECT_VECTOR_H
#define C_PROJECT_VECTOR_H
#include <iostream>
#include <math.h>
#include <qstring.h>



class Vector {
public:
    Vector(float x, float y) : _x(x) , _y(y) {}
    Vector(Vector& v) : _x(v.getX()), _y(v.getY()) {}

    ~Vector(){}


    const float getX() const {
        return _x;
    }
    const float getY() const {
        return _y;
    }


    void setX(const float x) {
        _x = x ;
        setSquaredLength();
    }

    void setY(const float y) {
        _y = y ;
        setSquaredLength();
    }

    void setCoords(const Vector& v) {
        _x = v.getX();
        _y = v.getY();
        setSquaredLength();
    }
    void setCoords(const float x ,const float y) {
        _x = x;
        _y = y;
        setSquaredLength();
    }

     void setSquaredLength()  {
        norm = (*this)*(*this) ;

    }

    float getSquaredLength() const {
        return  (*this)*(*this) ;
    }



    inline float operator *(const Vector & v) const { //dot product will be *
        return _x*v.getX() + _y*v.getY();
    }

    inline Vector operator *(const float scalar) const { //dot product will be *
        return {_x*scalar , _y*scalar};
    }

    //inline float Norm(const Vector& v) {return math.sqrt( v.x*v.x + v.y*v.y + v.z*v.z);}


    inline Vector operator+(const Vector& v1) {
        return {_x + v1.getX(), _y + v1.getY() };
    }

    inline Vector operator-(const Vector& v1) const {
        return {_x - v1.getX(), _y - v1.getY() };
    }


    inline std::ostream& operator<<(std::ostream& out) {
        return out << " " << _x << " " << _y  << "\n";
    }

    std:: string  toString() {
        return "Vector(" + std::to_string(_x) + "," +  std::to_string(_y) + ")" ;
    }
    bool isNull() {
        if (_x == 0 && _y == 0) {
            return true;
        }else {
            return false;
        }
    }



private:
    float _x;
    float _y;
    float norm ;
};

inline std::ostream& operator<<(std::ostream& out, const Vector& v) {
    return out << "Vector coordinates : " << v.getX() << " " << v.getY() <<  "\n";
}


#endif //C_PROJECT_VECTOR_H