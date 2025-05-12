Ya vimos cómo se veía la función de perdida en [[10 - Función de perdida y problema general de optimización para aprendizaje supervisado]]. En esta se evalúa la discrepancia entre los valores del *ground truth* y los estimados por el modelo.

Anteriormente aprendimos a encontrar $\rm w^*$ mediante descenso de gradiente respecto de la pérdida. En otras palabras, la única regla que imponemos para aprender el modelo es que los parámetros elegidos minimicen la función de pérdida. 

Esto de regularizar consiste en añadir más reglas. Puestoo que tanto $\rm X$ como $\rm Y$ vienen dados por el cliente, lo único sobre lo que podemos imponer reglas es sobre los pesos. Así convertimos la función objetivo en esto:$$
\mathcal L \big( {\bf Y}, f({\bf X};{\bf w}) \big) +
\mathcal R \big( {\bf w} \big)
$$
Veremos tres métodos:
- Lasso
- Ridge
- Elastic Net
## Lasso
Consiste en añadir el término
$$
\mathcal R_{L} = \alpha \sum\limits_{i=1}^{D} \vert w_i\vert
$$
a la función de pérdida; donde $\alpha\ge 0$ es un valor que elegimos nosotros para contralar su efecto.
- $\alpha \rightarrow 0:\quad$
  Obtenemos el mismo $\bf w^*$ que con la regresión lineal, es decir desaparece el término de regularización.
- $\alpha > 0:\quad$
  Algunos parámetros tenderán a ir hacia 0
- $\alpha \rightarrow \infty:~~$
  Todos los parámetros se anulan.

En definitiva, quitando los dos casos extremos, el efecto de este regularizador es lograr que haya menos parámetros, porque muchos de ellos tenderán hacia 0.

Comentarios:
- Dado que la norma-1 de un vector $\bf w$ es
$$\Vert {\bf w} \Vert_1 = \sum\limits_{i=1}^{D} \vert w_i\vert$$ a esta regularización también se le llama **Regularización L1**
- El nombre proviene de _Least Absolute Shrinkage and Selection Operator_, precisamente por la propiedad de seleccionar y reducir el número de parámetros.
- La clase `sklearn.linear_model.Lasso` implementa la pérdida con esta regularización para el modelo lineal.
<BR> También se puede usar en otros modelos que ofrecen la opción `penalty = "l1"`.
## Ridge
Consiste en añadir el término
$$
\mathcal R_{R} = \frac{\alpha}{2} \sum\limits_{i=1}^{D} ( w_i )^2
$$
a la función de pérdida; donde $\alpha\ge 0$ es un valor que elegimos nosotros para contralar su efecto.
- $\alpha \rightarrow 0:\quad$
  Obtenemos el mismo $\bf w^*$ que con la regresión lineal, es decir desaparece el término de regularización, igual que con _Lasso_,
- $\alpha > 0:\quad$
  Impide que los parámetros se separen mucho o que alguno crezca demasiado.<br>
- $\alpha \rightarrow \infty:~~$
  Todos los parámetros se anulan, igual que con _Lasso_.

En definitiva, quitando los dos casos extremos, el efecto de este regularizador es lograr que todos los parámtros tengan valores pequeños, pero no necesariamente nulos.

Comentarios:
- Dado que la norma-2 al cuadrado de un vector $\bf w$ es
$$\Vert {\bf w} \Vert_2 = \frac{1}{2}\sum\limits_{i=1}^{D} ( w_i )^2$$ a esta regularización también se le llama **Regularización L2**
- El factor $1/2$ se añade para que al derivar el término el exponente se cancele con él.
- La clase `sklearn.linear_model.Ridge` implementa la pérdida con esta regularización para el modelo lineal.
<BR> También se puede usar en otros modelos que ofrecen la opción `penalty = "l2"`.
## Elastic Net
Consiste en añadir una combinación lineal de ambos
$$
\mathcal R_{E} = \alpha_1 \mathcal R_{L} + \alpha_2 \mathcal R_{R}
= \alpha_1 \Vert{\bf w}\Vert_1 + \frac{\alpha_2}{2} \Vert{\bf w}\Vert_2^2.
$$
Esta regularización causa un doble reducción de los parámetros: la que provoca Lasso y la de Ridge. Para tener más control y además una interpretación de $\alpha_1$ y $\alpha_2$ es más frecuente utilizar una combinación lineal convexa de ambos términos de regularización. Es decir:
$$
\mathcal R_{E} = \alpha \big( r \cdot \mathcal R_{L} + (1-r)  \cdot \mathcal R_{R} \big),
$$
donde $r$ es el porcentaje o ratio de regularización Lasso que aplicamos; y por tanto el porcentaje complementario hasta llegar a 100% es de regularización Ridge; y $\alpha$ es un multiplicador para dar más o menos peso al termino.

Comentarios:
- La clase `sklearn.linear_model.ElasticNet` implementa la pérdida con esta regularización para el modelo lineal.
<BR> También se puede usar en otros modelos que ofrecen la opción `penalty = "elasticnet"`.
# Hiperparámetros

Con los términos de regularización aparece un término nuevo muy-muy importante: **hiperparámetro**.

Los parámetros son aquellos elementos que podemos utilizar para ajustar un modelo a un conjunto de datos supervisado, <br>
mientras que los **hiperparámetros** son aquellos elementos que se han añadido al modelo o al algoritmo para controlar la ejecución.

<u>Ejemplos</u>
- En la regla de actualización de parámetros mediante descenso del gradiente aparecía el _learning rate_ $\eta$, que controlaba la velocidad a la que viajamos por el espacio de parámetros.
- En los términos de regularización aparece $\alpha$ para dar más o menos peso al regularizador
- En la regularización Elastic Net aparece $r$ para dar más o menos porcentaje a Lasso.