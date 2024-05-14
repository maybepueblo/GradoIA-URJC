
> [!NOTE] Propósito de la práctica
> Crear un programa para la gestión de una agenda de personas. Los datos que se guardarán son: nombre, apellidos, teléfono, edad y tipo de contacto. Hemos de abordar esta práctica usando POO para crear una clase llamada *persona* que permita guardar los datos de cada individuo, así como generar, de cada uno, una cadena del estilo siguiente:
> 
> 	Juan;Martín Pérez;917897898;25;TRABAJO
> 
> También es necesario crear una clase *agenda* que disponga de los atributos y métodos necesarios para el siguiente menú, que se implementará en el *main.cpp*, fuera de la clase *agenda*:
> 
> 	1 - Listado de personas
> 	2 - Nueva persona
> 	3 - Borrar persona 
> 	0 - Salir
> 	Elija opción:

Cabe destacar la similitud de estas prácticas con las ya anteriormente realizadas:

- [[Práctica 2 - Agenda]]
- [[Práctica 3 - Agenda con ficheros de texto]]
- [[Práctica 4 - Agenda con ficheros binarios]]
- [[Práctica 5 - TAD]]

Primeramente, creemos las clases requeridas por el ejercicio. Vamos a centrarnos principalmente en la clase *Persona*

#### Class Persona

Antes que nada, vamos a definir un enumerador que nos dará los tres valores que puede tener la variable *tipo de contacto* que son: FAVORITO, CONOCIDO y TRABAJO.

```
typedef enum {
	FAVOURITE, // FAVORITO 
	ACQUAINTANCE, // CONOCIDO
	WORK // TRABAJO
} ContactType;
```

Teniendo nuestro *ContactType* definido, ahora podemos pasar a lo bueno: definir nuestra clase *persona*. Vamos a hacer un apartado privado que cree las variables y luego implementar diversos constructores.

```
class Person {  
private:  
    char name[MAX]{};  
    char surname[MAX]{};  
    char phone[10]{};  
    int age;  
    contactType type;  
public:  
    Person();  
    Person(char *n, char *sn, char *p, int a, contactType t);  
    char *getName();  
    void printPerson();  
};
```

El código aquí es bastante simple, buscamos definir en `private` todo dato que conforma nuestra clase persona, es decir, un nombre, un apellido, un teléfono, etc...

Asimismo, hemos de definir los métodos correspondientes a esta función, donde vemos primeramente dos constructores, el primero siendo el constructor vacío que inicializa los parámetros (que en este caso hemos de señalizar puesto que ya tenemos un constructor más adelante), y posteriormente tenemos otro que nos permite dar valores a nuestras variables guardadas en private a partir de inputs dados. Por último pero no menos importante, definimos `getName()` y `printPerson()` las cuales usaremos más tarde. 

Veamos cómo implementar estas funciones:

```
#include "Person.h"  
#include <cstring>  
#include <iostream>  
  
void Person::printPerson() {  
    std::cout << name << ";" << surname << ";" << phone <<  
    ";" << age << ";" << (type == FAVOURITE ? "FAVOURITE" :  
    (type == ACQUAINTANCE ? "ACQUAINTANCE" : "WORK")) << std::endl;  
}  
  
Person::Person(char *n, char *sn, char *ph, int a, contactType t) {  
    strcpy(this->name, n);  
    strcpy(this->surname, sn);  
    strcpy(this->phone, ph);  
    this->age = a;  
    this->type = t;  
}  
  
Person::Person() {  
    strcpy(this->name, "");  
    strcpy(this->surname, "");  
    strcpy(this->phone, "");  
    this->age = 0;  
    this->type = ACQUAINTANCE;  
}  
  
char *Person::getName() {  
    return this->name;  
}
```

Y aquí está todo el código necesario para implementar absolutamente todas las funciones que conforman nuestra clase Persona. Cabe destacara que en `printPerson()` lo que vemos al final es un if que trata de hallar el tipo de valor que tiene type.

#### Class Agenda

Pasamos a algo un poco más lioso, en este caso, la clase Agenda, que nos va a permitir almacenar contactos, veamos su declaración:

```
class Agenda {  
private:  
    Person *person;  
    int numPeople;  
public:  
    Agenda() : numPeople(0) {}  
    Agenda(int max) {  
        person = new Person[max];  
    }    void printContacts();  
    void addContact();  
    void removeContact();  
};
```

En la práctica, no tenemos mucho pero es importante pararnos a pensar cómo funciona todo. 

Primero, estamos definiendo de forma privada nuestro array de clase persona llamado person, y además estamos definiendo el entero que lleva cuántas personas hay. Cabe destacar que en esta implementación hemos buscado darle un número constante a nuestro array de personas, lo cual obtendremos con los constructores, el cual ya tenemos uno implementado que lo que hace es recibir el tamaño máximo constante que hemos decidido y crea en person un nuevo array de clase persona de tamaño el número dado.

Además, hemos definido funciones como imprimir contactos, añadirlos o eliminarlos. Veamos cómo se implementan:

```
#define MAX 30  
  
void Agenda::printContacts() {  
    for (int i = 0; i < numPeople; ++i) {  
        person[i].printPerson();  
    }    std::cout << "\n" << std::endl;  
}  
  
void Agenda::addContact() {  
    if (numPeople >= 5) {  
        std::cout << "The agenda is full" << std::endl;  
        return;  
    }  
    char name[MAX];  
    char surname[MAX];  
    char phone[10];  
    int age;  
    contactType type;  
    int t_int;  
  
    std::cout << "Give me their name:";  
    std::cin >> name;  
  
    std::cout << "Give me their surname:";  
    std::cin >> surname;  
  
    std::cout << "Give me their phone:";  
    std::cin >> phone;  
  
    std::cout << "Give me their age:";  
    std::cin >> age;  
  
    std::cout << "Give me their name:";  
    std::cin >> t_int;  
  
    type = static_cast<contactType>(t_int);  
  
    std::cout << "Contact added successfully" << std::endl;  
  
    person[numPeople++] = Person(name, surname, phone, age, type);  
}  
  
void Agenda::removeContact() {  
    if (numPeople <= 0) {  
        std::cout << "There are no contacts to remove" << std::endl;  
    }  
    char name[MAX];  
  
    std::cout << "Give me the name of the contact to delete:"; std::cin >> name;  
  
    for (int i = 0; i < numPeople; ++i) {  
        if (strcmp(person[i].getName(), name) == 0) {  
            for (int j = i; j < numPeople-1; ++j) {  
                person[j] = person[j+1];  
            }            std::cout << "Contact successfully removed" << std::endl;  
            --numPeople;  
            return;  
        }    }    std::cout << "Contact not found" << std::endl;  
  
}
```

Ahora sí. Es mejor que se miren cada función que he ido declarando ya que explicarlas una por una sería un proceso un poco engorroso, pero creo que se entienden bien.

OJO! Es importante decir una cosa, aunque tengamos un teléfono de 9 dígitos, tenemos que definir el tamaño del array que lo contiene como mínimo un número por encima de 9, es decir, 10. Porque al usar el strcpy, C++ nos copia el string y necesita un hueco más para dejar el carácter nulo, cosa que si no le dejamos, nos corrompe toda la salida. Quien avisa no es traidor (me pasó y estuve horas para hallar el fallo aunque sea esta bobería)

El sistema de eliminar personas podría ser mejor también, pero para esta versión puntual hecha meramente por la práctica, he decidido hacer un sistema que vaya por nombre, y que borre el primer nombre que encuentre del que le hayas dado. Otra opción sería directamente irte al apellido, allá ustedes.

#### Menú principal

Pues ya estaría, queda cohesionar todo bien en un main que resalte nuestro programa, vamos a hacerlo:

```
#include "Agenda.h"  
  
int main() {  
    /*  
    Person person("Juan", "Garcia", "619222222", 18, FAVOURITE);    person.printPerson();    */    const int MAX_CONTACTS = 5;  
  
    Agenda agenda = Agenda(MAX_CONTACTS);  
    int choice;  
  
    do {  
        std::cout << " --- MENU --- " << std::endl;  
        std::cout << " 1 - Contacts " << std::endl;  
        std::cout << " 2 - New contact " << std::endl;  
        std::cout << " 3 - Delete contact " << std::endl;  
        std::cout << " 0 - Exit " << std::endl;  
  
        std::cout << "Choose an option: "; std::cin >> choice;  
        std::cout << std::endl;  
  
        switch (choice) {  
            case 1:  
                agenda.printContacts();  
                break;  
            case 2:  
                agenda.addContact();  
                break;  
            case 3:  
                agenda.removeContact();  
                break;  
            case 0:  
                std::cout << "See you next time!" << std::endl;  
                break;  
            default:  
                std::cout << "ERROR. No choice given" << std::endl;  
        }  
    } while (choice != 0);  
  
    return 0;  
}
```

Y ya estaría :-)

Poco más se necesita, gracias por leer!

