## Votación de la mayoría
Método más simple de combinación de clasificadores.
- **Mecanismo:** Entrenamos $K$ clasificadores, y la clase final predicha es la que recibe el **mayor número de votos** (la clase más repetida) de los $K$ clasificadores individuales.
- **Funcionamiento:** Este método funciona de manera efectiva si los errores de los clasificadores individuales son **estadísticamente independientes**. Si los clasificadores se equivocan en ejemplos diferentes y no dependen entre sí, la probabilidad de que la mayoría del conjunto se equivoque es mucho menor que la probabilidad de error de un solo clasificador.
## Bagging y Random Forest
Técnica diseñada fundamentalmente para **reducir la varianza** de los estimadores que son inestables (aquellos cuya predicción cambia mucho si se cambia ligeramente el conjunto de datos de entrenamiento)

**Conceptos clave**
- **Mecanismo de entrenamiento:** Cada clasificador individual (o estimador base) se entrena usando una **muestra aleatoria con reemplazamiento** (bootstrap) de los $N$ datos de entrenamiento originales.
- **Objetivo:** El clasificador resultante del Bagging **incrementa la estabilidad** y **reduce la varianza**. 
- **Tipos de modelo base:** Funciona mejorando las técnicas de **varianza alta** (como los [[Árboles de Decisión]] o las Redes de Neuronas), pero no suele mejorar las técnicas de varianza baja (como un clasificador lineal)

**Árboles de Decisión como Modelos Base*
Son estimadores ideales para Bagging porque:
- **Desventajas del árbol individual:** Tienden a tener un **sesgo bajo** (se ajustan muy bien a los datos de entrenamiento) y una **varianza alta** (tienden al sobreaprendizaje o *overfitting*), ya que siempre pueden construir un árbol con un acierto del 100% en el conjunto de entrenamiento.
- **Estrategia con Bagging:** Se mitiga esta alta varianza. Por lo tanto, con Bagging es preferible usar árboles de decisión **profundos** (por ejemplo, de 16 nodos hoja, que tienen alta varianza) en lugar de árboles simples
### Random Forest (RF)
Aplicación más conocida de Bagging, combinando $M$ árboles de decisión binarios mediante votación de la mayoría.
- **Aleatoriedad en Random Forest**: Además de usar Bagging, RF introduce aleatoriedad adicional en el entrenamiento de cada árbol para asegurar su independencia estadística.
	1. Muestreo aleatorio de subconjuntos de **características**
	2. Selección aleatoria de **umbrales** de corte (en técnicas como *Extremely Randomized Trees*)
- **Sesgo y varianza:** RF reduce la varianza, pero no reduce el sesgo del modelo base. Por ello, es crucial usar árboles con un número adecuado de niveles ($L$) para controlar el sesgo del modelo base.
- **Paralelización:** Tanto el entrenamiento como la ejecución de los árboles en Random Forest se pueden **paralelizar**. 
## Boosting Biclase (Adaboost)
Método aditivo donde se construye un clasificador fuerte combinando una secuencia de clasificadores básicos o **débiles** (que son solo un poco mejores que el azar). A diferencia del Bagging, el Boosting **reduce principalmente el sesgo**.

**AdaBoost (Adaptive Boosting) - Clasificación Biclase**
Fue uno de los primeros algoritmos de Boosting y se aplica a problemas de clasificación biclase.
- **Mecanismo iterativo** Entrena secuencialmente $M$ clasificadores débiles $G_m(x)$
	1. **Importancia del clasificador ($\alpha_m$)**: El algoritmo asigna un peso o importancia ($\alpha_m$) a cada clasificador $G_m$  basado en su error ($err_m$). Cuanto más pequeño el error, más grande es $\alpha_m$, modelando así lo "bueno" que es el clasificador
	2. **Actualización de Pesos de Datos**: En cada iteración, AdaBoost **incrementa el peso de los ejemplos que fueron mal clasificados** por el clasificador anterior, y mantiene sin cambios el peso de los ejemplos bien clasificados. Esto obliga al siguiente clasificador débil a **centrarse en los datos más difíciles** de clasificar.
- **Modelos base:** Funciona bien si los clasificadores básicos tienen **sesgo alto y baja varianza** (es decir, son **modelos simples** o "no muy complejos"). Por lo tanto, con Boosting es mejor usar árboles de decisión **simples** (por ejemplo, con 2 nodos hoja)
- **Función de pérdida**: AdaBoost se interpreta como un algoritmo de modelado aditivo que minimiza la **función de pérdida exponencial** ($L_{exp}(y, f(x))=e^{-y·f(x)}$). Esta función es sensible a los errores.
## Boosting Multiclase (SAMME)
SAMME (*Stagewise Additive Modeling using Multi-class Exponential loss function*) es la adaptación de AdaBoost para problemas de clasificación con $K$ clases
- **Función de pérdida**: Usa la **pérdida exponencial multiclase**
## Gradient Boosting
Enfoque más general de modelado aditivo que se puede aplicar a cualquier función de pérdida diferenciable.
- **Mecanismo:** Ajusta un modelo aditivo de forma iterativa, usando el concepto de **Descenso de Gradiente** en el espacio de funciones.
	1. En cada paso, hallamos el **gradiente negativo** ($g_m$) de la función de pérdida $L$ con respecto a la predicción actual.
	2. El estimador básico que se entrena en esa iteración debe intentar **estimar este gradiente negativo** (pseudo-residual)
	3. La función se actualiza en la dirección opuesta al gradiente.
- **Clasificación:** Si se usa la entropía cruzada (*cross-entropy*, véase [[Tema 2 - Optimización y regularización de la pérdida esperada]]), se aprenden $K$ árboles (uno por cada clase)
- **Regularización**: Gradient Boosting usa métodos de regularización intrínsecos al algoritmo para mejorar la generalización.
	- **Tasa de aprendizaje (*Learning Rate* o *Shrinkage*):** Se aplica un factor $s$ (donde $0 < s \leq$ 1 ) que se multiplica por el parámetro de cada estimador débil entrenado.
	- **Tasa de muestreo (*Sampling Rate*):** Usamos un factor $r$ (donde $0 < r \leq 1$) que define la proporcion de datos de entrenamiento seleccionados mediante muestreo **sin reemplazamiento** para entrenar cada estimador débil.