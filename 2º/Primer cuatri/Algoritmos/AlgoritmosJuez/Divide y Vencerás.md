#### Ciega a citas

![[prob-Ciega a citas.pdf]]

##### Entrada 

```python
# Entrada  
N = int(input())  
reservas = list(map(int, input().strip().split()))  
M = int(input())  
acompanantes = list(map(int, input().strip().split()))  
P = int(input())  
parejas = []  
for i in range(P):  
    P1, P2 = map(int, input().strip().split())  
    parejas.append((P1, P2))
```

##### Funciones dyv

```python
def busquedaBin(lista, objetivo):  
  
    inicio = 0  
    fin = len(lista)-1  
  
    while inicio <= fin:  
        medio = (inicio+fin)//2  
        if lista[medio] == objetivo:  
            return medio  
        elif lista[medio] < objetivo:  
            inicio = medio+1  
        else:  
            fin = medio-1  
  
    return -1  
  
def resolver_citas(reservas, acompanantes, parejas):  
    # Esta lista nos va a devolver nuestros resultados  
    resultados = []  
    for persona1, persona2 in parejas:  
  
        # Tenemos que buscar a cada persona en cada grupo  
        posicion1 = busquedaBin(reservas, persona1)  
  
        # Repetimos con la siguiente  
        posicion2 = busquedaBin(acompanantes, persona2)  
  
        # Verificamos si están las dos personas, si falta una o las dos es un PLANTON  
        if posicion1 == -1 or posicion2 == -1:  
            resultados.append("PLANTON")  
        else:  
            resultados.append(f"{posicion1} {posicion2}")  
    return resultados
```

Aquí nos valemos de dos funciones vitales para solucionar este problema. Primero que todo tenemos la búsqueda binaria y luego nuestra resolución:

- **Búsqueda binaria** -> En ella, primero iniciamos unas variables que señalen al inicio (siempre cero) y luego al final (el tamaño del conjunto menos uno). Mientras que el inicio no llegue al final, iteramos por el array.
	- Definimos el *medio* como la suma de estas variables anteriores a la mitad.
	- Si en el medio de la lista está el objetivo, devolvemos el medio, si no, analizamos si el valor en el medio es menor (ya que sabemos que la lista viene ordenada).
		- Si lo es, repetimos la búsqueda pero esta vez en un array cuyo inicio es la mitad + 1 (ya que sabemos que no es la mitad).
		- Si no, acortamos el array hasta medio - 1 (nuevamente, sabemos que el medio no es)
	- Devolvemos -1 si no hemos encontrado nada

- **Resolver citas** -> Por cada conjunto de personas (la tupla (P1, P2) que creamos en la salida) vemos si encontramos a esa persona en el array de tanto reservas como de los acompañantes. Si uno de estos no está, es un PLANTON, si no, los devolvemos como que si están.

##### Salida

```python
solucion = resolver_citas(reservas, acompanantes, parejas)  
for i in range(len(solucion)):  
    print(solucion[i])
```

#### Clear Souls

![[prob-Clear Souls.pdf]]

##### Entrada

```python
N = int(input())  
niveles = list(map(int, input().strip().split()))  
M = int(input())  
nivel_caballero = []  
for i in range(M):  
    Q = int(input())  
    nivel_caballero.append(Q)
```

##### Funciones

```python
def busqueda_Souls(lista, objetivo):  
  
    inicio = 0  
    fin = len(lista)-1  
    ultima_valida = -1  
  
    while inicio <= fin:  
        medio = (inicio+fin)//2  
        if lista[medio] <= objetivo:  
            ultima_valida = medio  
            inicio = medio + 1  
        else:  
            fin = medio - 1  
  
    return ultima_valida  
  
def clearSouls(niveles, nivel_caballero):  
    lista_acumulada = [0] * len(niveles)  
    for i in range(len(niveles)):  
        lista_acumulada[i] = lista_acumulada[i-1] + niveles[i]  
  
    casos = []  
  
    for i in range(len(nivel_caballero)):  
        nivel_actual = nivel_caballero[i]  
        posicion = busqueda_Souls(niveles, nivel_actual)  
        if posicion != -1:  
            num_enemigos = posicion + 1  
            puntos = lista_acumulada[num_enemigos-1] # Sumamos hasta el número de enemigos que podemos cargarnos  
            casos.append(f"{num_enemigos} {puntos}")  
        else:  
            casos.append(f"{0} {0}")  
  
    return casos
```

- **Busqueda Souls** -> Mismo esquema que la búsqueda binaria, pero tenemos en cuenta la última posición valida, ya que hasta ella recorremos el vector para sumar todos los puntos. Así, como nos interesa todo lo que precede al objetivo, simplemente tenemos que imponer que cada vez que encontremos que la lista en su mitad es menor o igual a objetivo, la última que fue válida fue esa mitad. Si no fuese así, solamente acortamos el array.

- **Clear Souls** -> Teniendo nuestra posición, vamos a hacer una función que sirva para tener todas las puntuaciones acumuladas (por el bien de nuestra eficiencia algorítmica). Teniendo eso, simplemente nos queda buscar en cada caso de prueba de nuestro caballero. Ahí tendremos el nivel actual y la posicion donde nos encontramos. Si esta posición no es nula entonces tenemos que podemos matar a cierto num_enemigos (por ejemplo si posición es igual a 3) podemos matar cuatro enemigos.
	- Teniendo esto, solo nos queda guardar nuestros puntos como la posición de la lista sumatorio que hicimos antes en la posición de num_enemigos menos 1 (por temas de índices en programación) y así guardamos el caso que tenemos.

##### Salida

```python
casos = clearSouls(niveles, nivel_caballero)  
  
for caso in casos:  
    print(caso)
```

#### Rey de diamantes

![[prob-Rey de Diamantes.pdf]]

##### Entrada

1. El programa pide al usuario el tamaño `N` de la matriz, que será una matriz cuadrada de `N x N`.
2. Luego, el programa recibe los elementos de la matriz, fila por fila. Cada fila se lee como una lista de enteros y se almacena en una lista de listas llamada `matriz`.
3. Después, el programa recibe una lista de números, `eliminados`, que representa los elementos que deben ser marcados como "X" en la matriz.
##### Funciones

###### 1. `busqueda_binaria_fila(matriz, ini, fin, elem)`
Esta función realiza una **búsqueda binaria** sobre las filas de la matriz para encontrar una fila específica que contenga el elemento `elem` en su primera columna. En caso de no encontrarlo, devuelve la fila más cercana en la que debería estar el elemento.

```python
def busqueda_binaria_fila(matriz, ini, fin, elem):
```

- **Parámetros**:
  - `matriz`: la matriz en la cual se buscan los elementos.
  - `ini` y `fin`: índices que representan el rango de filas en la matriz donde se está buscando.
  - `elem`: el elemento que queremos encontrar.

1. **Condición base**:
   ```python
   if fin < ini:
       return fin
   ```
   Si `fin < ini`, la función concluye que el elemento no está en ninguna de las filas en el rango de búsqueda y devuelve `fin`, que sería el índice más cercano.

2. **Caso cuando `fin` es igual a `ini`**:
   ```python
   if fin == ini:
       if matriz[fin][0] == elem:
           return fin
   ```
   Si solo queda una fila (`fin == ini`), la función verifica si el primer elemento en esa fila es `elem`. Si es igual, devuelve el índice de la fila (`fin`).

3. **Comparación de elementos**:
   - Si `elem` es menor que `matriz[fin][0]`, `elem` debería estar antes de esta fila. Si `fin` es la primera fila, la función devuelve `fin`; si no, devuelve `fin - 1`.
   - Si `elem` es mayor, se intenta buscar en la fila siguiente.

4. **División en mitades**:
   ```python
   mid = (fin + ini) // 2
   ```
   La función calcula el índice medio `mid` para dividir el rango de búsqueda.

5. **Llamadas recursivas**:
   - Si `elem > matriz[mid][0]`, la búsqueda continúa en la mitad derecha:
     ```python
     return busqueda_binaria_fila(matriz, mid + 1, fin, elem)
     ```
   - Si `elem < matriz[mid][0]`, la búsqueda continúa en la mitad izquierda:
     ```python
     return busqueda_binaria_fila(matriz, ini, mid - 1, elem)
     ```

###### 2. `busqueda_binaria_columna(fila, ini, fin, elem)`
Esta función realiza una **búsqueda binaria** en una fila específica (ya localizada en `busqueda_binaria_fila`) para encontrar la columna donde se encuentra el elemento `elem`. Si no lo encuentra, devuelve el índice donde debería estar.

```python
def busqueda_binaria_columna(fila, ini, fin, elem):
```

1. **Condición base**:
   ```python
   if fin < ini:
       return ini
   ```
   Si `fin < ini`, la función devuelve `ini`, que sería el índice más cercano donde debería estar `elem`.

2. **Cálculo del índice medio**:
   ```python
   mid = (fin + ini) // 2
   ```

3. **Comparación y llamadas recursivas**:
   - Si el elemento en `fila[mid]` es igual a `elem`, devuelve `mid` porque el elemento fue encontrado.
   - Si `elem > fila[mid]`, busca en la mitad derecha:
     ```python
     return busqueda_binaria_columna(fila, mid + 1, fin, elem)
     ```
   - Si `elem < fila[mid]`, busca en la mitad izquierda:
     ```python
     return busqueda_binaria_columna(fila, ini, mid - 1, elem)
     ```

###### 3. `poner_X(matriz, f, col, N)`
Esta función se encarga de **poner una "X" en la matriz** en la posición `(f, col)`, correspondiente a un elemento de la lista `eliminados`.

```python
def poner_X(matriz, f, col, N):
```

1. **Condiciones de salida (fuera de rango)**:
   ```python
   if f > N - 1 or col > N - 1:
       return
   ```
   Si `f` o `col` están fuera del rango de la matriz, la función se detiene.

2. **Ajuste de columna negativa**:
   ```python
   if col < 0:
       return poner_X(matriz, f, col + 1, N)
   ```
   Si `col` es menor que 0, `poner_X` corrige `col` incrementándolo por 1.

3. **Marcado de la posición con "X"**:
   ```python
   if matriz[f][col] != "X":
       matriz[f][col] = "X"
       return
   ```
   Si la posición `(f, col)` no tiene "X", coloca una "X" y termina la función.

4. **Condiciones para avanzar**:
   - Si está en la última columna y última fila, no hay más posiciones que modificar y la función se detiene:
     ```python
     if f == N - 1 and col == N - 1:
         return
     ```
   - Si está en la última columna de la fila, avanza a la siguiente fila y vuelve a la primera columna (`col = 0`):
     ```python
     if col == N - 1:
         f += 1
         col = 0
         return poner_X(matriz, f, col, N)
     ```
   - Si no está en la última columna, avanza a la columna siguiente:
     ```python
     if col < N - 1:
         col += 1
         return poner_X(matriz, f, col, N)
     ```

Estas tres funciones trabajan juntas para buscar la posición de cada elemento en `eliminados`, y luego marcarlo con "X" en la matriz.
##### Salida

1. Tras realizar las modificaciones en la matriz, el programa imprime el contenido de la matriz modificada, fila por fila. Cada valor se imprime seguido de un espacio para que tenga una disposición en forma de matriz cuadrada, donde los valores eliminados aparecen como "X".
#### Yo soy tu padre

![[prob-Yo soy tu padre.pdf]]

##### Entrada

```python
N = int(input())  
familias = []  
for i in range(N):  
    enteros = list(map(int, input().split()))  
    familias.append(enteros)  
M = int(input())  
miembros = []  
for i in range(M):  
    miembro = int(input())  
    miembros.append(miembro)
```
##### Funciones

```python
# Función improvisada que furula para crear un árbol en un diccionario  
def arbol(familias):  
    tree = {}  
    # Para cada padre que tiene cierta dirección a un nodo hijo en nuestras familias, lo asignamos en el conjunto  
    for parent, *children in familias:  
        tree[parent] = children  
    return tree  
  
  
def calcular_niveles(arbol, niveles, actual=0, nivel=1, visitado=None):  
  
    # Iniciamos el conjunto de visitado  
    if visitado is None:  
        visitado = set()  
  
    if actual in visitado:  
        return  
  
    visitado.add(actual)  
    niveles[actual] = nivel  
  
    if actual not in arbol or not arbol[actual]:  
        return  
  
    hijos = arbol[actual]  
    medio = len(hijos)//2  
  
    for hijo in hijos[:medio]:  
        calcular_niveles(arbol, niveles, hijo, nivel+1, visitado)  
    for hijo in hijos[medio:]:  
        calcular_niveles(arbol, niveles, hijo, nivel+1, visitado)
```

Como se puede ver, primero he creado una función que imita el tener el tipo de dato de un árbol, pero nada, no es difícil. Hay que pensar en ella así:
- Por cada padre que apunta hacia sus hijos en la lista de la familia, asignamos al arbol la estructura de que ese arbol en la posicion padre, son sus hijos.

Luego, nos servimos de esto para aplicar un esquema de divide y vencerás:

- Iniciamos la variables visitado, que será un conjunto (no repetición)
- Si el actual está ahí, no tiene caso hacer nada, salimos porque ya hemos acabado.
	- Si no, simplemente asignamos ese actual como ya visitado y seguimos al siguiente nivel. 
		- Si este actual no está en el arbol, salimos
		- En caso contrario, lo que buscamos es meternos en el lado de los hijos, hallar la mitad de los mismos y en cada mitad, aplicar nuestro algoritmo para saber si se encuentra por la mitad izquierda de nuestro arbol o la derecha.

##### Salida

```python
tree = arbol(familias)  
niveles = {}  
calcular_niveles(tree, niveles, 0, 1)  
  
# Usar un metodo de python que dado un diccionario obtiene el valor de una clave, en caso contrario, imprime -1  
for miembro in miembros:  
    print(niveles.get(miembro, -1))
```

Aquí lo único extraño es que usamos dict.get() que nos ayuda a obtener un valor de un diccionario, dándonos la posibilidad de que si este valor no existe, imprimamos otra cosa, en este caso un -1.




