## Introducción
Una de las búsquedas primigenias, es un procedimiento de búsqueda trayectorial, inspirada por un principio heurístico:
- "mejor una mala decisión basada en información que en buena decisión al azar"

**Características**
- Uso de memoria adaptativa
	- Componente principal que simula un aprendizaje durante la búsqueda. Se distinguen dos tipos de memoria
		- Memoria a corto plazo -> Intensificación
			- Muy pocos movimientos para no volver atrás a lo que ya inferimos que era peor que nuestra actualidad. Es una forma de "fine-tuning" para poder llegar a una solución realmente prometedora
		- Memoria a largo plazo -> Diversificación
- Estrategias de problem solving que permiten empeorar durante la búsqueda
	- Recordar por dónde empeorar para no hacerlo por donde te dificulte encontrar una buena solución
- Procedimientos sistemáticos que minimicen las componentes aleatorias
- Compromiso intensificación-diversificación
	- Intensificar : centrarte en un punto
	- Diversificar : explorar diversas ramas
- Procedimientos implícitos y explícitos de aprendizaje
## Esquema general

![[EsquemaGeneralTabuSearch.png]]
## Memoria a corto plazo
Se encarga de evitar que la búsqueda caiga en óptimos locales ya visitado, prohibiendo realizar ciertos movimientos, emplear ciertos atributos o visitar ciertas soluciones.

Estos movimientos, atributos o soluciones prohibidos son "tabús", con los que se pretende escapar de ciclos. Permiten esos movimientos de empeoramiento para escapar de óptimos locales.

Estos elementos restringidos no permanecen en la lista tabú para siempre, ello se denomina "permanencia tabú" (tabu tenure) al intervalo de tiempo durante el que un atributo o movimiento permanece tabú-activo o una solución es tabú. 

Este parámetro se mide en número de iteraciones. Una vez transcurrido el valor especificado, el elemento deja de ser tabú activo y lo eliminamos de la lista.
### Criterio de aspiración
Permite determinar cuándo pueden ser reemplazadas las restricciones tabú, de forma que se elimina una clasificación tabú aplicada a un moivmiento.
## Memoria a largo plazo

**Estrategia y uso**
La información guardada en esta memoria se usa para reiniciar la búsqueda desde otra solución siguiendo dos estrategias:
- **Intensificar** volviendo a visitar zonas prometedoras ya exploradas parcialmente
- **Diversificar** visitando nuevas zonas no exploradas

**Estructuras auxiliares**
La más común es la memoria de frecuencias, que registra el número de veces que cada valor de un atributo ha pertenecido a soluciones visitadas en la búsqueda. Aun así, se pueden usar otras estructuras para la memoria a largo plazo, dependiendo del problema tratado.