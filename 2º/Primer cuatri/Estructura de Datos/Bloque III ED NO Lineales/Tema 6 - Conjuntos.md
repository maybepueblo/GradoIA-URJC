#### Introducción

- Colección no ordenada de elementos del mismo tipo sin repeticiones. Contienen una función llamada cardinalidad

Los conjuntos referencian a lo matemático, teniendo funciones como la unión, la diferencia o la intersección. 

#### Especificación

- Parametrizado por el elemento que guarda
- Posibles operaciones: 
	- CrearConjVacío, Poner, Pertenece, Cardinal

```c
ESPECIFICACION Conjunto

PARÁMETROS GENÉRICOS
	TIPOS TipoElemento
FIN PARÁMETROS

TIPOS TipoConjunto

OPERACIONES
	(*CG*)
	CrearConjVacio : -> TipoConjunto
	Poner: TipoConjunto x TipoElemento -> TipoConjunto

	(*OS*)
	PARCIAL Elegir: TipoConjunto -> TipoElemento
	

ECUACIONES DE DEFINITUD
	DEF 
		

```

#### Implementación

- Estática
	- Mediante un vector de "booleanos"
	- Vector de elementos

- Dinámica
	- Punteros (Muy similar a una lista enlazada simple)
		- Insertaremos por cabecera --> O(1)
			- No obstante, hay que comprobar si ese elemento existe con lo que el insertar es en verdad de complejidad -> O(n)

