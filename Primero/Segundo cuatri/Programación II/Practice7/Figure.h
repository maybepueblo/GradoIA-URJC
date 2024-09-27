//
// Created by pablo on 5/14/2024.
//

#ifndef PRACTICE7_FIGURE_H
#define PRACTICE7_FIGURE_H

class Figure {
protected:
    double numSides;
    double sideLength;
public:
    Figure(int sides, double value) : numSides(sides), sideLength(value) {} ;
    virtual double area() = 0;
    virtual double perimeter() {
        return numSides * sideLength;
    };
};

#endif //PRACTICE7_FIGURE_H
