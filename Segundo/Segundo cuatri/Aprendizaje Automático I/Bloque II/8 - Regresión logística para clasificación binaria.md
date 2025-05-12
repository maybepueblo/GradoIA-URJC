## Motivación
Hemos aprendido que tanto clasificación como regresión se pueden resolver usando la solución matricial de un problema de regresión. Podemos decir que la clasificación es un problema de regresión donde el *target* es categórico/discreto en vez de continuo. O dicho de otra forma, un problema de regresión es un problema de clasificación con infinitas etiquetas.

No parece muy lógico usar la solución de regresión para un número finito de etiquetas, así que podemos usar otra forma, que nos devuelve una medida de probabilidad, lo que da significado a la predicción.
## Mates necesaria
### Sigmoide
Funciones cuya gráfica parece una S. Cumple lo siguiente:
- $S: \Re \rightarrow (a, b)$ con $a < b$, o sea, real y acotada.
- Diferenciable con derivada no negativa en cada punto y sólo 1 punto de inflexión, siempre creciente y en forma de S. 
### Logística
Es una Sigmoide particular:$$S(x)=\frac{1}{1+e^{-x}}$$
donde $x$ hace referencia a la entrada de la función, no a un ejemplo del conjunto de datos.

Esto tiene las siguientes propiedades:
- Continua y siempre creciente
- $\lim_{x\rightarrow -\infty}S(x)=0$ 
- $\lim_{x\rightarrow +\infty}S(x)=1$
Por tanto **cumple las condiciones para ser una distribución de probabilidad**
## Regresión logística
Ahora lo que buscamos es **saturar** el valor de la función vista $f(w, x)$ de modo que por encima de esta saturación valga siempre lo mismo.

La sigmoide se encarga de la parte de saturar, convirtiéndolo a una medida de la probabilidad de que el ejemplo pertenezca a una de las dos clases. Sea **Logit** el nombre que recibe el resultado de la función lineal $f(w, x)=\rm w^{\top}x$ 

Entonces, la función logística aplicada al logit nos devuelve una medida de la probabilidad de que $\rm x$ pertenezca a la clase "+1", más exactamente.
$$Pr(y=+1|logit=\rm w^{\top}x) = \frac{1}{1+e^{-w^{\top}x}}$$
### Aprendizaje
No hay que explicar nada nuevo ya que los parámetros son los de un modelo lineal. Simplemente hemos de transformar el resultado mediante la función logística.
## Cosas importantes
### ¿La regresión logística es un modelo lineal?
Es un modelo lineal generalizado ya que los logits se calculan con un modelo lineal. La función logística simplemente nos sirve para dar una estimación de la probabilidad de pertenecer a una clase pero el modelo de los datos sigue siendo un modelo lineal. 
### La regresión logística **también** tiene una función discriminante
Tiene una umbralización tal que:
$$
\hat y = \left\lbrace
\begin{array}{llll}
+1 & \text{si} & \hat p > \theta \\
-1 & \text{si} & \hat p \le \theta
\end{array}
\right.
\quad\text{donde}\quad
\hat p = \frac{1}{1+e^{-{\bf w}^\top{\bf x}}}
$$
con $\theta = 0.5$.

Según el dominio de la app, nos puede interesar ser más restrictivos o más laxos a la hora de fijar el umbral.
