>[!NOTE] Propósito de la práctica
>Se busca en esta ocasión enseñar un caso de herencia, donde tenemos que a partir de una clase inicial llamada Figura, partir para crear nuevas derivadas como un triángulo, un cuadrado o más.
>
>Estas nuevas clases podrán implementar el área individual a cada clase así como otros cálculos relevantes.

Sin más dilación, veamos todos los apartados que tenemos que hacer, esta práctica es bastante breve:

- `Figura` -> Clase base.
	- `Triangle`
	- `Square`
	- `Pentagon`
	- `Hexagon`

#### Figura

En este caso, figura contendrá la implementación estándar del cálculo del perímetro, ya que es igual para todas las figuras, siendo este la multiplicación del tamaño del lado por el número de lados de la figura que deseemos. 

Sin embargo, no podremos implementar la función que nos da el area, por lo cual habremos de crear a figura como una clase abstracta.

```
class Figure {  
protected:  
    double numSides;  
    double sideLength;  
public:  
    Figure(int sides, double value) : numSides(sides), sideLength(value) {} ;  
    virtual double area() = 0;  
    virtual double perimeter() {  
        return numSides * sideLength;  
    };};
```

Como podemos ver, logramos implementar el perímetro, pero no el área. También se observa que tenemos declaradas ya en un protected (que también se hereda) el número de lados de dicha figura y el tamaño del lado, que son pasados a una constructora que asigna los valores. 

Empecemos entonces a crear derivadas.

#### Triángulo

```
class Triangle : public Figure {  
public:  
    Triangle(double length) : Figure(3, length) {};  
    double area() override {  
        return (sqrt(3)/4)*pow(sideLength, 2);  
    }};
```

Sí, así de fácil es. Como se puede observar, simplemente hemos de definir un triángulo del tamaño que nos hallan dado, con lo cual sabiendo el tamaño que tiene la figura pues iniciamos en Figure, nuestra clase base, los valores de 3 lados y el tamaño dado que tiene cada lado individual. 

Asimismo, hacemos un `override` y implementamos el area originalmente declarado en nuestra clase base, devolviendo directamente el valor de tipo double que queremos, el área.

#### Cuadrado

```
class Square : public Figure {  
public:  
    Square(double length) : Figure(4, length) {}  
    double area() override {  
        return pow(sideLength, 2);  
    }};
```

Nuevamente, esto se repite, no hay nada que valga la pena comentar salvo que aquí estoy usando pow(base, exponente), que viene incluido en la librería `cmath`. 

#### Pentágono

```
class Pentagon : public Figure {  
public:  
    Pentagon(double length) : Figure(5, length) {}  
    double apotheme(double length) {  
        return length/1.45;  
    }    double area() override {  
        return (perimeter()* apotheme(sideLength))/2;  
    }};
```

En este caso, como ahora tenemos que hallar la apotema, sí es necesario definir la forma de hallarla dentro de esta clase, ya que no es común a todas nuestras funciones, por lo demás, todo se mantiene exactamente igual.

#### Hexágono

```
class Hexagon : public Figure {  
public:  
    Hexagon(double length): Figure(6, length) {};  
    double apotheme(double length) {  
        return length/1.15;  
    }    double area() override {  
        return (perimeter()* apotheme(sideLength))/2;  
    }};
```

Y aquí de nuevo, volvemos a necesitar la apotema así que tenemos que hacer un par de pasos extra pero poca cosa más. 

#### Menú principal

Como se puede ver, esta práctica no es muy enrevesada, veamos cómo se amalgama todo en un main.cpp:

```
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
```

Gracias por leer ;)