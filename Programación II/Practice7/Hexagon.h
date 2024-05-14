//
// Created by pablo on 5/15/2024.
//

#ifndef PRACTICE7_HEXAGON_H
#define PRACTICE7_HEXAGON_H
#include "Figure.h"
#include <cmath>

class Hexagon : public Figure {
public:
    Hexagon(double length): Figure(6, length) {};
    double apotheme(double length) {
        return length/1.15;
    }
    double area() override {
        return (perimeter()* apotheme(sideLength))/2;
    }
};


#endif //PRACTICE7_HEXAGON_H
