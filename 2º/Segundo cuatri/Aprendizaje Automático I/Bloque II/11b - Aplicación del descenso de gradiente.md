## Descenso del gradiente con pérdidas de regresión
Necesitamos las siguientes dos expresiones:
$$\rm Problema \space de \space optimización : w^* = arg min ~\mathcal L(Y, f(X;w))$$
$$\rm Regla \space de \space actualización : w^{nuevo} = w^{actual}-\eta·\nabla_w ~\mathcal L(w^{actual})$$
El primer paso es calcular el gradiente de la pérdida $\rm \nabla_w ~\mathcal L$. Luego hemos de usar ese cálculo en la regla de actualización.
## Gradiente de la pérdida MSE
$$
\begin{align}
  \nabla_{\bf w}\mathcal L &=
  \left[ \frac{\partial \mathcal L}{\partial w_i}
  \right]_{i=1,\ldots,D}
\end{align}
$$
Para calcular la derivada parcial de la pérdida respecto del parámetro $i$-ésimo, vamos a reescribir la pérdida del siguiente modo:
$$
\mathcal L =
\frac{1}{N}\sum\limits_{k=1}^N \delta_{(k)}^2,
$$
con
$$\delta_{(k)} = y^{(k)} - f({\bf x}^{(k)},{\bf w}),$$
y con
$$
f({\bf x}^{(k)},{\bf w}) = x_1^{(k)}w_1 + x_2^{(k)}w_2 + \cdots + x_D^{(k)}w_D.
$$
Así podemos aplicar la regla de la cadena de la derivada de modo que para el ejemplo $k$-ésimo tenemos:
$$
\frac{\partial \mathcal L}{\partial w_i} =
\frac{\partial \mathcal L}{\partial \delta_{(k)}}\cdot
\frac{\partial \delta_{(k)}}{\partial f}\cdot
\frac{\partial \mathcal f}{\partial w_i}
$$
Juntando todo y recordando que tenemos el sumatorio de $N$ términos $\delta^2$:
$$
\frac{\partial \mathcal L}{\partial w_i} =
\frac{1}{N}\sum\limits_{k=1}^{N}
 2\delta_{(k)}(-1)x_i^{(k)} =
\frac{2}{N}\sum\limits_{k=1}^{N}
 \left( f({\bf x}^{(k)},{\bf w}) - y^{(k)} \right)\left( x_i^{(k)} \right),
$$
que para el caso de modelos lineales es
$$
\frac{\partial \mathcal L}{\partial w_i} =
\frac{2}{N}\sum\limits_{k=1}^{N}
 \left( {\bf w}^\top{\bf x}^{(k)} - y^{(k)} \right)\left( x_i^{(k)} \right)
$$
## Regla de actualización de parámetros
Una vez se conoce la expresión del gradiente para todo punto, sólo hay que utilizarla en la regla de actualización del descenso de gradiente. 