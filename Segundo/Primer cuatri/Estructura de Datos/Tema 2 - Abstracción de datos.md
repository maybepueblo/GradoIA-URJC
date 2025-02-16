#### Cajas negras

A medida que programamos, nuestro programa se llena de cajas negras, o en otras palabras, implementaciones cuyo trasfondo no conocemos. 

#### Cómo definir un TAD

Hemos de definir qué podemos hacer con ese tipo abstracto de datos:

```c
Especificación xxxx

	TIPO tDato 

	OPERACIONES --> Qué podemos hacer con este tipo de datos
	(* CONSTRUCTORAS GENERADORAS *) --> Conjunto mínimo de funciones que      me permite generar ese TAD
	(* CONSTRUCTORAS NO GENERADORAS *) --> Funciones que me permiten          seguir generando el tipo de datos
	(* OBSERVADORAS SELECTORAS *) --> Me permiten acceder a alguna            información dentro del TAD
 	(* OBSERVADORAS NO SELECTORAS *) --> Acceder a información que            calculo en función del TAD

	ECUACIONES --> Comprobaciones para ver que funcione bien

FIN ESPECIFICACIÓN
```

Vamos antes que nada, a entender un poco mejor qué significa esto en temas posteriores como [[Tema 3 - Listas]] o demás:

 1. Constructoras Generadoras

Estas son las operaciones mínimas necesarias para crear y dar vida al TAD desde cero. Este conjunto de funciones crea instancias iniciales válidas del tipo de datos, y por lo general, constituyen el núcleo para construir cualquier versión del TAD. Sin las constructoras generadoras, no se puede formar el tipo de datos.

_Ejemplo:_ En una lista enlazada, una función generadora podría ser la creación de una lista vacía (`crearListaVacia()`), ya que es fundamental para iniciar cualquier estructura de este tipo.

2. Constructoras No Generadoras

Son las funciones que permiten modificar o expandir una instancia ya creada del TAD. Si bien estas no forman el TAD desde cero, permiten añadir o modificar elementos para seguir desarrollando la estructura.

_Ejemplo:_ En una lista, una constructora no generadora sería `insertarElemento(lista, elemento)`, que agrega un nuevo elemento a una lista ya existente, sin tener que crearla desde el inicio.

 3. Observadoras Selectoras

Estas funciones permiten acceder directamente a elementos o información específica dentro del TAD. Su función principal es la obtención de partes internas o datos guardados sin modificarlos. Permiten “seleccionar” datos específicos del TAD.

_Ejemplo:_ En un TAD de lista enlazada, `obtenerPrimero(lista)` sería una observadora selectora, ya que accede al primer elemento sin alterar la lista.

 4. Observadoras No Selectoras

Estas operaciones también observan información en el TAD, pero, a diferencia de las observadoras selectoras, obtienen datos calculados o derivados de la estructura, en lugar de acceder directamente a una parte específica de ella. Estas operaciones brindan una visión más general o procesada del TAD.

_Ejemplo:_ En una lista enlazada, `esVacia(lista)` es una observadora no selectora, pues verifica si la lista está vacía o no sin retornar un elemento específico.

---

Ahora, veamos la especificación algebraica para los complejos: 

```c
Especificación Complejos

	TIPO tComplejo
	
	OPERACIONES
	
	(* Constructoras generadoras *)
		CrearComplejo : Real x Real -> tComplejo
	(* Constructoras no generadoras *)
		Sumar : tComplejo x tComplejo -> tComplejo
		Restar : tComplejo x tComplejo -> tComplejo
		Multiplicar : tComplejo x tComplejo -> tComplejo
		Dividir : tComplejo x tComplejo -> tComplejo
		Conjugado : tComplejo -> tComplejo
		I -> tComplejo
	(* Observadoras selectoras *)
		ObtenerReal : tComplejo --> Real
		ObtenerImaginaria : tComplejo --> Real
	(* Observadoras no selectoras *)
		CalcularModulo : tComplejo -> Real

	VARIABLES
		re, im : Real

	ECUACIONES DE DEFINITUD
		SI re2 != 0 O im2 != 0
			DEF(Dividr(CrearComplejo(re, im), CrearComplejo(re2, im2)))

	ECUACIONES

	(* Constructoras no generadoras *)
		Sumar(CrearComplejo(re, im), CrearComplejo(re2, im2)) =                          CrearComplejo(re+re2, im+im2) 		
		Restar(CrearComplejo(re, im), CrearComplejo(re2, im2)) =                         CrearComplejo(re-re2, im-im2)
		Multiplicar(CrearComplejo(re, im), CrearComplejo(re2, im2)) =
		CrearComplejo()
		Dividir(CrearComplejo(re, im), CrearComplejo(re2, im2)) =
		CrearComplejo(((re*re2) + (im*im2))/(re2^2+im2^2),                               ((re2*im)-(re*im2)/(re2^2+im2^2)))
		Conjugado(CreaComplejo(re, im) ->rComplejo(re, im))
		I = CrearComplejo(0, 1)
		
	(* Observadoras selectoras *)
		ObtenerReal(CrearComplejo(re, im)) =  re
		ObtenerImaginaria(CrearComplejo(re, im)) = im
	(* Observadoras no selectoras *)
		CalcularModulo(CrearComplejo(re, im)) = sqrt(re^2 + im^2)

FIN ESPECIFICACIÓN
```

Así podemos definir el tipo booleano con nuestro TAD:

```c
ESPECIFICACIÓN Booleanos
	TIPOS tBooleano

	OPERACIONES 
		(* constructoras generadoras *)
		CIERTO: -> tBooleano
		FALSO: -> tBooleano

		(* constructoras no generadoras *)
		NO: tBooleano -> tBooleano
		Y:tBooleano x tBooleano -> tBooleano
		O: tBooleano x tBooleano -> tBooleano

	ECUACIONES 
		(* constructoras no generadoras *)
		NO(CIERTO) = FALSO
		NO(FALSO) = CIERTO

		Y(FALSO, FALSO) = FALSO
		Y(FALSO, CIERTO) = FALSO
		Y(CIERTO, FALSO) = FALSO
		Y(CIERTO, CIERTO) = CIERTO

		O(FALSO, FALSO) = FALSO
		O(FALSO, CIERTO) = CIERTO
		O(CIERTO, FALSO) = CIERTO
		O(CIERTO, CIERTO) = CIERTO

FIN ESPECIFICACIÓN
```

Además, podemos encontrar una forma alternativa:

```c
ESPECIFICACIÓN Booleanos2
	TIPOS tBooleano

	OPERACIONES 
		(* constructoras generadoras *)
		CIERTO: -> tBooleano
		NO: tBooleano -> tBooleano

		(* constructoras no generadoras *)
		Y:tBooleano x tBooleano -> tBooleano
		O: tBooleano x tBooleano -> tBooleano

	VARIABLE
		b, c: tBooleano

	ECUACIONES ENTRE GENERADORAS
		NO(NO(b)) = b

	ECUACIONES 
		(* constructoras no generadoras *)
		Y(b, CIERTO) = b
		Y(b, NO(CIERTO)) = NO(CIERTO)

		O(b, CIERTO) = CIERTO
		O(b, NO(CIERTO)) = b

FIN ESPECIFICACIÓN
```

Veamos cómo haríamos la definición de un entero: 

```c
ESPECIFICACION Enteros

	TIPOS tEntero

	OPERACIONES
		
		(* constructoras generadoras *)
		CERO -> Entero
		Sucesor: tEntero -> tEntero
		Predecesor: tEntero -> tEntero
		
		(* constructoras no generadoras *)
		Suma: tEntero x tEntero -> tEntero
		Resta: tEntero x tEntero -> tEntero

	VARIABLES
		n, m: tEntero

	ECUACIONES ENTRE GENERADORAS
		Sucesor(Predecesor(n)) = n
		Predecesor(Sucesor(n)) = n

	ECUACIONES
			
		Suma(n, CERO) = n 

		Suma(2, 1) = Suma(2, Sucesor(CERO)) = Sucesor(2) = 3
		Suma(n, Sucesor(m)) = Sucesor(Suma(n, m))
		
		Suma(2, -1) = Suma(2, Predecesor(CERO)) = Predecesor(Suma(2, 0))                 = Predecesor(2) = 1
		Suma(n, Predecesor(m)) = Predecesor(Suma(n, m))

		Resta(n, CERO) = n
		Resta(n, Sucesor(m )) =  Predecesor(Resta(n, m))
		Resta(n, Predecesor(m)) = Sucesor(Resta(n, m))

FIN ESPECIFICACIÓN
```

Asimismo, esta es una posible definición de los números naturales:

```c
ESPECIFICACION Enteros

	TIPOS tNatural

	OPERACIONES
		
		(* constructoras generadoras *)
		UNO -> tNatural
		SUCESOR: tNatural -> tNatural

		(* constructoras no generadoras *)
		PARCIAL PREDECESOR: tNatural -> tNatural
		SUMAR: tNatural x tNatural -> tNatural
		MULTIPLICAR: tNatural x tNatural -> tNatural

	VARIABLES
		n : integer
		m, p : tNatural

	ECUACIONES DE DEFINITUD
		if n> -> DEF(PREDECESOR(n))
		
		DEF (PREDECESOR(SUCESOR(m)))
		
		SI NO(ES_UNO(m)) -> DEF(PREDECESOR(m))
	
	ECUACIONES
			
		Suma(n, CERO) = n 

		Suma(2, 1) = Suma(2, Sucesor(CERO)) = Sucesor(2) = 3
		Suma(n, Sucesor(m)) = Sucesor(Suma(n, m))
		
		Suma(2, -1) = Suma(2, Predecesor(CERO)) = Predecesor(Suma(2, 0))          = Predecesor(2) = 2
		Suma(n, Predecesor(m)) = Predecesor(Suma(n, m))

		Resta(n, CERO) = n
		Resta(n, Sucesor(m )) =  Predecesor(Resta(n, m))
		Resta(n, Predecesor(m)) = Sucesor(Resta(n, m))

FIN ESPECIFICACIÓN
```

Y finalmente, veremos la creación de un vector:

```c
ESPECIFICACIÓN Contenedor

	PARÁMETROS GÉNÉRICOS
		TIPOS tElemento, tPosicion
	FIN PARÁMETROS GENÉRICOS
	
	TIPOS tContenedor
	
	OPERACIONES 
		(* constructoras generadoras *)
		CrearVacio -> tContenedor
		Asignar: tElemento x tPosición x tContenedor -> tContenedor

		(* observadora selectora *)
		PARCIAL ObtenerElemento: tContenedor x tPosición -> tElemento
		BuscarPosición: tContenedor x tElemento -> tPosición

		(* observadoras no selectoras *)
		ExistePosición: tContenedor x tPosición -> tBooleano

		(* constructoras no generadoras
			PARAMETRO GENÉRICOS
				OPERACION
					ModificarElemento: tElemento -> tElemento
			FIN PARAMETRO GENÉRICOS
		Modificar : tContenedor -> tContenedor

	VARIABLE
		c: tContenedor
		p: tPosición

	ECUACIONES DE DEFINITUD
		 SI Existe(c, p) -> DEF(ObtenerElemento(c, p))

```