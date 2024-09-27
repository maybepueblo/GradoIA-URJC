#include <iostream>
#include "Hexagon.h"
#include "Triangle.h"
#include "Square.h"
#include "Pentagon.h"


int main() {
    const int SIDE = 5;

    std::cout << std::endl;

    Triangle *t = new Triangle(SIDE);
    std::cout << "Triangle of side " << SIDE << std::endl;
    std::cout << "The area of your triangle is " << t->area() << std::endl;
    std::cout << "The perimeter of your triangle is " << t->perimeter() << std::endl;
    delete t;

    std::cout << std::endl;

    Square *s = new Square(SIDE);
    std::cout << "Square of side " << SIDE << std::endl;
    std::cout << "The area of your square is " << s->area() << std::endl;
    std::cout << "The perimeter of your square is " << s->perimeter() << std::endl;
    delete s;

    std::cout << std::endl;

    Pentagon *p = new Pentagon(SIDE);
    std::cout << "Pentagon of side " << SIDE << std::endl;
    std::cout << "The area of your pentagon is " << p->area() << std::endl;
    std::cout << "The perimeter of your pentagon is " << p->perimeter() << std::endl;
    delete p;

    std::cout << std::endl;

    Hexagon *h = new Hexagon(SIDE);
    std::cout << "Hexagon of side " << SIDE << std::endl;
    std::cout << "The area of your hexagon is " << h->area() << std::endl;
    std::cout << "The perimeter of your hexagon is " << h->perimeter() << std::endl;
    delete h;

    std::cout << std::endl;

    return 0;
}
