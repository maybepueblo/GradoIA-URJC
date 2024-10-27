#### Introducción

**Definición**
Colección de elementos homogéneos dispuestos en orden tal que se recuperan en igual orden a como se introdujeron. El único elemento accesible es el primero.

**FIFO** (First In, First Out)

#### Especificación

¿Qué operaciones definimos para el TAD Cola?
- CrearColaVacia, Insertar, Eliminar...

Veamos su especificación algebraica:

```c
ESPECIFICACION Colas

	PARAMETROS GENERICOS
		TipoElemento
	FIN PARAMETROS GENERICOS

	TIPOS TipoCola

	OPERACIONES

	(* CONSTRUCTORAS GENERADORAS *)
	CrearColaVacia -> TipoCola
	Insertar: TipoElemento x TipoCola -> TipoCola

	(* OBSERVADORAS SELECTORAS *)
	PARCIAL PrimeroCola: TipoCola -> TipoElemento
	PARCIAL Eliminar: TipoCola -> TipoCola
	
	(* OBSERVADORAS NO SELECTORAS *)
	EsColaVacia : TipoCola -> Booleano
	IgualCola : TipoCola x TipoCola -> Booleano

	(* CONSTRUCTORAS NO GENERADORAS *) 
	CopiarCola : TipoCola -> TipoCola

	VARIABLES
		cola, cola2 : TipoCola;
		elem, elem2: TipoElemento;

	ECUACIONES DE DEFINITUD
		DEF(PrimeroCola(Insertar(elemento, cola)))
		DEF(Eliminar(Insertar(elemento, cola)))

	ECUACIONES
		(* OBSERVADORAS SELECTORAS *)
		PrimeroCola(Insertar(elem, cola)) =
			SI EsColaVacia(cola) ->
				elem
			|   PrimeroCola(cola)
		Eliminar(Insertar(elem, cola)) =
			SI EsColaVacia(cola) ->
				cola
			|   Insertar(elem, Eliminar(cola))

		(* OBSERVADORAS NO SELECTORAS *)
		EsColaVacia(CrearColaVacia) = CIERTO
		EsColaVacia(Insertar(elem, cola)) = FALSO

		IgualCola(CrearColaVacia, cola2) = EsColaVacia(cola2)
		IgualCola(Insertar(elem, cola), CrearColaVacia) = FALSO
		IgualCola(Insertar(elem, cola), Insertar(elem2, cola2))         = elemento = elem2 Y IgualCola(cola, cola2)

		(* CONSTRUCTORAS NO GENERADORAS *)
		CopiarCola(CrearColaVacia) = CrearColaVacia
		CopiarCola(Insertar(elemento, cola)) =
			Insertar(elemento, CopiarCola(cola))

FIN ESPECIFICACION
```

#### Implementaciones

##### Estática

En este caso, para implementar una cola, lo haremos a través de un vector en diversas formas de representación:

- Vector

![[Pasted image 20241027210346.png]]

- Vector circular con posición libre

![[Pasted image 20241027210428.png]]

- Vector circular con variable auxiliar longitud

![[Pasted image 20241027210455.png]]

Según estas definiciones podríamos deducir los siguientes casos:
- Si P y F apuntan a la misma posición, entonces la cola está vacía. 
- Si F apunta a la posición directamente anterior de P, entonces la cola está llena.

![[Pasted image 20241027210643.png]]
##### Dinámica

A su vez, existen diversas formas de resolver esta implementación de forma dinámica:

- Mediante punteros y variables dinámicas.
	- Son estructuras donde cada elemento tiene un componente de información y otro de enlace. Existen dos punteros, uno que señala al principio de la cola y otro a su final.
- Colas circulares.
	- El puntero de acceso a la cola referencia al último elemento, para poder insertar elementos.
	- El único elemento accesible de la cola será el primero, para consulta/extracción.

#### Cola de prioridad

>[!WARNING] 
>OJO, hay que tener en cuenta una diferencia crucial entre una lista ordenada y una cola de prioridad. La cola de prioridad prima al elemento que lleve más tiempo esperando, es decir, que si entra un nuevo elemento de la misma prioridad de uno ya existente, lo pondrá detrás de este elemento porque tiene prioridad el que lleva más tiempo en la cola. En cambio, en una lista ordenada, si el elemento es de la misma prioridad, se mete justo delante de él.

Veamos la especificación de la cola de prioridad:

```c
ESPECIFICACION ColasPrioridad
(* cola de máximos *)
	PARAMETROS GENERICOS
	
	TIPOS TipoElemento, TipoPrioridad
	OPERACIONES
		Prioridad: TipoElemento → TipoPrioridad
		(* La operación Prioridad devuelve la prioridad
		asociada a un elemento *)
		Mayor: TipoPrioridad x TipoPrioridad → Booleano
		(* operación de orden total ente prioridades *)
		Igual: TipoPrioridad x TipoPrioridad → Booleano
		(* operación de igualdad ente prioridades *)
	
	FIN PARAMETROS GENERICOS
	
	TIPOS TipoColaP
	
	OPERACIONES
	(* CONSTRUCTORAS GENERADORAS *)
		CrearColaVacia: → TipoColaP
		Insertar: TipoElemento x TipoColaP → TipoColaP
	(* OBSERVADORAS SELECTORAS *)
		PARCIAL PrimeroCola : TipoColaP -> TipoElemento
		PARCIAL Eliminar : TipoColaP -> TipoColaP
	(* OBSERVADORAS NO SELECTORAS *)
		EsColaVacia : TipoColaP -> Booleano
		
	VARIABLES
		cola, cola2 : TipoColaP;
		e, elem1,elem2 : TipoElemento;
	
	ECUACIONES DE DEFINITUD
		DEF(PrimeroCola(Insertar(elemento, cola)))
		DEF(Eliminar(Insertar(elemento, cola)))

	ECUACIONES ENTRE GENERADORAS
	(* La operación Insertar es conmutativa *)
	SI NO Igual(Prioridad(elem1), Prioridad(elem2))
		Insertar(elem1,Insertar(elem2,cola)) =                          Insertar(elem2,Insertar(elem1,cola))
	
	ECUACIONES
	(* Observadoras selectoras *)
	PrimeroCola(Insertar(e ,cola)) =
		SI EsColaVacia(cola) O                                          Mayor(Prioridad(e),Prioridad(PrimeroCola(cola)) →
		e
		| PrimeroCola(cola)
	Eliminar (Insertar(e,cola)) =
		SI EsColaVacia(cola) O Mayor(Prioridad(e),Prioridad             (PrimeroCola(cola)) →
			cola
	    | Insertar(e, Eliminar(cola))
	
	ECUACIONES (Cont.)
	(* Observadoras no selectoras *)
		EsColaVacia (CrearColaVacia) = CIERTO
		EsColaVacia (Insertar(elemento,cola)) = FALSO

FIN ESPECIFICACION
```

De igual forma, se adjunta en este repositorio el código perteneciente a [[Práctica Listas ED]] donde se incluye el TAD de las colas de prioridad y se explica en mayor profundidad.