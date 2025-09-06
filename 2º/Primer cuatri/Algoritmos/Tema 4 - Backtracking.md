### **Introducción**

Ciertos pclroblemas requieren realizar una búsqueda exhaustiva por el espacio de posibles soluciones hasta encontrar una solución o constatar que no existe. Para ello, utilizamos el esquema de **Vuelta Atrás (Backtracking)**, que genera de forma **sistemática** posibles soluciones.

El espacio de soluciones se plantea como un **grafo (o árbol) implícito**, donde cada nodo representa una decisión o una solución parcial.

#### **Casos de uso**

1. **Encontrar una solución**: Paramos en cuanto encontramos la primera solución factible.
2. **Encontrar todas las soluciones**: Recorremos todo el espacio de soluciones para enumerarlas.
3. **Encontrar la mejor solución**: Evaluamos todas las soluciones y devolvemos la más óptima según un criterio (e.g., mayor valor en el problema de la mochila).

#### **Árbol implícito**

Este modelo:

- Nos permite **recorrer soluciones de forma eficiente** sin almacenar todas las posibles combinaciones.
- Realiza un recorrido **en profundidad** en un grafo dirigido sin ciclos, conocido como el **Árbol de Exploración**.

![[Árbol implícito Backtracking|500]]

---

### **Estrategia general**

#### **Construcción y poda**

1. A medida que progresamos, construimos soluciones parciales representadas por una **n-tupla**.
2. Al llegar a un nodo hoja:
    - Si la solución no es válida o completa, hacemos **backtracking**:
        - Eliminamos el último elemento de la tupla.
        - Probamos con otro elemento disponible.
    - Si la solución es válida y completa:
        - **Detenemos el algoritmo** (si buscamos una única solución).
        - **Continuamos explorando** (si buscamos todas o la mejor solución).

#### **N-tupla**

- Una solución es **factible** si satisface restricciones:
    - **Restricciones explícitas**: Limitaciones individuales de cada componente (e.g., "el peso del objeto debe ser ≤ capacidad").
    - **Restricciones implícitas**: Relaciones entre componentes (e.g., "no puede haber reinas en la misma diagonal").

#### **Árbol de exploración**

- Organiza el **espacio de soluciones factibles**.
- Cada nodo representa:
    - Una tupla parcial (potencialmente prometedora).
    - Una tupla completa (solución factible).
- Usa una **función de poda** para descartar tuplas no prometedoras, mejorando la eficiencia.

#### **¿Cuándo usar Backtracking?**

1. Cuando las soluciones se pueden expresar como una **n-tupla**.
2. Si podemos realizar un recorrido **en profundidad** sobre un árbol implícito.
3. Si las etapas del problema corresponden a **niveles en el árbol de búsqueda**.

> **Nota**: Backtracking es viable cuando el espacio de soluciones es manejable, usualmente con entradas pequeñas (complejidad O(n!)).

---

### **Esquema de la técnica**

```python
procedimiento VueltaAtras(v[1..k]):
    si EsSolucion(v[1..k]) entonces
        escribir v  # O almacenar v
    sino:
        para ei en {e1, .., ej} hacer:  # Posibles opciones
            v[k+1] ← ei
            si EsPrometedor(v[1..k+1]) entonces:
                VueltaAtras(v[1..k+1])
            fsi
        fpara
fsi
fprocedimiento
```

### **Ejemplos prácticos**

#### **1. Mochila (Backtracking)**

Tienes una mochila con límite de peso y debes maximizar el valor total de los objetos que puedes cargar. Cada objeto tiene un peso `w[k]` y un valor `v[k]`.

**Código del algoritmo**:

```python
funcion mochilaVA(i, r: entero): entero:
    # i: índice del objeto actual
    # r: capacidad restante de la mochila
    b ← 0
    para k ← i hasta n hacer:
        si (w[k] ≤ r) entonces:
            b ← max(b, v[k] + mochilaVA(k, r - w[k]))
        fsi
    fpara
    devolver b
ffuncion
```

#### **2. Problema de las N-Reinas**

Colocar `N` reinas en un tablero de ajedrez (`N x N`) sin que se ataquen entre sí.

- Representamos el tablero como un vector `tablero[1..N]`, donde cada posición indica en qué columna está la reina en una fila específica.
- Aplicamos restricciones de:
    - Fila (por construcción).
    - Columna (sin repetición).
    - Diagonales (evitando conflictos).

**Esquema simplificado**:

```python
procedimiento n_reinas(k, col, diag45, diag135):
    si k = N entonces:
        escribir solución
    sino:
        para j ← 1 hasta N hacer:
            si (j no en col y j-k no en diag45 y j+k no en diag135) entonces:
                sol[k+1] ← j
                n_reinas(k+1, col ∪ {j}, diag45 ∪ {j-k}, diag135 ∪ {j+k})
            fsi
        fpara
fsi
```
#### **3. Laberinto**

Encuentra un camino desde la entrada `[1, 1]` hasta la salida `[N, N]` en una matriz `N x N` donde:

- `0`: Casilla transitable.
- `∞`: Obstáculo.

**Pseudocódigo**:

```python
procedimiento Laberinto(f, c, k, tab):
    tab[f, c] ← k
    si (f = N) y (c = N) entonces:
        MostrarSolucion(tab)
    sino:
        para cada dirección (arriba, abajo, izquierda, derecha) hacer:
            si EsPosible(tab, nueva_f, nueva_c) entonces:
                Laberinto(nueva_f, nueva_c, k+1, tab)
            fsi
        fpara
    tab[f, c] ← 0  # Backtracking: deshacer el movimiento
fsi
```

### **Notas finales**

Con esta técnica puedes resolver problemas combinatorios que requieren evaluar muchas posibilidades. El uso de poda y estructuras como árboles implícitos hace que Backtracking sea práctico para problemas con entradas pequeñas, permitiendo explorar soluciones sistemáticamente.

