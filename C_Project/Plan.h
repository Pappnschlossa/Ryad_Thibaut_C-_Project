//
// Created by ryadg on 09/12/2025.
//

#ifndef C_PROJECT_PLAN_H
#define C_PROJECT_PLAN_H
#include "Vector.h"


class Plan {
public:
    Plan(Vector& defP,Vector& normalV):defPoint(defP) , normalVector(normalV) {

    }
    ~Plan();
private:
    Vector defPoint;
    Vector normalVector;
};


#endif //C_PROJECT_PLAN_H