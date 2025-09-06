**Introducción a C++**

[[Paradigmas de programación]]


> [!NOTE] C++
> Fue desarrollado en 1979. Es una evolución de C para incluir características de programación orientada a objetos (POO). Es un lenguaje híbrido ya que permite combinar POO y programación imperativa. Cabe destacar que todos los códigos de C funcionan en C++ siempre que se tengan las librerías adecuadas.

Para más información sobre C++ véase [[Anexo C++]]
#### Programación Orientada a Objetos (POO)

- **Clases y objetos**
	- **Clases** -> definición de todos los elementos comunes de los objetos de dicha clase. Por ejemplo, una clase es el concepto general, como la definición de una persona.
		- Miembros de la clase: atributos (variables y ctes de dicha clase) y métodos (operaciones / funciones)
	- **Objetos** -> instancia de una determinada clase. Un ejemplo de esto sería una simple persona de la clase que habíamos definida antes conocida como personas.

- **Herencia**

- **Polimorfismo**

#### TAD vs Clases

- Un TAD define un tipo (o tipos) de datos y sus operaciones asociadas.
	Las operaciones reciben como parámetros los elementos sobre los que operan. 

- Mientras tanto, una clase es un tipo de datos que incluye diferentes miembros: **atributos** y operaciones.
	Las operaciones (**métodos**) pueden utilizar los atributos del objeto que las invoca usando el puntero *this*, o bien operar sobre parámetros de entrada.

Veamos estas diferencias plasmadas en el código:

- TAD

```
// Declaración de una variable estática
TadFecha miFecha = creaFechaEstatico(22, 12, 2000);
imprimeFecha(&miFecha);

// Declaración de variable dinámica
TadFecha *miFecha2 = creaFecha(22, 12, 2000);
imprimeFecha(miFecha2);
```

- POO

```
// Declaración de objeto estático
Fecha objFecha = Fecha(22, 12, 2000);
objFecha.imprimeFecha();

// Declaración de objeto dinámico
Fecha *objFecha2 = new Fecha(22,12,2000);
objFecha2->imprimeFecha();
```

#### Clases en C++

Una clase nos define las características comunes a todos los objetos:
- Los **atributos** son variables que se definen dentro de los objetos.
- Los **métodos** son funciones definidas en la clase.
- Atributos y métodos son **miembros** de la clase.
- En C++ se declaran con la palabra reservada *class*
- Existen diferentes niveles de acceso a miembros de una clase en C++:
	- Público (public): Los miembros públicos son accesibles desde los lugares donde el objeto es accesible.
	- Privado (private): Los miembros privados son accesibles desde miembros de la clase pero no desde el exterior ni desde clases miembros de clases derivadas.
	- Protegido (protected): Se trata de miembros privados accesibles desde clases derivadas.

Veamos cómo declarar una clase en C++:

```
class Fecha {
	public:
		// Constructor
		Fecha(int dia, int mes, int anyo);
		// Accesores
		int dameDia();
		int dameMes();
		int dameAnyo();
		// Mutadores
		void ponDia(int dia);
		void ponMes(int mes);
		void ponAnyo(int anyo);
		// Otros métodos
		void imprimeFecha();
	private:
		int dia;
		int mes;
		int anyo;
};
```

- Es importante recalcar que los métodos públicos se pueden usar donde queramos siempre que el objeto sea accesible.

- El método *Fecha* es el constructor que tiene características particulares.

- Zona privada donde se encuentran los atributos

- La declaración suele estar en un fichero cabecera (.h)

- Si una función se implementa en la declaración se considera "inline" y su código se replica en tiempo de complicación.
	Acelera la ejecución pero incrementa el tamaño del ejecutable, se recomienda su uso en funciones muy cortas.

Ahora hemos de implementar la clase, veamos cómo se hace:

```
#include "Fecha.h"
#include <iostream>

Fecha::Fecha(int dia, int mes, int anyo) {
	this->dia = dia;
	this->mes = mes;
	this->anyo = anyo;
}

int Fecha::dameDia() {
	return this->dia;
}

void Fecha::imprimeFecha() {
	std::cout << this->dameDia() << "/" 
			  << this ->dameMes() << "/" << this->dameAnyo();
}


```
##### Constructores

Métodos que crean los objetos.

###### Características de los constructores

- Tienen el mismo nombre de la clase a la que pertenecen
- Han de ser públicos
- No tienen *return* ni tipo de retorno porque devuelven un objeto de la clase a la que pertenecen.
- Puede haber tantos constructores como se desee, pero deben de tener parámetros de entrada diferentes. Esto se conoce como **sobrecarga de métodos**.
- No se heredan.

Si una clase carece de constructor, el compilador genera uno sin parámetros para que los objetos se puedan instanciar.
	En estos casos los atributos contienen valores no controlados.

Si se crea un constructor sin argumentos este se invoca en declaraciones sin asignación.

En C++ todos los elementos, incluso de tipos básicos como *int*, *float* o *char* son objetos, por lo que tienen constructor. 

Es posible **inicializar miembros** de la clase en la cabecera del constructor, aunque esto obliga a que la inicialización sea *inline*. El siguiente código de la implementación de la clase:

```
Fecha::Fecha(int d, int m, int a) {
	dia = d;
	mes = m;
	anyo = a;
}
```

Es equivalente al siguiente con inicializaciones:

```
Fecha(int d, int m, int a) : dia(d), mes(m), anyo(a) {}
```

##### Destructores

Métodos que se ejecutan cuando un objeto deja de usarse.
	- Invocación automática en objetos estáticos al salir del ámbito de la declaración.
	- Si el objeto se creó con el *new*, el destructor se invoca en el *delete*, no hay invocación automática.

Se utilizan para liberar los recursos ocupados por el objeto y tienen las siguientes características:

- Tienen el mismo nombre de la clase a la que pertenecen pero con el símbolo ~ delante.
- Deben ser públicos.
- No tienen parámetros.
- No tienen ni return ni tipo de retorno.
- No se pueden sobrecargar.
- No se heredan.
#### Herencia

La herencia es la capacidad de crear una clase diferente reutilizando los datos de una clase anteriormente utilizada. Así, definimos herencias cuando queremos crear una clase derivada que hereda de otra clase base. 

Una clase definida a través de herencia se denomina **clase derivada** mientras que la clase a partir de la que se deriva es la llamada **clase base**.

La existencia de varias clases relacionadas a través de herencia define una jerarquía de clases.

La herencia modela la relación "es-un". Esto significa que una clase hija es una extensión o especialización de la clase padre. Estas clases hijas pueden agregar nuevos atributos y métodos o sobrescribir los existentes de la clase padre (**redefinición de métodos**).
	Se extiende la funcionalidad de la clase base para adaptarse a las necesidades específicas de la clase hija.

Al heredar en C++ se pueden definir dos tipos de acceso a la clase base:

- `public` conserva el tipo de acceso a los métodos de la clase base
- `private` hace que los métodos heredados de la clase sean privados.
- Si no hay método indicado, se usa `private`. 

La herencia se indica en la declaración de la clase derivada, listando las clases de quienes hereda:

```
// Clase base
class PersonaUniversidad {
	protected:
		static const int TAM_PALABRA = 30;
		char nombre[TAM_PALABRA];
		char telefono[TAM_PALABRA];
		char email[TAM_PALABRA];
	public:
		void obtenerTarjetaUniversidad();
};

// Clase derivada
class Estudiante : public PersonaUniversidad {
	private:
		char numeroEstudiante[TAM_PALABRA];
	public:
		float obtenerMediaExpediente();
		int obtenerCreditosSuperados();
};
```

##### Constructores y destructores en herencia

En C++ antes de ejecutar el constructor de una clase derivada se ejecuta el constructor de la clase base. Para usarlos, es necesario invocarlos como inicializadores en la declaración de la clase.

Se pueden inicializar varios elementos usando comas. Otros objetos miembro se inicializan con su nombre, no con el de la clase.
	Las llamadas a constructores se han de indicar antes que la inicializaciones de los parámetros.

```
// Clase derivada
class Estudiante : public PersonaUniversidad {
	private:
		char numeroEstudiante[TAM_PALABRA];
		Mentor miMentor;
	public:
		Estudiante();
		Estudiante(char *nombre, char *numeroEstudiante) :                               PersonaUniversidad(nombre), miMentor(nombre) {
			strcpy(this->numeroEstudiante, numeroEstudiante)
		}
		float obtenerMediaExpediente();
		int obtenerCreditosSuperados();
};
```

En la destrucción de un objeto de una clase derivada primero invocamos el destructor de la clase derivada, si existen objetos miembro se invoca a sus destructores y finalmente se invoca al destructor de la clase base o clases base. Si la clase base es derivada, se repite recursivamente.

#### Redefinición de métodos

Consiste en crear una nueva implementación de un método ya implementado en la clase base.

- El método de la clase base se sobrescribe (override)
- Si es necesario se puede invocar al método de la clase base usando el nombre de la clase como prefijo.
	- objeto.clase_base::método;

Ejemplo donde cada clase tiene su implementación de un saludo:

```
// Declaración de varios objetos
PersonaUniversidad personaUniversidad = PersonaUniversidad("Paco");
Estudiante estudiante = Estudiante("Ana", "1234");
Profesor profesor = Profesor("Juan");

// Cada objeto invoca a su método
personaUniversidad.saludo();
estudiante.saludo();
profesor.saludo();

// Invoca al método de la clase base
profesor.PersonaUniversidad::saludo();
```

#### Redefinición y sobrecarga

Un método se sobrecarga cuando se definen varias implementaciones con diferentes parámetros para el mismo nombre de método. Ejemplo donde *sumar* está sobrecargado:

```
class Base {
	public:
		void sumar() {std::cout <<"Sumando" << std::endl; }
		void sumar(int valor) {std::cout << "Sumando " << valor << std::endl; }
}
```

En C++ al redefinir un método en la clase derivada se pierde el acceso a todos los métodos sobrecargados.

#### Polimorfismo

La herencia nos permite llegar hasta aquí, pudiendo concebir un objeto de una clase derivada que se trata como de su clase base, lo que permite escribir código genérico que funcione con diferentes tipos de objetos.

En C++ por defecto solamente podemos acceder a los miembros de la clase base, los de las derivadas son inaccesibles desde la variable polimórfica.

```
// Polimorfismo 
PersonaUniversidad p = Estudiante("Ana","1234"); 
PersonaUniversidad p2 = Profesor("Juan"); 
PersonaUniversidad *p3 = new Estudiante("Carlos","5678"); 

p.saludo(); 
p2.saludo(); 
p3->saludo();
```

Estos saludos serían todos iguales, ya que no podemos acceder a la implementación específica de cada clase derivada.
#### Funciones virtuales

Para que la invocación use la implementación de la clase derivada, hemos de definir el método como virtual en la clase base y la invocación se tiene que hacer con punteros o referencias.

La propiedad virtual se hereda siendo virtual en las clases derivadas. Y si en una clase hay funciones virtuales el destructor ha de serlo también.

Sin embargo, los constructores no pueden ser virtuales pero sí pueden definir métodos virtuales para clonar soluciones. 

Veamos cómo afectaría esto a nuestro código dado en el apartado anterior:

```
PersonaUniversidad p = Estudiante("Ana","1234"); 
PersonaUniversidad p2 = Profesor("Juan"); 
PersonaUniversidad *p3 = new Estudiante("Carlos","5678"); 
p.saludo(); 
p2.saludo(); 
p3->saludo()
```

En este caso, p y p2 nos devolverían los saludos provenientes de la clase base, pero sin embargo p3 nos devuelve un saludo personalizado, ya que ahora tenemos en nuestra clase PersonaUniversidad definido de forma virtual este método saludo, lo que conlleva que para usarlo con la implementación particular de cada clase derivada, hemos de apuntar con un puntero, cosa que hacemos en p3 pero no en p2 o en p.

#### Clases abstractas

Una función virtual pura es lo que decimos no tiene implementación, ya que se implementa en las clases derivadas. Se declara asignándole cero:

```
virtual tipo nombreDeLaFuncion(parametros) = 0;
```

En C++ una clase es abstracta desde que se haya declarado AL MENOS una función virtual pura. Estas clases se usan para definir comportamientos que se implementan en sus clases derivadas particulares.

En C++ pueden incluir también métodos no virtuales y atributos. 

Tienen las siguientes propiedades:

- Son clases que no pueden ser instanciadas directamente o lo que es lo mismo, no podemos crear objetos de estas clases.
- Si las funciones virtuales no se implementan en una de las clases derivadas, la clase derivada será también abstracta