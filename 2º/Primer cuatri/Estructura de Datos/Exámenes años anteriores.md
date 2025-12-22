![[Pasted image 20241030225827.png]]En esta sección, veremos algunos exámenes de años pasados, a la vez que aprovecharé para resolverlos y explicar mi procedimiento.

#### Parcial 1

![[Recuperación Primer Parcial_ Revisión del intento.pdf]]

##### Ejercicio 1

>[!Enunciado]
Calcula mediante la técnica de expansión de recurrencias la complejidad en notación O() de un algoritmo de busqueda ternaria similar a la búsqueda binaria, pero donde, en lugar de dividir en 2 mitades el almacén de datos ordenados, lo dividimos en 3 tercios.

Nos tenemos que guiar por un posible caso base y un caso recursivo, véase [[Complejidad Algorítmica]] para saber cómo hacer esto.
$$T(n)=nºllamadas·Tiempofunción+Tiemporesultado$$
Tenemos lo siguiente:
$$\begin{cases}
O(1) \space caso \space base \\
3·T(\frac{n}{3})+\frac{3n}{3} \space caso \space recursivo
\end{cases}
$$
Pues ya tenemos de dónde partir:
$$n'=\frac{n}{3}=T(\frac{n}{3})$$
$$T(n')=3·T(\frac{n'}{3})+n'$$
Deshacemos el cambio:
$$3·T(\frac{n}{3²})+\frac{n}{3}$$
Recordamos:
$$T(\frac{n}{2})=T(n')=>3·(3·T(\frac{n}{3²})+\frac{n}{3})+n=9·T(\frac{n}{3²})+2n$$
Seguimos desarrollando esta vez con n'':
$$n''=\frac{n}{3²}$$
$$T(\frac{n}{3²})=T(n'')=3·T(\frac{n''}{3})+n''$$
De nuevo, deshacemos el cambio:
$$3·T(\frac{n}{3³})+\frac{n}{3²}$$
Recordamos otra vez más:
$$T(\frac{n}{3²})=T(n'')$$
$$9·(3·T(\frac{n}{3³})+\frac{n}{3²})+2n=27·T(\frac{n}{3^3})+3n$$
Como vemos, tenemos un patrón que se puede expresar así:
$$T(n)=3·T(\frac{n}{3})+n=9·T(\frac{n}{3²})+2n=27·T(\frac{n}{3^3})+3n=...=^k3^kT(\frac{n}{3^k})+kn$$
Ahora podemos hallar la equivalencia caso base-recursivo:
$$T(\frac{n}{3^k})=1$$
$$\frac{n}{3^k}=1$$
$$n=3^k$$
$$log_3n=log_33^k$$
$$log_3n=k$$
Ahora podemos sustituir en nuestra función en base al parámetro k:
$$3^{log_3n}·T(\frac{n}{3^{log_3n}})+log_3n·n$$
Recordamos que:
$$a^{log_ax}=x$$
Así que:
$$n·T(\frac{n}n)+nlog_3n=n·T(1)+ nlog_3n$$
T(1) = 1 tal y como conocemos:
$$n+nlog_3n$$
Y por tanto podemos calificar este sistema con una complejidad algoritmica de:
$$O(nlogn)$$
##### Ejercicio 2

>[!Enunciado]
>TAD Lista acaba de ser ampliado con una nueva función llamada Duplicar. La labor de esta función es la de duplicar aquellos elementos de la lista que cumplen Condicion. En caso de que los elementos no cumplan dicha Condicion, se mantendrán en la lista sin sufrir ningún cambio. 
>
>En este ejercicio deberás indicar la operación, el tipo de operación que es, y la implementación (usando especificación algebraica) de Duplicar. NOTA El método condición se define como: Condicion : tElemento -> Booleano

Aquí tenemos que indicar la especificación algebraica de una nueva función llamada `Duplicar`, remontamos a [[Tema 2 - Abstracción de datos]] para ello. Nos servimos de una constructora no generadora para definir duplicar:

```c
ESPECIFICACIÓN

	(* OPERACIÓN CONSTRUCTORA NO GENERADORA *)
	Duplicar : TipoLista -> TipoLista

	VARIABLES
	lista : TipoLista
	e : TipoElemento

	ECUACION
	Duplicar(crearVacia) = crearVacia
	Duplicar(construir(e, lista)) = SI Condicion(e) => construir(e, construir(e,                                     Duplicar(lista))
	                                SI NO construir(e, duplicar(lista))+
```

##### Ejercicio 3

>[!Enunciado]
>Como cada año, el número de sugerencias para mejorar la asignatura de Estructura de Datos por parte del alumnado es tan alto (ronda las 50 sugerencias) que el profesorado se ve completamente desbordado para poder gestionarlas todas. Ante esto, los profesores han encargado a los alumnos del Grado en Inteligencia Artificial que desarrollen un módulo inteligente para gestionar todas esas sugerencias.
> 
>La aplicación en cuestión parece funcionar correctamente, pero al analizar el sistema se ha visto que el código elige un número aleatorio entre 0 y 100 (aún a sabiendas de que es difícil superar las 50 sugerencias) y que la estructura de datos seleccionada es una cola circular dinámica. 
>
>La estructura en cuestión utiliza un TAD llamado tSugerencia (que no es necesario programar) que tiene información de la sugerencia y del alumno que hace dicha sugerencia. Además, dentro del TAD tSugerencia disponemos de la siguiente funcionalidad:
>```
>void crearSugerencia(tSugerencia *dest, char alumno[50], char mensaje[300]); 
>void mostrarSugerencia(tSugerencia sug); 
>void asignarSugerencia(tSugerencia *dest, tSugerencia origen); 
>char* obtenerAlumno(tSugerencia sug); 
>char* obtenerMensaje(tSugerencia sug); 
>int iguales(tSugerencia uno, tSugerencia dos); // Devuelve 1 si las dos sugerencias son iguales
>```

 a. Definir los tipos de datos necesarios para poder crear el sistema descrito para almacenar sugerencias. Este tipo de datos se llamará tEstructura

```c
typedef struct Nodo {
	struct Nodo* anterior;
	tSugerencia sugerencia;
	struct Nodo* siguiente;
} tNodo;

typedef tNodo* tEstructura;
```

 b.  Realizar una función que dada la tEstructura y un número (que se corresponde con una sugerencia seleccionada) sea capaz de devolver un puntero al nodo que contiene dicha sugerencia. La cabecera de la función es la siguiente

```c
tNodo* localiza(tEstructura est, int numero) {
	if (est == NULL || numero < 0) {
		perror("Estructura vacía o número inválido");
	}

	tNodo* actual = est;
	int contador = 0;

	do {
		if (contador == numero) {
			return actual;
		}
		actual = actual->siguiente;
		contador++; 
	} while (actual != est)

	return NULL;
}
```
 
 c. Desarrollar un procedimiento que dada la tEstructura y un número, sea capaz de guardar la tSugerencia seleccionada en el tercer parámetro de la función y eliminarla del sistema. La cabecera de la función es la siguiente:

```c
void elimina(tEstructura *est, int numero, tSugerencia* dest) {
	if (est == NULL || numero < 0) {
		perror("Estructura vacía o número invalido");
		return;
	}

	tNodo* nodoObj = localiza(*est, numero);

	if (nodoObj != NULL) {
		asignarSugerencia(dest, nodoObj->sugerencia)
	
		if (nodoObj->anterior != nodoObj) {
			nodoObj->anterior->siguiente = nodoObj->siguiente;
			nodoObj->siguiente->anterior = nodoObj->anterior;
		}

		if (nodoObj == *est) {
			*est = nodoObj->siguiente;
		}
		
	} else {
		*est = NULL;
	}

	free(nodoObj);
}
```

##### Ejercicio 4

Nos encontramos con la función misterio que se muestra a continuación:

```c
void misterio(TEstructura *t) { 
	TNodo* aux = t->p; 
	while(aux != NULL){ 
		TElemento elem; 
		asignarElemento(&elem, aux->elemento); 
		if(cumpleCondicion(elem)){ 
		TNodo* otro = (TNodo*)malloc(sizeof(TNodo)); 
		asignarElemento(&(otro->elemento), elem); 
		otro->sig = NULL; 
		t->f->sig = otro; 
		t->f = otro; 
		} 
	aux = aux->sig; 
	} 
}
```

**¿Qué hace la función misterio y en qué TAD se encontraría de los estudiados en la asignatura?**

La función misterio es una Lista Enlazada Simple con puntero a inicio y fin, véase [[Tema 3 - Listas]]. En esta función, recorremos una lista desde el principio y dado el elemento del nodo en donde estemos situados, si dicho elemento perteneciente al nodo cumple una condición, crearemos un nuevo nodo con ese mismo elemento en su interior, para luego introducirlo al final de la lista. Es decir, si un nodo cumple una condición, lo copiaremos al final.

**¿Observas algún problema en esta función? En caso afirmativo, describe cuál o cuáles.**

El error que yo veo es que en esta línea:
``` t->f->sig = otro; ```

Hay un par de errores de hecho, el primer gran error es que no se verifica si la lista está vacía, lo que deriva en una gran cantidad de errores a posteriori. Tenemos primero que todo que cuando accedemos a ``` t->f->sig = otro; ```, si `t->f` es igual a NULL (cosa que sucede si la lista está vacía) se producirá un error de segmentación. 

Cabe recalcar que si la lista está vacía, t->f debería de apuntar a otro, que es algo más que no se contempla en este código.

Asimismo, no actualizamos nunca el t->p en el caso de que la lista estuviese vacía donde deberíamos actualizarlo para apuntar al nuevo nodo creado. 

Pero el mayor error de todos es no verificar si la lista está vacía o no.