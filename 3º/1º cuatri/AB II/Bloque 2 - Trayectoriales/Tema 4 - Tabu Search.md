Para abreviarlo, lo llamaré TS a lo largo de este documento.
# Introducción 
Es un procedimiento de **búsqueda trayectorial**, véase la taxonomía del [[Tema 2 - Introducción a las heurísticas y metaheurísticas]]. 

Propuesto por Fred Glover en 1977, se basa en un principio heurístico simple:
- *"mejor una mala decisión basada en información, que una buena decisión al azar"*
## Características
Lo que le hace diferente es que:
- Usa **memoria adaptativa**
	- Una de las principales componentes de Tabu Search
	- Simula un **aprendizaje** durante el proceso de búsqueda que aplica en la toma de decisiones inmediatamente posterior
	- Se pueden distinguir dos tipos de **memoria**:
		- **Corto plazo**
		- **Largo plazo**
- Tiene estrategias de resolución de problemas que **permiten empeorar** durante la búsqueda
- Procedimientos **sistemáticos** que minimizan las componentes aleatorias.
- Compromiso entre **intensificar y diversificar**
- Procedimientos implícitos y explícitos de **aprendizaje**
# Esquema general - explicación

![[Pasted image 20260531184110.png]]

1. Obtener nueva solución $x*$ de $N(x)$
	- Generamos un candidato $x*$ del vecindario $N(x)$ de la solución actual $x$. El vecindario es el conjunto de soluciones alcanzables con un único movimiento desde x.
		*En este punto no hemos decidido si ese movimiento se hará*
2. ¿El movimiento usado es tabu activo?
	- Se consulta la **lista tabú**, que es la memoria a corto plazo que almacena los movimientos recientemente realizados para no repetirlos.
	- Rama NO -> El movimiento NO está prohibido
		- Es libre ese movement, así que procedemos a evaluarlo:
			- Evaluamos fitness de $x*, f(x*)$: se calcula la calidad de la solución candidata.
			- ¿Es $f(x*)$ mejor que $f(x_{best})$?
				- **Sí** -> actualizamos el mejor encontrado $x_{best}=x*$
				- **No** -> continuamos sin actualizar el $x_{best}$
	- Rama SÍ -> El movimiento SÍ está prohibido
		- No lo podemos aceptar directamente pero existe una forma de escapar, el **criterio de aspiración**
3. ¿Criterio de aspiración?
	- Esto es lo que nos permite levantar la **prohibición tabú** de forma excepcional. El criterio más habitual es:
		- *"Acepto el movimiento tabú si la solución resultante **es mejor que la mejor solución global encontrada hasta ahora**"*
	- Sí supera el criterio -> Levantamos prohibición y la unimos al flujo normal, pudiendo actualizar $x_{best}$
	- No lo supera -> El movimiento se **descarta completamente**
4. ¿Se han evaluado suficientes movimientos?
	- **Bucle de exploración del vecindario**. No elegimos al primer candidato que encontremos, sino que evaluamos varios movimientos antes de decidir cuál ejecutamos.
	- No -> volvemos a obtener otro candidato $x*$ de $N(x)$ (seguimos explorando)
	- Sí -> se ha terminado de explorar y elegimos al mejor candidato aceptable
5. Realizar el movimiento elegido $x = x_{best}$
	- Ejecutamos el **mejor movimiento admisible** encontrado en la exploración del vecindario. La solución actual pasa a ser $x_{best}$
6. Actualizar estructura tabú
	- Registramos el movimiento realizado en la **lista tabú** para que quede prohibido durante las próximas iteraciones. Tras esto, el algoritmo **vuelve al inicio** con la nueva x.
# Memoria a corto plazo
TS es una metaheurística que se superpone a una **técnica de búsqueda**, y así, lo podemos combinar con otras técnicas.

Se encarga de evitar que la búsqueda caiga en óptimos locales ya visitados, **prohibiendo** (penalizando) realizar ciertos **movimientos**, emplear ciertos **atributos** o visitar ciertas **soluciones**.

Incorporamos un mecanismo de generación de vecinos modificado que evita la exploración de zonas del espacio de búsqueda ya visitadas.
- Clasificando ciertos movimientos como prohibidos (**tabú**) escapamos de ciclos durante la búsqueda.
- Permitimos **movimientos de empeoramiento** para huir de óptimos locales.

Sea $x$ una solución y $N(x)$ una vecindad de $x$. TS restringe $N(x)$ a una versión restringida $N^*(x)$ de la que se elige la mejor solución para el movimiento aunque este suponga un empeoramiento de la solución.

La lista de soluciones admitidas en este $N^*(x)$ se calcula en función de la estructura de la lista tabú:
- Lista de **soluciones tabú-activas**: prohibimos soluciones ya vistas.
- Lista de **movimientos tabú-activos**: eliminamos soluciones de $N(x)$ que obtenemos realizando movimientos tabú desde $x$
- Lista de **atributos tabú-activos**: eliminamos de $N(x)$ los vecinos con par (atributo, valor) determinado que ya ha aparecido en alguna solución explorada anteriormente.

Evidentemente, un atributo, movimiento o solución añadido en una **lista tabú** no se queda ahí por siempre, esto se llama **permanencia tabú** (**tabu tenure**). Este parámetro se mide en número de iteraciones. Una vez transcurrido el valor especificado, el elemento en cuestión **deja de ser tabú activo** y lo eliminamos de la lista.
## Criterio de aspiración
Este concepto es el que permite determinar cuándo pueden ser reemplazadas las restricciones tabú, de modo que se elimina la clasificación tabú aplicada a un movimiento.

**Aspiración por objetivo**
- Forma global: si la solución resultante es la mejor encontrada hasta el momento
- Forma local: si la solución resultante es la mejor encontrada hasta el momento en una región determinada.
**Aspiración por defecto**
- Si todos los movimientos son tabú y no se pueden aplicar criterios de aspiración sobre ellos, s- **AB II:** Tema 12 (Genéticos) y Tema 13 (Programación Genética).e elige el menos tabú.
# Memoria a largo plazo
Tener información guardada que permite **guiar la búsqueda** a posteriori, después de una primera etapa en la que se han realizadoo una o varias ejecuciones del algoritmo usando la memoria a corto plazo.

La información que tenemos en esta memoria se puede usar para **reiniciar la búsqueda** desde otra solución siguiendo dos posibles estrategias:
- **Intensificar la búsqueda**, volviendo a visitar zonas prometedoras del espacio (que contenían buenas soluciones), ya exploradas parcialmente.
- **Diversificar la búsqueda**, visitando nuevas zonas no exploradas aún.

Usa lo frecuente para modificar temporalmente el caso del problema, potenciando **elegir los valores de los atributos menos usados**. Así, nos permite reinicializar la búsqueda usando la info almacenada en memoria a largo plazo favoreciendo componentes menos frecuentes frente a los más habituales.
## Estructuras auxiliares
Podemos usar diferentes tipos, dependiendo del problema que tratemos.
### Memoria de frecuencias
Registra el número de veces que cada valor de un atributo ha pertenecido a soluciones visitadas en la búsqueda.
### Ejemplos
- **Problemas binarios** -> Un vector de dimensión n, para almacenar el número de veces que cada variable tomó el valor 0 o 1.
- **Problemas enteros** -> Una matriz bidimensional que guarde las veces que la variable i toma el valor k
- **Problemas permutaciones** -> Se puede usar una matriz bidimensional, como contador de las veces que el valor i ha ido seguido del j.