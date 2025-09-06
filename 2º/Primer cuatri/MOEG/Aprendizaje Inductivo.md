Primer colab en la serie de notebooks dados por el profesorado de MOEG.

Definamos brevemente dos funciones, `plot_f` y `plot_df`, las cuales sirven para graficar una función en su intervalo y para trazar una tangente, respectivamente.

```python
import numpy as np
import matplotlib.pyplot as plt

# plot a function from i0 to i1
def plot_f(f, i0, i1):
	x = np.arrange(i0, i1, 0.1)
	y = f(x)
	plt.plot(x, y)

# plot tangent line at point f(w) in domain
def plot_df(f, df, w):
	# work out line parameters
	# prediction point for given weights w
	y = f(w)
	m = df(w)
	c = y-m*w
	# plot prediction point y
	plt.plot(w, y, "*")
	x = np.arrange(w-1,w+1,0.1)
	y = m*x+c
	plt.plot(x, y)
```

Ahora definamos ciertos datos:

``` python
Dx = [-2, 4.5, 6.2]
Dy = [7, 9, 18]
```

Y ahora graficamos los puntos:

```python
plt.plot(Dx, Dy, "*", color = "blue")
plt.show()
```

Este es el resultado del código de arriba:

![[Pasted image 20241013180507.png]]

#### Función lineal

Vamos a definir una función f(w, x) que representa una línea recta (regresión lineal) con una pendiente w1 y un término independiente w0. La usamos para calcular la predicción y a partir de los valores de x y w `(y = w1*x + w0)`

``` python

w = [0.9, 9.2]
def f(w, x):
	w1 = w[1] # pendiente
	w0 = w[0] # término independiente
	# y = w1*x + w0 es la fórmula que comentábamos anteriormente
	m = w1
	b = w0
	y = m*x + b
	return y

def pf(x):
	y = w[1]*x+w[0]
	return y
```

Ahora grafiquemos la función:

```python
plot_f(pf, -4, 8)
plt.plot(Dx, Dy, "*", color="blue")
plt.show()
```

Este es el resultado:

![[Pasted image 20241013181152.png]]

#### Matrices

Ahora, probaremos a representar datos en forma matricial para realizar cálculos vectoriales eficientes. Usaremos una matriz `x` que incluye una fila de 1's (término independiente) y otra fila con los valores de `Dx`. Los valores de salida `y` también se representan en forma de matriz.

``` python
# Datos, primera fila de 1's representan datos para el término independiente
x = np.matrix([[1.0, 1.0, 1.0], [-2.0, 4.5, 6.2]])
y = np.matrix([7.0, 9.0, 18.0])

# Parámetros iniciales
w = np.matrix([5.0, 1.2])
```

Recordamos la función para graficar la recta y la derivada:

``` python
# Función de la expresión lineal
def f(w, x):
	y = w*x
	return y

# Función de la derivada
def df(w, x):
	return x
```

Ahora podemos evaluar los datos con una llamada

``` python
f(w, x)

y - f(w, x)
```

Esto nos ha de devolver para f(w, x) que `matrix([[2.6, 10.4, 12.44]])` y para y - f(w, x) nos pasa lo siguiente: `matrix([[4.4, -1.4, 5.56]])`.

#### Previo a la función de costo

A partir de este segmento, primero hemos de definir unas funciones auxiliares para el visualizado:

``` python
# Visualizer

#Funciones auxiliares para Colab

# plot a function f from i0 to i1

def plot_f(f,i0,i1):
	x=np.arange(i0,i1,0.1)
	y=f(x)
	plt.plot(x,y)

# plot tangent line at point f(w) in w domain

def plot_df(f,df,w):
	# work out line parameters
	# prediction point for given weights w
	y=f(w)
	m=df(w)
	c=y-m*w
	# plot prediction point y
	plt.plot(w,y,"*")
	# plot tangent line at y
	x=np.arange(w-1,w+1,0.1)
	y=m*x+c
	plt.plot(x,y)

# Visualización

#Matrix version of linear model

def plots():
	#plotting, don't pay attention to this.
	plt.figure()
	plot_f(lambda x:w[0,1]*x+w[0,0],-4,7)
	plt.plot(x[1],f(w,x),"*",color="red")
	plt.plot(x[1],y,"*",color="blue")
	plt.show()
#plotting
plots()
```

Expliquemos para qué funciona cada parte de este código:
##### 1. **Función `plot_f(f, i0, i1)`**:

- Esta función toma como parámetros una función `f` y dos límites, `i0` e `i1`, para definir un rango de valores en el eje x.
- Usa `np.arange(i0, i1, 0.1)` para crear los puntos en el eje x entre esos dos valores.
- Después, evalúa `y = f(x)` para cada valor de `x` en ese rango y genera la gráfica con `plt.plot(x, y)`.

##### 2. **Función `plot_df(f, df, w)`**:

- Esta función está destinada a graficar la tangente de la función `f` en un punto específico `w`.
- `f(w)` calcula la predicción en ese punto.
- `df(w)` es la derivada de la función en `w`, que corresponde a la pendiente de la línea tangente.
- La fórmula `y = mx + c` se utiliza para graficar la recta tangente, donde `m` es la pendiente, y `c` es el término independiente calculado como `y - m*w`.
- También grafica el punto `w` sobre la recta.

##### 3. **Función `plots()`**:

- En esta función, se define la gráfica de la función lineal ajustada. `plot_f(lambda x: w[0,1]*x + w[0,0], -4, 7)` genera la línea recta a partir de los coeficientes `w`.
- Se grafica un conjunto de puntos: los valores reales de `y` con color azul (`plt.plot(x[1], y, "*", color="blue")`) y los valores predichos con color rojo (`plt.plot(x[1], f(w, x), "*", color="red")`).

###### **Gráfica generada**:

En la imagen siguiente podemos ver:

- **Estrellas azules**: Estos son los puntos reales de los datos originales (`Dx`, `Dy`), es decir, las observaciones que estás intentando ajustar.
- **Estrellas rojas**: Son los valores que la línea de regresión ha predicho para esos mismos puntos de `x`. Indican la precisión de la línea ajustada.
- **Línea azul**: Es la recta que representa la función de regresión lineal que se ha calculado con los parámetros actuales `w`.

![[Pasted image 20241013183108.png]]
##### **Interpretación del resultado**:

- La línea azul es la predicción que hace el modelo para los valores de `y` basados en los datos de `x`.
- Cuanto más cerca estén las estrellas rojas de las azules, mejor ajusta el modelo los datos reales. En este caso, puedes ver que los puntos rojos se encuentran bastante cerca de los azules, lo que indica que el modelo está logrando un ajuste decente, aunque no perfecto.

##### 1. **Fórmula `r = y - f(w, x)`**:

- `r` representa el **residuo** o error entre los valores reales de salida (`y`) y los valores predichos por el modelo (`f(w, x)`).
- La función `f(w, x)` está calculando las predicciones del modelo, que es la recta ajustada.
- Entonces, `r` es simplemente la diferencia entre los valores reales (`y`) y las predicciones del modelo. Este valor te dice, para cada punto de datos, cuán lejos está la predicción del valor real. Si el modelo predice perfectamente, el residuo sería 0.

##### 2. **Fórmula `r * r.T`**:

- Aquí estás calculando el **producto matricial** del residuo con su **transpuesta**. Esto se usa para calcular el **error cuadrático** total del modelo.
- En este contexto, `r` es un vector columna (unidimensional), y `r.T` es su transpuesta (un vector fila). El producto `r * r.T` es la suma de los cuadrados de los residuos.
- Al multiplicar `r * r.T`, estás obteniendo una matriz 1x1 que contiene la suma de los errores al cuadrado, también conocido como el **error cuadrático total** (o **suma de errores cuadráticos**).
- Esta es una métrica clave en la regresión lineal porque te indica la magnitud total del error entre tus predicciones y los valores reales. Mientras más pequeño sea el valor, mejor es el ajuste del modelo.

#### Función de costo

Ahora sí podemos hallar y definir la función de costo que calcula la suma de los errores cuadráticos (residuos) entre los valores predichos y los reales.

``` python
# Loss function 
def Cf(w, x, y):
	r = y-f(w, x) # residuo
	l = r*r.T
	return l[0, 0]
# this value is equal to the not matrix version from before 
print("Loss=%0.3f" % Cf(w, x, y))
```

Este valor que nos da: `Loss = 52.234` debe de en parte referenciar al mismo valor anterior de `r*r.T = matrix([52.2336])`.

#### Derivada de la función de costo (dCf) o gradiente

Casi llegando al final, nos queda definir la función que calcula el gradiente de la función de costo con respecto a los parámetros w.

```
def dCf(w, x, y):
	r = y-f(w, x)
	dCfw = -2*r*x.T
	return dCfw
print("ciuesta w[1] = %0.3f w[0] = %0.3f"%(dCf(w,x,y)[0,1], dCf(w,x,y)[0,1])
```

Esto nos devuelve -> `cuesta w[1]=-38.744 w[0]=-38.744

#### Proceso iterativo de ajuste

Finalmente, con la ayuda de un bucle `for`realizamos un ajuste iterativo de los parámetros usando un factor de aprendizaje de `a = 0.01`. Cada 25 iteraciones graficamos los resultados y se muestran los valores actuales de los parámetros y el error.

```
a = 0.01
# w = np.matrix([5.0, 1.2])
for i in range(101):
	if i%25==0:
		#plotting
		plots()
		print("W   =", w)
		print("Cf(w)   =", Cf(w,x,y))
		print("dCf(w)   =", dCf(w,x,y))
		iw = -dCf(w, x, y)
		w = w+a*iw
```

Esto irá iterando poco a poco, veamos los resultados:

##### **Primera iteración**

![[Pasted image 20241013185000.png]]

**Valores**
``` python
w    = [[5.  1.2]]
Cf(w) = 52.23360000000001
dCf(w) = [[-17.12  -38.744]]
```

##### **Segunda iteración**

![[Pasted image 20241013185107.png]]

**Valores**

``` python
w    = [[5.1712  1.58744]]
Cf(w) = 44.94412668038401
dCf(w) = [[-9.351344  12.8121072]]
```

##### **Tercera iteración**

![[Pasted image 20241013185156.png]]

**Valores**

``` python
w    = [[5.26471344 1.45931893]]
Cf(w) = 43.27497050162042
dCf(w) = [[-11.01957001  -1.62457895]]
```

##### **Cuarta iteración**

![[Pasted image 20241013185254.png]]

**Valores**

``` python
w    = [[5.37490914 1.47556472]]
Cf(w) = 42.11839323992736
dCf(w) = [[-10.07571907   2.32972332]]
```

##### **Quinta y última iteración**

![[Pasted image 20241013185336.png]]

**Valores**
``` python
w    = [[5.47566633 1.45226748]]
Cf(w) = 41.07255358041667
dCf(w) = [[-9.87654779  1.16189134]]
```
