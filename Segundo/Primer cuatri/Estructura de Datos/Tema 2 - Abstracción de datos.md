#### Cajas negras

A medida que programamos, nuestro programa se llena de cajas negras, o en otras palabras, implementaciones cuyo trasfondo no conocemos.

#### Cómo definir un TAD

Hemos de definir qué podemos hacer con ese tipo abstracto de datos:

```
Especificación xxxx

	TIPO tDato 

	OPERACIONES --> Qué podemos hacer con este tipo de datos
	(* CONSTRUCTORAS GENERADORAS *) --> Conjunto mínimo de funciones que me          permite generar ese TAD
	(* CONSTRUCTORAS NO GENERADORAS *) --> Funciones que me permiten seguir          generando el tipo de datos
	(* OBSERVADORAS SELECTORAS *) --> Me permiten acceder a alguna información       dentro del TAD
 	(* OBSERVADORAS NO SELECTORAS *) --> Acceder a información que calculo en        función del TAD

	ECUACIONES --> Comprobaciones para ver que funcione bien

FIN ESPECIFICACIÓN
```

Ahora veamos la especificación algebraica para los complejos:

```
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
	(* Observadoras selectoras *)
		ObtenerReal : tComplejo --> Real
		ObtenerImaginaria : tComplejo --> Real
	(* Observadoras no selectoras *)
		CalcularModulo : tComplejo -> Real

	VARIABLES
		re, im : Real

	ECUACIONES

	(* Constructoras no generadoras *)
		Sumar(CrearComplejo(re, im), CrearComplejo(re2, im2)) =                          CrearComplejo(re+re2, im+im2) 		
		Restar(CrearComplejo(re, im), CrearComplejo(re2, im2)) =                         CrearComplejo(re-re2, im-im2)
		Multiplicar(CrearComplejo(re, im), CrearComplejo(re2, im2)) =
		CrearComplejo()
		Dividir(CrearComplejo(re, im), CrearComplejo(re2, im2)) =
		CrearComplejo(((re*re2) + (im*im2))/(re2^2+im2^2), ((re2*im)-                    (re*im2)/(re2^2+im2^2)))
		Conjugado(CrearComplejo(re, im))
	(* Observadoras selectoras *)
		ObtenerReal(CrearComplejo(re, im)) =  re
		ObtenerImaginaria(CrearComplejo(re, im)) = im
	(* Observadoras no selectoras *)
		CalcularModulo(CrearComplejo(re, im)) = sqrt(re^2 + im^2)

FIN ESPECIFICACIÓN
```

