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

Ahora veamos la especificación algebraica para los complejos: 

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
		CrearComplejo(((re*re2) + (im*im2))/(re2^2+im2^2),                        ((re2*im)-(re*im2)/(re2^2+im2^2)))
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
		
		Suma(2, -1) = Suma(2, Predecesor(CERO)) = Predecesor(Suma(2, 0))          = Predecesor(2) = 2
		Suma(n, Predecesor(m)) = Predecesor(Suma(n, m))

		Resta(n, CERO) = n
		Resta(n, Sucesor(m )) =  Predecesor(Resta(n, m))
		Resta(n, Predecesor(m)) = Sucesor(Resta(n, m))

FIN ESPECIFICACIÓN
```

Asimismo, esta es una posible definición de los números naturales:

```
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

```
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