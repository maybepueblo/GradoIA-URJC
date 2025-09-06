## 1º Ejercicio
a. Nombre, teléfono y nombre de la persona de contacto de todos los alojamientos
	$\pi$ nombre-aloja, telefono, contacto (ALOJAMIENTOS)
b. Nombre y teléfono de los alojamientos que ofertan habitaciones dobles.
	$\pi$ nombre, telefono (ALOJAMIENTOS $\theta_{alojamiento=nombre-aloja}$ ($\sigma_{tipo="Doble"}$  (HABITACIONES))
c. Nombre de actividades que se realizan los viernes
	$\pi$ nombre-activ (ACTIVIDADES $\theta_{codigo-activ}$ ($\sigma_{dia-semana='viernes'}$  (REALIZA_ACTIVIDAD)))
d. Nombre de los alojamientos que no ofertan habitaciones con baño compartido
	$\pi$ nombre-aloja (ALOJAMIENTOS) - $\pi$ nombre-aloja (ALOJAMIENTOS $\theta_{alojamiento=nombre-aloja}$ ($\sigma_{baño='Compartido'}$ (HABITACIONES)))
e. Nombre de los alojamientos que ofertan todo tipo de habitaciones
	$\pi$ nombre-aloja (ALOJAMIENTOS) / $\pi$ tipo (HABITACIONES)
f. Nombre y dirección de los alojamientos con más de 25 habitaciones que ofrezcan actividades de nivel "Fácil"
	$\pi$ nombre-aloja, direccion ($\sigma_{nºhab>25}$ ALOJAMIENTOS $\theta_{nombre-aloja}$ (REALIZA_ACTIVIDAD $\theta_{codigo-activ}$ ($\sigma_{nivel='Fácil'}$) ACTIVIDADES))
## 2º Ejercicio

## 3º Ejercicio
1. V
2. F
3. V
4. F
## 4º Ejercicio
1. V
2. V 
3. F
4. F