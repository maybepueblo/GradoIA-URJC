## C a C++
Muy similares, tenemos el mismo tipo de comentarios, la misma forma de declarar literales y variables, sentencias de control, así como bucles. 
 
**¿Cómo funciona el siguiente código?**
```c
void increment(int n) {
	n+=4;
}

int main() {
	int a{3};

	increment(a);
	std::cout<<a<<"\n";

	return 0;
}
```
Lo que pasa es que hemos declarado en memoria la variable a, para luego pasarle a la función increment este valor que declaramos, incrementando en 4 al 3. Llegamos al main y imprimimos la variable "a", que sería simplemente imprimir 3, porque en C no existe paso por valor/referencia. 

Para simular que esto existe, tenemos que usar punteros. Cambiando el código a tal forma que:
```c
void increment(int *n) {
	*n+=4;
}

int main() {
	int a{3};

	increment(&a);
	std::cout<<a<<"\n";

	return 0;
}
```

Esto sería en C, pero en C++ sí existe el paso por referencia:
```cpp
void increment(int& n) {
	n+=4;
}

int main() {
	int a{3};

	increment(a);
	std::cout<<a<<"\n";

	return 0;
}
```
La única complicación que tiene es que si solo vemos el main, no podemos saber qué hace esa función en cuestión, cosa que sí podríamos haber hecho en C.
### Particularidades de Cpp
#### Auto, const y constexpr
En el caso auto nos permite deducir el tipo automáticamente:
```cpp
auto a = 3; // int 
auto b {2u}; // unsigned int
auto c {3.5f}; // float
auto d = 4.5; // double
auto e = 42UL; // unsigned long
auto f = std::numbers::pi; // double
auto g = {3}; // list of int
auto h{}; 
auto i = {1, 2, 3}; // list of int
auto j = {3.1415}; // list of double
auto k{1, 2, 3}; 
const auto m{3}; // int
```
Es importante hacer constante todo aquello no variable, en otros lenguajes viene por defecto, pero para cpp es una buena práctica es tanto asignar const cuando se debe así como poner auto cuando sea posible.

Constexpr es para componer expresiones constantes en tiempo de compilación, lo que quiere decir que cuando cree una variable
## POO
Es común que datos y funciones estén relacionados. La programación orientada a objetos facilita un empaque que está compuesto de muchos tipos de datos internos, los cuales podrán tener operaciones exclusivas para dichos contenedores (los llamaremos clases). 

Las structs en C++ pueden tener métodos, cosa que en C no es posible. Tanto class como struct crean estas llamadas clases. Difieren en la visibilidad por defecto de sus atributos y métodos.

En las clases queremos limitar los atributos, los cuales hemos de definir, si todo fuese público, volvemos al struct. En una clase no debería haber atributos públicos. Puede haber constantes privadas, pero lo normal son públicas. 

A la hora de crear structs, podemos encontrar este caso:
```cpp
struct Punto{ 
	double x, y, z; 
	Punto() { 
		x = 0.5; 
		y = 0.2; 
		z = 4.2; 
	} 
	
	Punto(double x, double y, double z) { 
		x = x; 
		y = y; 
		z = z; 
	} 
};
```
Aquí tenemos el problema de: ¿A qué x nos referimos?

Aquellos de la vieja escuela usarían esta forma:
```cpp
struct Punto{ 
	double x, y, z; 
	Punto() { 
		x = 0.5; 
		y = 0.2; 
		z = 4.2; 
	} 
	
	Punto(double x, double y, double z) { 
		m_x = x; 
		m_y = y; 
		m_z = z; 
	} 
};
```
Pero esto es poco eficiente ya que tendría que estar poniendo un m_ delante de toda vaariable, lo que lo hace un poco más tedioso.

Otra forma de resolver este problema y la preferida del profesor es:
```cpp
struct Punto{ 
	double x, y, z; 
	Punto() { 
		x = 0.5; 
		y = 0.2; 
		z = 4.2; 
	} 
	
	Punto(double x, double y, double z) { 
		this->x = x; 
		this->y = y; 
		this->z = z; 
	} 
};
```
Donde se reciben parámetros para inicializar la clase de forma correcta.

Otra forma es:
```cpp
struct Punto{ 
	double x, y, z; 
	Punto() { 
		x = 0.5; 
		y = 0.2; 
		z = 4.2; 
	} 
	
	Punto(double x, double y, double z): x(x), y(y), z(z) {}
};
```
Esta lista de inicializadores es la más recomendable de usar cuando sea posible.

No obstante, es mejor no implementar un constructor si no es necesario, es lo que llamamos la regla del cero (Rule of Zero)
```cpp
struct Punto{ 
	double x = 0.5;
	double y = 0.2;
	double z = 4.2;
};

...

Punto p{}
Punto q;
Punto r{1, 2, 3}
```

## Genericidad
Los `templates` nos permiten definir clases con tipos diferentes, por lo que lo usamos para hacer estructuras genéricas. Veamos un ejemplo:

```cpp
template <typename T>

struct Punto {
	T x;
	T y;
	T z;
}

Punto<int> pint{1, 2, 3};
Punto<double> pdouble{1.0, 2.0, 3.0};
```
### Punteros inteligentes
Cpp dispone de punteros que gestionen la memoria a la que apuntan automáticamente. Veamos distintos tipos:
- `std::shared_ptr` -> Contador de referencias
	- El último que quede de estos que sea dueño de un objeto es destruido. 
	- El último que está adueñado de un objeto es asignado a otro puntero.
- `std::unique_ptr` -> Puntero exclusivo
	- Se encarga de otro objeto con un puntero y se deshace de este objeto cuando el puntero único desaparece de la vista del programa.
### Repaso listas
- **Array** `std::array`
	- Contenedor estático que almacena elementos en secuencia contigua en memoria.
	- Se debe conocer su tamaño en tiempo de compilación
	- Proporciona acceso rápido a elementos mediante índices
	- No permite la inserción o eliminación de elementos después de su creación.
- **Lista** `std::list`
	- Lista doblemente enlazada
	- Permite inserción y eliminación eficiente de elementos
- **Queue** `std::queue`
	- Cola FIFO
	- Inserción por final y eliminación por cabecera
	- No permite acceso directo a elementos que no estén en el frente o al final
- **Vector** `std::vector`
	- Array dinámico configurable
	- Proporciona acceso rápido mediante índices
	- Permite inserción y eliminación eficiente pero menos eficiente en otras posiciones
- **Forward List** `std::forward_list`
	- Simplemente enlazada
	- Inserción y eliminación eficiente al principio o medio
	- No proporciona acceso aleatorio
	- Más eficiente que list
- **Deque** `std::deque`
	- Doblemente terminada cola
	- Inserción y eliminación eficiente de elementos a principio y fin
	- Acceso rápido mediante índices
	- Almacena elementos en secuencia contigua
- **Stack** `std::stack`
	- Pila FIFO
	- Inserción y eliminación de elementos en parte superior
	- No permite acceo a elementos que no estén en la parte superior