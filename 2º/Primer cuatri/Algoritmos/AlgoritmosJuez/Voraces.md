#### Alfombra Roja

![[prob-AlfombraRoja.pdf]]

##### Entrada

``` python
# Entrada  
N = int(input())  
famosos = []  
nombresFamosos = []  
for _ in range(N):  
    datos = list(input().strip().split())  
    S = datos[0]  
    M = int(datos[1])  
    L = int(datos[2])  
    T = int(datos[3])  
    famosos.append((L/M, S, M, L, T))  
    nombresFamosos.append(S)  
famosos.sort(reverse=True)  
nombresFamosos.sort()
```

Una entrada sencilla pero que refleja perfectamente lo que nos pide el ejercicio. También nos ayudamos de una lista que recopile los nombres de los famosos para poder ordenarlos en orden alfabético y así tomarlos como referencia.

##### Función voraz

```python
def greedyFamosos(famosos, nombresFamosos):  
    minutos = 0  
    contador = 0  
    while famosos[contador][1] != nombresFamosos[0]:  
        minutos += famosos[contador][4]  
        contador += 1  
    return minutos
```

En este caso, iniciamos una variable que sirva como contador y otra para tener recopilados los minutos que tenemos que ir esperando. Para hallar cuántos minutos esperamos hasta el primer nombre ordenado alfábeticamente, nos valemos de una comparación en bucle while para saber si el famoso en el que estamos actualmente coincide con el primer famoso de nuestra lista ordenada por nombres. 

Si fuese así, devolvemos los minutos. En caso contrario, añadimos los minutos pertenecientes a ese otro famoso y seguimos sumando al contador para seguir iterando.

##### Salida

```python
# Salida  
minutosEspera = greedyFamosos(famosos, nombresFamosos)  
for famoso in famosos:  
    print(famoso[1])  
print(minutosEspera)
```

Poco que explicar, es una salida estandar que se asegura de cumplir a la perfección lo que solicita el ejercicio.
#### Negocios Espaciales

![[prob-Negocios espaciales.pdf]]

##### Entrada

```python
# Entrada  
N = int(input())  
valores = list(map(int, input().strip().split()))  
valores.sort(reverse=True)
```

Muy sencillo pero nos sirve así

##### Función voraz

```python
def greedyCoin(valores, n):  
    kMonedas = 0  
    sol = [0] * len(valores)  
    i = 0  
    while n > 0 and i < len(valores):  
        if valores[i] > n:  
            i += 1  
        else:  
            kMonedas += 1  
            n -= valores[i]  
            sol[i] += 1  
    return kMonedas, sol
```

Iniciamos una variable moneda y una lista del mismo tamaño que valores hayamos pasado.

Luego, metemos esto en un bucle, que se ejecutará mientras n no sea 0 (mientras haya dinero que cambiar) y i < len(valores), o lo que es lo mismo, que hayan todavía monedas de cambio que no hemos usado.

Si los el valor en la posición i de los valores que hemos pasado al programa es mayor que n, lo ignoramos, si no, lo que hacemos es sumar una moneda a nuestro mínimo de monedas que llevamos, restarle a n la parte que corresponde a ese valor en donde nos encontramos, y añadir en la posición de la lista sol que corresponde al valor de divisa un 1 para dejar en constancia que hemos usado una moneda de ese tipo.

#### Salida

```python
k, sol = greedyCoin(valores, N)  
print(k)  
for i in range(len(sol)):  
    if sol[i] > 0:  
        print(f"{valores[i]}:{sol[i]}")
```

Solo tenemos que imprimir el mínimo de monedas K y los valores tal y como vemos en el bucle.
#### Second Dates

![[prob-Second Dates.pdf]]

##### Entrada

```python
#Entrada  
N, K = map(int, input().strip().split())  
participantes = []  
for i in range(N):  
    datos = input().strip().split()  
    C = datos[0]  
    A = int(datos[1])  
    participantes.append((A, C))  
participantes.sort()
```

Entrada que se adhiere a lo solicitado por la práctica.

##### Función voraz

```python
def greedyDates(participantes, n, k):  
    Grupo1 = []  
    Grupo2 = []  
  
    Sum1 = 0  
    Sum2 = 0  
  
    participantesRest = len(participantes)-k  
  
    for posicion in range(len(participantes)):  
        jovenes = 0  
        mayores = 0  
        participanteAct = participantes[posicion]  
        if posicion < k:  
            jovenes = participanteAct[0]  
            Sum1 -= jovenes  
        else:  
            mayores = participanteAct[0]  
            Sum1 += mayores  
    for posicion in range(len(participantes)):  
        jovenes = 0  
        mayores = 0  
        participanteAct = participantes[posicion]  
        if posicion < n-k:  
            jovenes = participanteAct[0]  
            Sum2 -= jovenes  
        else:  
            mayores = participanteAct[0]  
            Sum2 += mayores  
    if Sum1 >= Sum2:  
        for posicion in range(len(participantes)):  
            participanteAct = participantes[posicion]  
            if posicion < k:  
                Grupo1.append(participanteAct[1])  
            else:  
                Grupo2.append(participanteAct[1])  
    else:  
        for posicion in range(len(participantes)):  
            participanteAct = participantes[posicion]  
            if posicion < n-k:  
                Grupo1.append(participanteAct[1])  
            else:  
                Grupo2.append(participanteAct[1])  
    return Grupo1, Grupo2
```

- **Inicialización de Variables**:
    - `Grupo1` y `Grupo2` son listas vacías que representarán los dos grupos de participantes, uno para los “jóvenes” y otro para los “no-tan-jóvenes”.
    - `Sum1` y `Sum2` son variables para almacenar las sumas de edades de cada grupo, utilizadas para comparar ambas distribuciones posibles de participantes.
    - `participantesRest` calcula cuántos participantes irán al segundo grupo dado que el primer grupo tendrá `k` participantes.
- **Cálculo de Sumas de Edades con dos Configuraciones**:
    - El algoritmo considera dos posibles formas de crear los grupos:
        - En la primera, los primeros `k` participantes (ordenados por edad) se asignan como el grupo de “jóvenes”, y el resto como el grupo de “no-tan-jóvenes”.
        - En la segunda, los primeros `n-k` participantes forman el grupo de “jóvenes” y los últimos `k` forman el grupo de “no-tan-jóvenes”.
    Cada bucle for en esta sección recorre la lista de participantes y actualiza `Sum1` y `Sum2` con la suma de edades para cada configuración de grupo.
- **Selección de la Configuración Óptima**:
    - La función compara las sumas `Sum1` y `Sum2`. La configuración que resulta en la mayor diferencia entre los grupos de edades se considera óptima.
    - Según esta comparación, se decide qué configuración de grupos se usará:
        - Si `Sum1` es mayor o igual que `Sum2`, se asigna la primera configuración, y viceversa.
- **Asignación de Participantes a Grupos**:
    - Basado en la comparación anterior, los participantes se asignan a `Grupo1` y `Grupo2` de acuerdo con la configuración óptima seleccionada.
    - Finalmente, la función retorna `Grupo1` y `Grupo2`.

##### Salida

```python
G1, G2 = greedyDates(participantes, N, K)  
  
for elem in G1:  
    print(elem, end=' ')  
print()  
for elem in G2:  
    print(elem, end=' ')
```

#### Velada IV

![[prob-A Por la Velada del Año IV.pdf]]

##### Entrada

```python
# Entrada  
N = int(input())  
actividades = []  
for i in range(N):  
    datos = input().strip().split()  
    S = datos[0]  
    I = int(datos[1])  
    F = int(datos[2])  
    actividades.append((F, I, S))  
actividades.sort()
```

Nuevamente, una entrada básica que se apega al objetivo de la práctica.

##### Función voraz

```python
def greedyVelada(actividades):  
    profit = 0  
    cost = 0  
    for i in range(len(actividades)):  
        actividad_actual = actividades[i]  
        if actividad_actual[1] >= cost:  
            cost = actividad_actual[0]  
            profit += 1  
    return profit
```

Esta función es un poco más compleja, vamos a desglosar cómo funciona:

- Esta función recibe la lista `actividades` ya ordenada por `F` y realiza la selección de actividades sin solapamiento.
- Se inicializan dos variables: `profit`, que cuenta el número de actividades seleccionadas, y `cost`, que mantiene el instante en el que termina la última actividad seleccionada.

- **Iteración sobre las Actividades**:
    
    - La función itera sobre cada actividad en la lista ordenada.
    - En cada iteración, se evalúa si el inicio de la actividad actual (`actividad_actual[1]`) es mayor o igual a `cost` (momento en que termina la última actividad seleccionada).
        - **Condición**: Si es así, significa que la actividad actual no se solapa con la última seleccionada, por lo que puede incluirse.
        - **Actualización**: En ese caso, se actualiza `cost` al momento de finalización de la actividad actual (`actividad_actual[0]`) y se incrementa `profit` en 1.

##### Salida

```python
sol = greedyVelada(actividades)  
print(sol)
```

Creo que no hay mucho que comentar de esta salida

#### Vuelta a la Tierra

![[prob-Vuelta a la Tierra.pdf]]

##### Entrada

```python
# Entrada  
N, M = map(int, input().strip().split())  
objetos = []  
for i in range(M):  
    V, P = map(int, input().strip().split())  
    objetos.append((P/V, V, P, i))  
objetos.sort()
```

##### Función voraz

```python
def greedyBag(objetos, N):  
    profit = 0  
    peso_actual = 0  
    objeto_actual = 0  
    backpack = [0] * len(objetos)  
    while objeto_actual < len(objetos) and peso_actual <= N:  
        obj = objetos[objeto_actual]  
        if obj[2] + peso_actual <= N:  
            peso_actual += obj[2]  
            profit += obj[1]  
            backpack[obj[3]] = 1  
        else:  
            proportion = (N - peso_actual) / obj[2]  
            profit += proportion * obj[1]  
            backpack[obj[3]] = proportion  
        objeto_actual += 1  
    return profit, backpack
```

Aquí tenemos que hacer una determinada serie de cosas:

1. Definir nuestros elementos a uso: `profit`, `peso_actual`, `objeto_actual`, `backpack` (que es una lista del tamaño de los objetos que tenemos disponibles)
2. Preparar un bucle: Nuestra condición será que debe de haber objetos a los que referenciar (objeto_actual < len(objetos)) y que no nos pasemos del peso máximo N (peso_actual) <= N

Dentro de este bucle, evaluamos si el peso del siguiente objeto candidato a ser añadido y el peso que ya llevamos es menor o igual al máximo. Si se cumple, pues actualizamos el peso actual, añadimos el valor del objeto y añadimos el objeto a nuestra lista mochila.

En caso contrario, calculamos una proporción en base al peso máximo, el actual y el del nuevo objeto. Le sumamos esto al beneficio multiplicado por la relación peso/valor que calculamos en la entrada. 

Asimismo, imponemos el coste como máximo, ya que ya tenemos la mochila llena y decimos que nuestra mochila en esa posición tendrá el valor de la proporción.

##### Salida

```python
sol, mochila = greedyBag(objetos, N)  
  
print("{:.2f}".format(sol))  
print(mochila)
```

Una salida básica para dar fin a esta primera serie de ejercicios de voraces. Véase [[Voraces_Grafos]] para más.

