Empezamos ahora a enfocarnos en el **Aprendizaje supervisado**, noción que vimos en [[0 - Introducción a ML I]]. Existen aquí dos grandes problemas:
- Regresión
- Clasificación
Son lo mismo en verdad, una regresión es una clasificación con infinitas clases.
## Regresión
Decimos que es emparejar los ejemplos con un **valor objetivo** (target) que toma valores en un intervalo continuo.
## Clasificación
Emparejar los ejemplos con un número discreto conocido como **etiqueta, clase** (label). A veces la clase toma valores dentro de un conjunto de categorías, por ejemplo {rojo, verde, azul}. Aquí o hacemos codificaciones con enteros como vimos anteriormente en la asignatura, o la codificación *One-Hot* (véase [[1 - Tipos de datos]])

Si hay solo dos clases el problema es **binario** o de clasificación binaria. Si hubiese varias el problema es **multi-clase**.
## En ambos casos
En problemas supervisados siempre tendremos:
- Un conjunto de datos consistente en:
	- N ejemplos D dimensionales (siendo cada ejemplo emparejado con su valor objetivo)
	- Un modelo para aprender a emparejar cada ejemplo con su valor objetivo (regresión) o su etiqueta (clasificación). 
Nuestro objetivo es estimar con la mayor tasa de acierto posible el valor objetivo o la etiqueta de los ejemplos **nuevos** que lleguen a partir del momento en el que pongamos nuestro sistema a funcionar. 

>[!Ojo]
>He dicho sistema y NO modelo
>El modelo es una parte de un sistema más grande del que hablaremos en otro momento.
## Modelo general para aprendizaje supervisado
Nuestro modelo es la siguiente función paramétrica ${\rm f(x;w)}$ donde decimos que:
- recibe un ejemplo $x \in \Re^D$ 
- produce una salida, que puede ser un vector ${\rm y}$ o un escalar $y$, dependiendo del problema
- el vector ${\rm w}$ es el conjunto de parámetros que nosotros podemos modificar para transformar la entrada ${\rm x}$ en la salida ${\rm y}$
Si en vez de un único ejemplo le metemos un conjunto de ejemplos ${\rm X \in \Re^{DxN}}$ entonces el modelo nos produce un conjunto o lote de salidas ${\rm Y}$. 
## Modelo lineal
Aquel en el que la salida del modelo es una combinación lineal de la entrada y los parámetros. Es decir:$$f(w; x) = w_0+w_1 x_1+···+w_Dx_D$$
La relación entre uno lineal y un hiperplano es clara. Dado un modelo lineal, existe un hiperplano cuyo vector característico es ${\rm w = (w_1,···,w_D)^{\top}}$ y término independiente $w_0$ tal que $w_0+w^{\top}x = 0$
### Linealidad y regresión
$$\hat{y}=w_0+\rm w^{\top}x$$
Siendo aquí $\hat{y}$ la estimación que hace el modelo para el ejemplo $\rm x$ dados los parámetros elegidos. El modelo es lo que hay que ajustar por **mínimos cuadrados** un conjunto de pares de puntos pero generalizado a $D \geq 2$ dimensiones.
#### Aprendizaje
Esto es encontrar los parámetros óptimos (o los mejores posibles), que son aquellos con los que logramos mantener la menor discrepancia entre la estimación del valor objetivo verdadero. Una forma es con un cálculo matricial.

Veamos una imagen donde se ilustra bien todo:

![[Cálculo matricial modelo lineal regresión.png]]
Lo malo es que este método es costoso computacionalmente cuando $\rm X$ es muy grande ya que exige invertir la matriz. Hay formas de hacerlo más eficiente pero lo más adoptado hoy en día es usar el **descenso de gradiente**, explicado más adelante.
### Linealidad y clasificación binaria
$$\hat{y}=Signo(w_0+\rm w^{\top}x)$$
Esto asume que tenemos dos clases etiquetadas como $\{+,-\}$.

De nuevo, $\hat{y}$ representa la estimación del modelo. Pero cuando se trata de clasificación binaria aparecen dos términos importantes nuevos:
- superficie de decisión
- función discriminante
#### Superficie de decisión
Los puntos de $\Re^D$  que satisfacen la igualdad $w_0+\rm w^{\top}x=0$ están exactamente sobre el hiperplano; no tienen ni signo positivo ni negativo. Por ende, se sitúan exactamente sobre la frontera entre las dos clases y se denomina **superficie de decisión**

Esta será un hiperplano sólo si $f(x; w)$ es lineal.
#### Función discriminante
El modelo lineal de clasificación binaria usamos Signo para producir la estimación de la etiqueta, es decir, discriminar a qué clase pertenece el ejemplo dado. Usar esta función sin embargo, NO es obligatorio.

En general usamos una función discriminante que transforme el resultado de $f(x; w)$ (ya sea lineal o no) en la etiqueta estimada.
$$
\hat y = \left\lbrace
 \begin{array}{lll}
  0 & \text{si} & f({\bf x};{\bf w}) > \theta \\
  1 & \text{si} & f({\bf x};{\bf w}) \le \theta
 \end{array}
\right.
$$
- La etiqueta puede ser {0, 1}.
- La función discriminante consiste en superar el umbral $\theta$.
#### Aprendizaje
Usamos la misma fórmula que teníamos en la regresión. Teniendo una superficie de decisión con los parámetros óptimos para luego aplicar una función discriminante.