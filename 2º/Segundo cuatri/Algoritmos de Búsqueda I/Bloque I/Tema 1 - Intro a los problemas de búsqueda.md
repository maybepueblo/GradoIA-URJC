En problemas de búsqueda trabajamos con estados (representados con nodos en grafos). Tendremos las denominadas rutas que nos guiarán en base a conexiones hasta el estado final, esto es lo que definimos como buscar. 

Se puede dar el caso de múltiples estados iniciales de problema y múltiples estados finales para el mismo (conjunto de estados inicio/fin).

Habríamos de considerar estos aspectos:
1. Las restricciones del problema
2. Condiciones para ejecutar acciones
3. Estrategia de control
4. Acceso a información sobre los estados
5. Criterios de aceptabilidad de las soluciones
Además de estos, también tenemos que considerar lo siguiente:
- Factor de ramificación
- Profundidad de la primera solución
## Elementos
- Formulación del objetivo de la búsqueda
- Formulación del problema
- Representación del problema (grafo):  espacio de estados
	- Decimos que es el conjunto de todos los estados posibles de un problema. Así, es como un mapa con toda la información sobre movimientos y las conexiones entre ellos. 
	- Si queremos ponernos formales, es un grafo dirigido
- Representación de la solución (árbol de búsqueda)
## Representación informática
### Agentes basados en búsqueda
- Capaces de percibir el estado actual del mundo (la situación)
- Tienen un determinado objetivo/meta
- Son capaces de realizar acciones que modifican el mundo
- Buscan una secuencia de acciones que modifiquen el mundo para llegar a su objetivo. 
Para hacer esto mantienen un modelo simbólico del entorno, anticipan los efectos esperados de sus acciones sobre el modelo, generando y seleccionando planes de actuación en el modelo antes de ejecutar las acciones del plan en el entorno. 

**Búsqueda offline** -> Se analizan todas las posibilidades y se ejecuta en el mundo real
**Búsqueda online** -> Se actualiza conforme se hace la búsqueda en relación al entorno. 

Todo sistema es offline por defecto pero cuando se ha de actualizar, es cuando se vuelve un sistema online.
### Características de entornos simples
- **Discreto**
	- Se puede concebir el mundo en estados
	- En cada estado hay un conjunto finito de percepciones y acciones
- **Accesible**
	- Puede determinar el estado actual del mundo
	- También puede determinar el estado del mundo a alcanzar
- **Estático y determinista**
	- Solo cambian las cosas cuando el agente actúa
	- Resultado de cada acción está definido y es estable
### Conocimientos a priori de un agente
Tenemos diferentes posibilidades:
- s_0; Estado inicial
- expandir: s-> {s_i1, ..., s_in}; conjunto finito de sucesores de un estado
- meta?: s->verdad|falso; prueba de éxito en un estado
- c: (s_i, s_j) -> v; coste de un operador
- c(s_i, s_i2, ..., s_in) = sumatorio de estos; coste de un plan
### Elementos del algoritmo general
``` python
{búsqueda general}
abierta <- s0 # lista
Repetir 
	Si vacía?(abierta) entonces
		devolver(negativo)
	nodo <- primero(abierta)
	Si meta?(nodo) entonces
		devolver(nodo)
	sucesores <- expandir(nodo)
	Para cada n sucesores hacer
		n.padre <- nodo
		ordInsertar(n, abierta, <orden>)
	Fin{repetir}
```
- El árbol lo representamos a través de un registro de tipo nodo
- abierta es una lista de nodos con las hojas actuales del árbol
- vacía? determina si una lista es vacía
- Primero quita el primer elemento de una lista
- ordInsertar añade un nodo a una lista, clasificado según una función de orden
### Problema de estados repetidos
### Métodos de búsqueda
- **No informados**
	- Conocimiento mínimo
- **Heurísticos**
	- Información aproximada y específica del problema (guía)
- **Con estados estructurados**
	- Características de estados para la complejidad