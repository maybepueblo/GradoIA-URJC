## Estudio del algoritmo Mini-Max

**Definición y objetivo**:
El algoritmo mini-max es una estrategia para juegos bipersonales de suma cero (como ajedrez o tres en raya), donde dos jugadores (MAX y MIN) actúan de forma adversarial. MAX busca maximizar su utilidad, mientras que MIN intenta minimizarla. El objetivo es determinar la jugada **óptima** para MAX, asumiendo que MIN responderá de manera óptima en cada turno.

**Funcionamiento**
1. **Generación del árbol del juego**
	- Se expanden todos los posibles movimientos hasta un nivel de profundidad
	- Los nodos se clasifican en:
		- **MAX**: Decisiones del jugador maximizador
		- **MIN:** Decisiones del adversario minimizador
		- **Terminales:** Estados finales con valores de utilidad (ejemplo infinito si gana MAX, menos infinito si gana MIN)
2. **Propagación de valores**
	- En nodos **MAX**: Seleccionamos **valor máximo** de los hijos
	- En nodos **MIN:** Seleccionamos **valor mínimo** de los hijos
	- Los valores se propagan desde los nodos terminales hasta la raíz

**Ejemplo (Tres en raya)**:
- Si MAX tiene tres opciones (a1, a2, a3), y los hijos de a1 son nodos MIN con valores [+∞, +∞, -∞], MIN elegirá -∞.
- MAX seleccionará la acción con el mejor valor garantizado (por ejemplo, a1 si su valor propagado es 3, mejor que otras opciones).

**Complejidad**:
- Sin optimizaciones: O(b^d), donde b es el factor de ramificación y d la profundidad del árbol.
## Aplicación de la técnica de poda alfa-beta
**Motivación**
El mini-max explora nodos innecesarios. La **poda alfa-beta** optimiza el proceso eliminando ramas que no afectarán el resultado final.

**Conceptos clave**
- **α (alpha)**: Mejor valor encontrado para MAX (inicialmente -∞) 
- **β (beta)**: Mejor valor encontrado para MIN (inicialmente +∞)

**Condiciones de poda:**+
1. **Poda alpha en nodos MIN**
	- Si el valor actual beta es menor o igual que alpha, se descartan los hijos restantes
	- *Ejemplo:* Sin MIN tiene un hijo con valor 3 y alpha = 5, no se exploran más hijos porque MIN ya no elegirá un valor mayor que 3.
2. **Poda beta en nodos MAX**
	- Si el valor actual alpha es mayor o igual que beta, se podan los hijos restantes
	- *Ejemplo:* Si MAX tiene un hijo con valor 8 y beta = 5, MAX ya no elegirá un valor menor que 8.1

``` python
def MaxValor(estado, α, β):
    if es_terminal(estado):
        return utilidad(estado)
    for hijo in expandir(estado):
        α = max(α, MinValor(hijo, α, β))
        if α ≥ β:
            return α  # Poda β
    return α

def MinValor(estado, α, β):
    if es_terminal(estado):
        return utilidad(estado)
    for hijo in expandir(estado):
        β = min(β, MaxValor(hijo, α, β))
        if β ≤ α:
            return β  # Poda α
    return β
```

**Eficiencia**
- **Mejor caso:** O(b^d/2) reduce el árbol a la mitad
- *Ejemplo práctico*: En un árbol con valores [3, 12, 8] al evaluar el primer hijo (3), MIN sabe que MAX no elegirá un valor menor que 3, por lo que ignora los hijos restantes
## Algoritmo expect-mini-max (juegos con azar)

**Contexto**
Para juegos con elementos aleatorios, se introduce un nuevo tipo de nodo: "**azar**", que representa eventos probabilísticos

**Funcionamiento:**
1. **Nodos azar**
2. **Propagación de valores**

**Ejemplo (Backgammon simplificado):**
- Estado inicial: (0,0,5,5). MAX mueve una ficha a (4, 4) o (3, 5)
- El dado puede dar 1 o 2 (probabilidad 1/2 para cada opción)
	- Para (4, 4, 1, 2): Valor esperado = 0.5 x 11 + 0.5 x 10 = 10.5
	- MAX elige la jugada con mayor valor esperado

**Complejidad**
- **O(b^d · n^d)** donde n son las opciones aleatorias (ejemplo: 21 combinaciones de dados en backgammon)

**Heurísticas**
- Las funciones de evaluación e(s) deben estimar la probabilidad de ganar
- *Ejemplo: En backgammon, e((a, b, c, d))* = a + b - c - d, donde a, b son posiciones propias y c, d del oponente
