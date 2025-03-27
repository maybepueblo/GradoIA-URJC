## Elementos de un juego
### Definición y características
Un juego en IA es un entorno multiagente donde las decisiones del jugador afecta a los demás. Se caracteriza por:
- **Agentes**: Jugadores con roles definidos (*ejemplo*: ***max*** y ***min*** en juegos bipersonales)
- **Metas opuestas o cooperativas**: En juegos de suma cero, lo ganado por un jugador, lo pierde el otro
- **Determinismo vs Azar**: Algunos juegos tienen reglas fijas (damas), mientras que otros incluyen elementos aleatorios (póker)
### Tipos de juegos
- **Número de jugadores**
	- **Bipersonales**: Dos jugadores (tres en raya, ajedrez)
	- **Multijugador**: Tres o más (Monopoly, póker)
- **Información**
	- **Perfecta**: Todos ven el estado completo (ajedrez)
	- **Imperfecta**: Información oculta (póker, cartas privadas)
- **Estructura de recompensas**
	- **Suma cero:** Ganancia de un jugador = pérdida del otro
	- **Cooperativos**: Jugadores comparten metas

**Ejemplo**
- **Tres en raya** -> Juego bipersonal, determinista de información perfecta y suma cero
- **Póker** -> Multijugador, no determinista (por cartas aleatorias) y de información imperfecta
### Complejidad y desafíos
- **Factor de ramificación:** Número promedio de movimientos posibles por turno (ejemplo: 35 en ajedrez)
- **Espacio de búsqueda:** En ajedrez, hay ~10^154 nodos posibles, lo que hace inviable explorarlos todos
- **Solución:** Uso de **heurísticas** (evaluaciones aproximadas) y **técnicas de poda** (como alfa-beta) para reducir la búsqueda
## Estados, acciones, jugadores y reglas
### Componentes básicos
- **Estados**: Configuraciones posibles del juego (ejemplo: tablero de ajedrez en un momento dado)
- **Acciones:** Movimientos legales
- **Jugadores:** Agentes que interactúan
- **Reglas:** Definen cómo se actualiza el estado y cuando termina el juego

**Ejemplo en Tres en Raya**
- **Estado inicial:** Tablero vacío
- **Acciones:** Colocar una ficha **X** (max) o **O** (min) en una casilla libre
- **Terminación:** Tres fichas iguales en línea o tablero lleno sin ganador
### Representación: Árbol de juego
- **Nodos:** Estados del juego
- **Aristas:** Acciones que llevan de un estado a otro
- **Etiquetas**: Turnos (max o min)
- **Hojas:** Estados terminales (victoria, derrota o empate)

**Estructura del árbol**
- **Raíz:** Estado inicial (turno de max)
- **Niveles alternados:**  max y min se turnan
- **Hojas:** Valores de utilidad (ejemplo: infinito positivo para victoria de max)
### Función de utilidad
Definimos con esto el valor de un estado terminal para cada jugador
En juegos bipersonales de suma cero:
- *max* gana: U(s) = + inf
- *min* gana: U(s) = - inf
- Empate: U(s) = 0
**Importante:** Solo se aplica en estados terminales

**Casos especiales:**
- Juegos multijugador: El valor es un vector (ejemplo: (1, 2, 6) para tres jugadores)
## Estrategias y comportamientos en juegos
### Estrategias óptimas: minimax
- **Objetivo de *max***: maximizar su utilidad
- **Objetivo de *min***: minimizar la utilidad de *max*
- **Estrategia minimax:**
	- *max* elige la acción con el **mejor peor caso** (suponiendo que *min* responderá de forma óptima)

``` python
max  
├─ min (elige entre 3 y 12) → 3  
└─ min (elige entre 8 y 4) → 4
```
*max* elige la rama con el **mayor valor mínimo**
### Juegos multijugador y alianzas
- **Vector de utilidad:** Cada jugador tiene su propia recompensa en estados terminales
- **Alianzas**
	- Surgen cuando jugadores débiles cooperan contra uno fuerte
	- **Ejemplo:** En un juego de 3 jugadores, si C es el más fuerte, A y B pueden unirse para debilitarlo
	- **Riesgo:** Las alianzas pueden romperse si un jugador traiciona para obtener ventaja individual
### Comportamiento racional y limitaciones
- **Supuesto básico:** Todos los jugadores son racionales y actúan para maximizar utilidad
- **Limitaciones prácticas**
	- **Tiempo y recursos**: En juegos como el ajedrez, es imposible sacar todas las ramas
	- **Heurísticas:** Se usan evaluaciones aproximadas para guiar la búsqueda
	- **Poda alfa-beta:** Técnica para eliminar ramas innecesarias del árbol [[Tema 6 - Algoritmos mini-max y poda alfa-beta]]

**Ejemplo aplicado**:
- En el tres en raya, _max_ (X) puede **forzar siempre un empate** si juega óptimamente, pero no una victoria, debido a la simetría del juego.