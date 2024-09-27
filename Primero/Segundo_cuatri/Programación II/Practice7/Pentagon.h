//
// Created by pablo on 5/15/2024.
//

#ifndef PRACTICE7_PENTAGON_H
#define PRACTICE7_PENTAGON_H
#include "Figure.h"

class Pentagon : public Figure {
public:
    Pentagon(double length) : Figure(5, length) {}
    double apotheme(double length) {
        return length/1.45;
    }
    double area() override {
        return (perimeter()* apotheme(sideLength))/2;
    }
};



#endif //PRACTICE7_PENTAGON_H
