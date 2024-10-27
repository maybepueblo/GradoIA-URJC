Este notebook se va a centrar en explicar el descenso de gradientes como un método iterativo para encontrar el mínimo de una función. Lo utilizamos principalmente en problemas de optimización y en aprendizaje automático.

#### Funciones auxiliares

``` python
import numpy as np
import matplotlib.pyplot as plt

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
```

#### Datos

``` python
Dx = [0.96, 1, 1.04]
Dy = [ 2, 3 , 4]

plt.plot(Dx,Dy,"*", color="blue")
plt.show()
```

Este es el resultado:

![[Pasted image 20241013195811.png]]

#### Función lineal

Nuevamente preparamos la función lineal para su uso:

``` python
w=[8, 1.5]
def f(w,x):
	w1=w[1]
	w0=w[0]
	#y=w1*x+w0
	m=w1
	b=w0
	y= m*x+b
	return y

def pf(x):
	y=w[1]*x+w[0]
	return y

# Visualizamos
plot_f(pf, -7, 7)
plt.plot(Dx, Dy, "*", color="blue")
plt.show()
```

Esta sería la salida del programa:

![[Test.png]]
#### Función de coste/error/pérdida/residuo

``` python
def Cf(w, Dx, Dy):
	c = 0 
	for i in range(len(Dx)):
		d = (Dy[i]-f(w, Dx[i]))**2
		c+=d
	return c
L=(7-f(w,-2))**2 + (9-f(w,4.5))**2+ (18-f(w,6.2))**2
print("Near/Cost/Loss/Error=",L)
print("Near/Cost/Loss/Error=",Cf(w,Dx,Dy))
```

Si lo tratamos genéricamente, tenemos que:
$$Cf(w, Dx, Dy)=-2\sum_i(Dy[i]-f(w, Dx[i]))²$$
La pendiente para nuestra función de coste en cada punto w es, usando la regla de la cadena, lo siguiente:
$$dCf(w, Dx, Dy)=-2\sum_i(Dy[i]-f(w,Dx[i])df(w,Dx[i])$$
#### Regla de la cadena

Para poder entender la deducción anterior, reduzcamos el caso a otros más simples para así poder explicar cómo hemos llegado a nuestra conclusión.

Usaremos este ejemplo:
$$Cf(w)=g(r(w))$$
Donde tenemos que:
$$g(w)=w²$$
Y también que:
$$r(w)=(5-f(w))$$
>[!CAUTION] 
>En este caso el 5 que vemos arriba es un número random elegido al azar para este ejemplo

Ahora tenemos lo siguiente:
$$Cf(w)=(5-f(w))²$$
La regla de la cadena dice que la función derivada de Cf que nos da la pendiente en todos los puntos de Cf, que llamaremos dCf es:
$$dCf(w)=dg(r(w))dr(w)$$
Aunque en nuestro caso, Cf es una función anidada, su derivada es el producto de funciones derivadas, esto nos simplifica un poco la vida.

Así, la derivada de g (el cuadrado) es:
$$dg(w)=2w$$
Y la de r es:
$$dr(w)=-df(w)$$
Como el parámetro que pasamos a g es r tenemos lo siguiente:
$$dCf(w)=dg(r(w))dr(w)=2(r(w))dr(w)=2(5-f(w))(-df(w))$$
Limpiemos un poco:
$$dCf(w)=-2(5-f(w))df(w)$$
#### Descenso de gradientes

Es lo que conocemos como el algoritmo de optimización utilizado para ajustar los parámetros `w` del modelo, minimizando la función de costo. La actualización de los parámetros sigue la regla:
$$w=w-\alpha·dCf(w)$$
Donde alpha es la tasa de aprendizaje. Veamos cómo implementarlo, pero primero definamos la función de coste en base a un único parámetro para visualizar gráficas.

``` python
def dCf(w,Dx,Dy):
	c=0
	for i in range(len(Dx)):
		d=(Dy[i]-f(w,Dx[i]))*dfw(w,Dx[i])
		c+=d
	return -2*c

def Cfw(w):
	return Cf(w, Dx, Dy)

def dCfw(w):
	return dCf(w, Dx, Dy)

plot_f(Cfw, -1, 5.5)
plot_df(Cfw, dCfw, w)
plt.show()
```

Y esta sería la gráfica:

![[Pasted image 20241013203815.png]]

Ahora, veamos el descenso de gradiente:

``` python
#Descenso de Gradiente
alpha=0.01
cuesta=dCfw(w)
w=w-alpha*cuesta

#Visualizamos
coste=Cfw(w)
print("w=%0.5f cuesta=%0.5f error/coste=%0.5f"%(w,cuesta,coste))

plot_f(Cfw,-1,5.5)
plot_df(Cfw,dCfw,w)
plt.show()
plot_f(pf,-4,8)
plt.plot(Dx,Dy,"*",color="blue")
plt.show()
```

Y iterando nuestro descenso de gradiente para minimizar la función, este es nuestro resultado:

![[Pasted image 20241013203946.png]]

![[Pasted image 20241013203955.png]]

#### Uso de matrices

Haciendo más eficiente el cálculo, podemos implementar el uso de matrices.

Iniciemos los datos apropiadamente:

``` python
x = np.matrix([[1.0, 1.0, 1.0], [-2.0, 4.5, 6.2]])
y = np.matrix([7.0, 9.0, 18.0])
w = np.matrix([5.0, 1.2])
```

Las cosas son muy parecidas:

``` python
def f(w, x):
	y = w*x
	return y

def df(w, x):
	return x
```

La función de coste se simplifica:
$$Cf(w, x, y)=(y-f(w,x))(y-f(w,x))^T$$
``` python
def Cf(w, x, y):
	r=y-f(w, x)
	l=r*r.T
	return l[0,0]
```

La derivada también se complica menos:
$$dCf(w, x, y)=-2(y-f(w, x))x^T=-2r(w, x, y)x^T$$
``` python
def dCf(w, x, y):
	r = y-f(w, x)
	dCfw=-2*r*x.T
	return dCfw
```

El descenso de gradiente en cambio, queda prácticamente igual:

``` python
a=0.01
#w=np.matrix([5.0,1.2])
for i in range(101):
	if i%25==0:
	#plotting
	plots()
	print("w =",w)
	print("Cf(w) =",Cf(w,x,y))
	print("dCf(w)=",dCf(w,x,y))
	iw=-dCf(w,x,y)
	w=w+a*iw
```

