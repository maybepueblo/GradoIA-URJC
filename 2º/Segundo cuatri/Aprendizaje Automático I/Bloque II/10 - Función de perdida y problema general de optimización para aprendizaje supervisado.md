Este algoritmo del descenso de gradiente nos permite resolver cualquier problema de optimización de aprendizaje supervisado siempre que dispongamos de una función$~\mathcal L({\bf w})~$ denominada **función de perdida**.
## Problema de optimización de aprendizaje supervisado
Tenemos a nuestra disposición:
- Un conjunto de datos $\rm X$ en forma de tabla $N$ x $D$
- Un conjunto $\rm Y$ de valores objetivos o etiquetas, que puede ser:
	- Para regresión: un vector columna de ***N*** elementos en el primer caso.
	- Para clasificación: un vector columna o una matriz si se usa una representación *one-hot*. A este conjunto se le denomina *ground truth*.
Se supone que tenemos un modelo. El objetivo es encontrar los parámetros óptimos, toca preguntarse por qué unos parámetros son mejor que otros.
## Función de perdida
Esto nos da una medida relacionada con los fallos cometidos por el modelo respecto al *ground truth*. Sea $~\mathcal L(\rm Y, f(X;w))$ dicha función.
### Expresión general para aprendizaje supervisado
Cuanto menos fallos mejor el modelo evidentemente. Por tanto se formula matemáticamente como el siguiente problema de optimización:$$
{\bf w}^* =
\mathop{\arg\min}\limits_{{\bf w}}
 ~\mathcal L \big( {\bf Y}, f({\bf X};{\bf w}) \big)
$$
En definitiva, para realizar una tarea supervisada necesitamos:
- un **conjunto de datos etiquetado**: nos lo dará el cliente
- un **modelo** y una **función de perdida**: decisión nuestra como gente que "sabe" de IA. 

Solo sabemos modelos lineales por ahora, es decir $f(\rm x;w)=w^{\top}x$ asumiendo la existencia de característica dummy. 

Tenemos que saber si es de regresión o de clasificación para aplicar la función de perdida primero.
#### Para regresión
Aquí hacemos $~f({\bf x};{\bf w}): (\mathbb R^{D}; \mathbb R^{D}) \rightarrow \mathbb R,~$y el valor objetivo $y \in ~\mathbb R$ también.

Por ende, una función de perdida para regresión ha de tener las siguientes características:
- Calcular $\delta_{(i)} = \left(y^{(i)} - f({\bf x}^{(i)},{\bf w}) \right)$ para cada $i = 1,2,\ldots,N.$
- Convertir $\delta_{(i)}$ en un valor positivo para todo $i$.
- Hacer el promedio para todos los ejemplos.
Algunas que cumplen esto son:
![[Funciones de perdida regresión.png]]
#### Para clasificación
A diferencia de la regresión, podemos encontrar varias formas:
1. Clasificación binaria -> Ejemplo pertenece a 2 clases excluyentes
2. Clasificación multiclase -> Pertenecer a varias clases pero excluyentes
3. Clasificación multietiqueta -> Pertenecer a una o varias clases al mismo tiempo
Los tres casos se pueden abordar como de regresión y después usar una función discriminante.

PERO ya hemos aprendido que la regresión logística es un modo mucho más natural de abordar la clasificación porque incorpora una medida de la probabilidad de pertenecer a una cierta clase. 

Sin embargo, cuando trabajamos con probabilidades las pérdidas NO son apropiadas

Esto es importante y se verá más adelante.
