## El problema de planificación
### Definición y objetivo
La planificación es el proceso de buscar y organizar una secuencia de acciones que permiten alcanzar un objetivo deseado. En términos simples, es como crear un "plan de acción" para resolver un problema, donde cada paso debe ser ejecutable y conducir al resultado deseado.
### Ejemplo ilustrado
Imagina que quieres comprar un libro con un ISBN específico (por ejemplo, 0137903952). Si consideramos que un ISBN tiene 10 dígitos, hay 10 billones de combinaciones posibles. Un algoritmo de búsqueda clásico (como búsqueda en profundidad o A*) tendría que examinar todas estas combinaciones para encontrar la correcta. Si además quieres comprar 4 libros, el número de planes posibles se dispara a $10^{40}$, lo que hace inviable una búsqueda exhaustiva. Aquí es donde la planificación, combinada con heurísticas, se vuelve esencial.
### Lenguajes de representación
- **STRIPS** (*Stanford Research Institute Problem Solver*):
	- **Estados** -> Se representan como conjuntos de literales positivos (hechos verdaderos). Por ejemplo:
		- `Pobre ∧ Desconocido` describe un estado donde el agente es pobre y desconocido
		- `En(Avión, Melbourne) ∧ En(Avión, Sidney)` describe la ubicación de un avión
	- **Objetivos** Estados parcialmente especificados. Un estado satisface un objetivo si contiene todos los literales del objetivo. Por ejemplo:
		- El estado `Rico ∧ Famoso ∧ Miserable` satisface el objetivo `Rico ∧ Famoso`
	- **Acciones** Se definen con precondiciones (qué debe ser cierto antes de ejecutarla) y efectos (cómo cambia el estado después).
- **ADL (Action Description Language)**
	Extiende STRIPS permitiendo literales negativos, cuantificadores y tipos
### Hipótesis STRIPS vs ADL
- **STRIPS**
	- Sólo literales positivos en estados
	- Mundo cerrado: lo no mencionado se asume falso
	- Objetivos son conjunciones simples
- **ADL**
	- Permite literales negativos y disyunciones
	- Mundo abierto: lo no mencionado es desconocido
	- Soporta efectos condicionales
## Planificación con búsquedas en espacios de estado
### Enfoques de búsqueda
1. **Búsqueda hacia delante**
	- Comienza en el estado inicial y aplica acciones válidas hasta alcanzar el objetivo
	- **Ejemplo:** Para el problema del avión, empezamos con `En(P1, JFK)` y aplicamos `Volar(P1, JFK, SFO)` para llegar a `En(P1, SFO)`
	- **Desventaja** Puede explorar muchas acciones irrelevantes
2. **Búsqueda hacia atrás**
	- Parte del objetivo y busca acciones que lo puedan lograr, luego precondiciones, etc...
	- **Ejemplo:** Si el objetivo es `En(C1, JFK)` buscamos acciones como `Descargar(C1, P1, JFK)` cuya precondición es `Dentro(C1, P1) ∧ En(P1, JFK)`
	- **Ventaja** Filtra acciones no relevantes
## Planificación ordenada parcialmente (POP)
En lugar de ser estrictos con el orden entre acciones, posponemos decisiones hasta que sean necesarias (**mínimo compromiso**). Esto es útil cuando subobjetivos son independientes
### Ejemplo: Ponerse zapatos y calcetines
- **Objetivo:** `ZapatoDerechoPuesto ∧ ZapatoIzquierdoPuesto`.
- **Acciones:**
    - `CalcetínDerecho` → `CalcetínDerechoPuesto`.
    - `ZapatoDerecho` (requiere `CalcetínDerechoPuesto`).
    - Análogo para el lado izquierdo.

**Solución POP:**
- **Relaciones de orden:**  
    `CalcetínDerecho < ZapatoDerecho` y `CalcetínIzquierdo < ZapatoIzquierdo`.
- **Enlaces causales:**  
    `CalcetínDerecho → CalcetínDerechoPuesto → ZapatoDerecho`.
- **Linearizaciones posibles:**  
    6 planes equivalentes (ej.: ponerse ambos calcetines primero, luego zapatos en cualquier orden).
### Elementos de un plan POP
- **Acciones:** Pasos del plan
- **Restricciones de orden** `A < B` (A antes de B)
- **Enlaces causales** `A -> P -> B` (A logra P para B)
- **Precondiciones abiertas**: Literales no alcanzados por ninguna acción
### Ejemplo complejo: Rueda de recambio
- **Objetivo:** `En(Repuesto, Eje)`
- **Acciones**:
	- `Quitar(Repuesto, Maletero)`: Mueve la rueda al suelo
	- `Quitar(Deshinchada, Eje)`
	- `Colocar(Repuesto, Eje)`
- **Conflicto** Si se usa `DejarloDeNoche` que elimina todas las ruedas, se rompe el plan. La solución es evitar esto y usar `Quitar(Deshinchada, Eje)` en su lugar
## Grafos de planificación
### Estructura
- **Niveles alternados**: Estados (`Si`) y acciones (`Ai`)
- **Nivel 0**: Estado inicial
- **Acciones persistentes**: Mantienen literales sin cambio
### Ejemplo: Tener y comer pastel
- **Nivel S0** `Tener(Pastel)`
- **Nivel A0** Acciones `Comer(Pastel)` (elimina `Tener(Pastel)`) y persiste `Tener(Pastel)`
- **Exclusión mutua**:
	- `Comer(Pastel)` y persistencia de `Tener(Pastel)` son excluyentes (efectos inconsistentes)
	- En `S1`, `Tener(Pastel)` y `¬Tener(Pastel)` son mutuamente excluyentes
### Estabilización
El grafo se estabiliza cuando dos niveles consecutivos son idénticos, indicando que no hay nuevos literales o acciones posibles
## Análisis de los enfoques de planificación
### Ventajas y desafíos
- **Fuerza combinada** La planificación integra búsqueda y lógica, permitiendo soluciones constructivas
- **Explosión combinatoria** En dominios complejos, el número de estados y acciones crece rápidamente
- **Divide y vencerás** La descomposición de problemas en subobjetivos independientes es clave para manejar la complejidad.
### Conclusión
Los planificadores como **STRIPS** y **POP** son herramientas poderosas para problemas estructurados, pero requieren heurísticas y estrategias como grafos de planificación para ser escalados. La elección del método depende del problema:
- **Búsqueda hacia delante/atrás**: Para problemas chicos
- **POP**: Subobjetivos independientes
- **Grafos de planificación**: Problemas proposicionales complejos
