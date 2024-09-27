//
// Created by pablo on 5/14/2024.
//

#ifndef PRACTICE7_TRIANGLE_H
#define PRACTICE7_TRIANGLE_H
#include "Figure.h"
#include <cmath>


class Triangle : public Figure {
public:
    Triangle(double length) : Figure(3, length) {};
    double area() override {
        return (sqrt(3)/4)*pow(sideLength, 2);
    }
};


#endif //PRACTICE7_TRIANGLE_H
