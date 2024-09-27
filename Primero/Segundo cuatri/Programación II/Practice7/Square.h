//
// Created by pablo on 5/15/2024.
//

#ifndef PRACTICE7_SQUARE_H
#define PRACTICE7_SQUARE_H
#include "Figure.h"
#include <cmath>

class Square : public Figure {
public:
    Square(double length) : Figure(4, length) {}
    double area() override {
        return pow(sideLength, 2);
    }
};


#endif //PRACTICE7_SQUARE_H
