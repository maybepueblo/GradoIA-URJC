#### Introducción

**¿Qué es una pila?**
Colección de elementos homogéneos dispuestos de tal manera que recuperamos en orden inverso al que se meten. Por ello, la extracción e inserción de elementos en la Pila se realiza por la parte superior.

- Existen dos acciones: ***push*** (apilar) y ***pop*** (desapilar). 
- El único elemento accesible es el último.
- Comportamiento **LIFO** (Last In, First Out)
#### Especificación

Parametrizada por el elemento que alberga:
- TipoElemento: parámetro genérico del TipoPila

¿Qué operaciones definimos para el TAD Pila?
- CrearVacia, Push, Pop, EsPilaVacia, Cima (algunas operaciones posibles)

>[!NOTE]
>Pop destruye lo último que hemos metido, Cima crea una copia de lo último que hemos metido.

``` c
ESPECIFICACIÓN FILAS

	PARÁMETROS GENÉRICOS
		TipoElemento
	FIN PARÁMETROS GENÉRICOS
	
	TIPOS TipoPila
	OPERACIONES 
	(* CONSTRUCTORAS GENERADORAS *)
	CrearPilaVacia : -> TipoPila
	Push : Tipo Elemento x TipoPila -> TipoPila
	(* OBSERVADORAS SELECTORAS *)
	PARCIAL Cima : TipoPila -> TipoElemento
	PARCIAL Pop : TipoPIla -> TipoPila
	(* OBSERVADORAS NO SELECTORAS *)
	EsPilaVacia : TipoPila -> Booleano

	VARIABLES
	pila: TipoPila;
	e: TipoElemento;

	ECUACIONES DE DEFINITUD
	DEF(Cima(Push(e, pila)))
	DEF(Pop(Push(e, pila)))
	
	ECUACIONES
		(* OBSERVADORAS SELECTORAS *)
		Cima(Push(e, pila)) = e
		Pop(Push(e, pila)) = pila

		(* OBSERVADORAS NO SELECTORAS *)
		EsPilaVacia(CrearPilaVacia) = CIERTO
		EsPilaVacia(Push(e, pila)) = FALSO

FIN ESPECIFICACIÓN
```

#### Implementaciones

##### Estáticas

Dentro de nuestra implementación estática, nos basaremos en un array de tamaño fijo con una variable llamada `cima` que representa la posición del último elemento de la pila. 

![[Pila Estática|700]]

``` c
typedef struct PilaArray {
	tElemento array[DIM]
	int cima;
}
```

Cabe recordar (aunque esté en la imagen) que una pila vacía tiene una cima de valor -1, debido a que no hay ningún elemento en nuestro array.

**¿Cómo añadimos un elemento?**

```c
void push(tPila* pila, tElemento elem) {
	if (pila->cima < DIM-1) {
		pila -> cima++;
		asignarElemento(pila->array[pila->cima], elem);
	}
}
```

Este código es bastante simple, pero veamos cómo furula. Primero, tenemos que comprobar si no estamos desbordando el array, es decir, no estamos metiendo más elementos de los que podemos. Si no lo estamos superando, aumentamos la cima de nuestro array y con asignarElemento, al array en la posición de la cima añadimos el elemento.

**¿Cómo haríamos pop?**

```c
void pop(tPila* pila) {
	if (!esPilaVacia(pila)) {
		pila->cima--;
	}
}
```

En este caso, pop lo que hace es eliminar el elemento que se encuentra en la cima, destruyéndolo completamente. Así, en nuestro caso anterior, habría borrado el elemento que acabamos de meter que estaba en la posición 0 de nuestro array.

###### Ejemplo estático

Veamos un ejemplo para visualizar cómo funcionaría una pila estática, usaremos las siguientes funciones aplicadas a un array de tamaño 4:

```c
push(pila, e);
push(pila, e2);
push(pila, e3);
cima(pila, &res);
pop(pila);
push(pila, e4);
```

![[Pila estática ejemplo|1900]]
##### Dinámicas

![[Implementación Dinámica Pilas|1000]]

Veamos ahora su implementación dinámica, donde usaremos nodos de tipo tElemento en los cuales tendremos un puntero al nodo anterior.

Así, nuestra pila será un puntero al nodo de la cima.

```c
typedef struct Nodo {
	tElemento info;
	struct Nodo* anterior;
} tNodo;

typedef tNodo* tPila;
```

Con esta estructura definida, podemos definir funciones que son parte de la implementación de esta pila:

```c
void crearPilaVacia(tPila *pila) {
	(*pila) = NULL;
}

void push(tPila* pila, tElemento elem) {
	tNodo* nuevoNodo = (tNodo*)malloc(sizeof(tNodo));
	asignarElemento(nuevoNodo->info, elem);
	nuevoNodo->anterior = *pila;
	*pila = nuevoNodo;
}

void cima(tPila* pila, tElemento* destino) {
	if (!esPilaVacia(pila)) {
		asignarElemento(destino, pila->info);
	}
}

void pop(tPila* pila) {
	if (!esPilaVacia(pila)) {
		tNodo* aux = *pila;
		*pila = aux->anterior
		free(aux);
	}
}

int esPilaVacia(tPila* pila) {
	return *pila == NULL;
}

void copiar(tPila* origen, tPila* destino) {
	tNodo* aux2NodoDest;

	if (!esPilaVacia(origen)) {
		tNodo* auxNodoOr = *origen;
		tNodo* auxNodoDest = (tNodo*)malloc(sizeof(tNodo));
		asignarElemento(auxNodoDest->info, auxNodoOr->info);
		auxNodoDest->anterior = NULL;
		*destino = auxNodoDest;
		auxNodoOr = auxNodoOr->anterior; // Avanzamos en pila
	
		while (auxNodoOr != NULL) {
			aux2NodoDest = auxNodoDest;
			auxNodoDest = (tNodo*)malloc(sizeof(tNodo));
			asignarElemento(auxNodoDest->info, auxNodoOr->info);
			auxNodoDest->anterior = NULL;
			aux2NodoDest->anterior = auxNodoDest;
			auxNodoOr = auxNodoOr->anterior;
		} 
	}
}

void destruirPila(tPila* pila) {
	while (!esPilaVacia(pila)) {
		pop(pila);
	}
}
```

La única función digna de mención profunda es `copiar`, debido a su complejidad, desglosemos la función y veamos cómo funciona:

1. **Verificar pila vacía**:
	Empezamos comprobando si la pila origen no está vacía. En caso de que lo estuviese, no hacemos nada.
2. **Iniciar el primer nodo de destino**
	Iniciamos el proceso de copia:
	1. `auxNodoOr = *origen` Establece un puntero auxiliar que apunta al primer nodo de la pila origen.
	2. Reservamos memoria en `auxNodoDest`, donde creamos el primer nodo de la pila destino.
	3. Copia de información: copiamos la info del nodo origen al nodo recién creado.
	4. Configuramos los punteros estableciendo que el anterior del nodo auxNodoDest en NULL ya que será el tope de destino. 
	5. Asignamos auxNodoDest a destino y destino apuntará al primer nodo de la nueva pila.
3. **Avanzar al siguiente nodo en origen**
	Avanzamos al siguiente nodo en la pila origen para continuar el proceso de copia.
4. **Copiar el resto de nodos de origen a destino**
	Nos servimos de un while para copiar nodo por nodo mientras que auxNodoOr no sea NULL.
	1. Almacenamos el nodo previo: la variable aux2NodoDest la usamos para mantener el puntero al nodo actual de destino antes de avanzar, permitiendo establecer un enlace entre el nodo que recién copiemos y el nodo anterior en destino.
	2. Creamos el siguiente nodo: Reservamos memoria para un nuevo nodo en auxNodoDest y se copia la info desde el nodo actual de origen a este nuevo nodo.
	3. Enlazamos los nodos.
	4. Avanzamos en origen poco a poco para poder llegar hasta el nodo final de nuestra pila.

Al finalizar, tendríamos todos nuestros nodos copiados en el mismo orden en la pila destino.