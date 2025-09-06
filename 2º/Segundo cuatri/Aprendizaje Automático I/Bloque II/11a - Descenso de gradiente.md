## ¿Qué es un gradiente?
Vector que marca la dirección de máxima pendiente de una función en un punto dado.

Sea $~\mathcal L(\rm w): ~\mathbb R^D \rightarrow ~\mathbb R$ , entonces el gradiente de $~\mathcal L$ respecto de $\rm w$ es el vector: $$
\nabla_w \mathcal L = \left[
  \frac{\partial \mathcal L}{\partial w_1},~
  \frac{\partial \mathcal L}{\partial w_2},~
  \cdots,~
  \frac{\partial \mathcal L}{\partial w_D}
\right]
$$
Significa lo siguiente:
- Decimos que $~\mathcal L(\rm w)$ es en general una superficie en un espacio D dimensional.
- Según viajamos por los reales en esa dimensionalidad obtenemos valores de esta superficie dicha.
- El gradiente en un punto concreto $\rm w$ nos indica la dirección a moverse para lograr subir más rápido que en ninguna otra dirección.
## ¿Qué requisitos debe haber para tener un gradiente?
La función $~\mathcal L$ ha de ser derivable en todas las direcciones.
## ¿Subir o bajar?
En casos nos interesa saber dónde esta el mínimo del gradiente, a lo que llegaremos dando la vuelta a la función y quedando:$$
\mathop{\arg\min}\limits_{\bf w}  \big( \mathcal L({\bf w}) \big) =
\mathop{\arg\max}\limits_{\bf w}  \big( - \mathcal L({\bf w}) \big)
$$
## Algoritmo *Descenso de gradiente*
Esto es un algoritmo para localizar el mínimo de una función de forma iterativa. En cada iteración nos desplazamos por $\rm w$ en la dirección que marca el gradiente de $~\mathcal L$. Este algoritmo comienza en un punto aleatorio y el desplazamiento produce un nuevo punto. Esto se repite, tomando como punto de partida el punto alcanzado en la iteración anterior, hasta llegar a una parada.

**Regla de actualización**
El punto siguiente se calcula **descendiendo** por el gradiente, por tanto:$$
{\bf w}^\text{nuevo} = {\bf w}^\text{actual} - \eta\cdot\nabla_{\bf w}{\mathcal L({\bf w}^\text{actual})}
$$
**Ratio de aprendizaje**
En vez de usar el valor del gradiente evaluado en el punto se utiliza sólo el $\eta \%$ . Normalmente empezamos probando con $\eta = 0.1$.

**Condición de parada**
Se detiene el algoritmo si ocurre alguno de los dos casos siguientes:
- Alcanzamos un tope de iteraciones
- El valor de $~\mathcal L$ ya no decrece más

