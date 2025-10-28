>[!NOTE] 
>Se usará $\textbf{w}$ o $\phi$ indistintamente para denominar los parámetros del modelo
## Planteamiento del problema
**Modelos y parámetros**
Un modelo de aprendizaje supervisado es una función $y=f(x;w)$. El modelo es una ecuación matemática que incluye parámetros que afectan al resultado.

Consideramos lineal al modelo en los parámetros si estos aparecen multiplicando a las entradas y sumándose (ej: $f(x, w)=w_0+w_1x_1+w_2x_2$). Un modelo como $f(x_1)=w_0·x_1·x_1$ **no es lineal**.

**Función de pérdida y función de coste**
- **Pérdida** ($L$): Mide cuán malo es el modelo para un único dato.
	- *Ejemplo*: $L(y_i,\hat{y}_i)=(y_i-\hat{y}_i)²$  -> Error cuadrático
- **Coste empírico** ($J$): Es la pérdida media o riesgo empírico sobre el conjunto de entrenamiento $D=\{x_i,y_i\}_{i=1}^N$. Se escribe de la siguiente forma: $$J(w)=\frac{1}{N}\sum_{i=1}^NL(f(x_1,w),y_i)$$
- Objetivo -> El entrenamiento de un modelo busca encontrar los parámetros $\hat{w}$ que minimizan la función de coste $J(w)$.
## Funciones de pérdida

**Derivación por Máxima Verosimilitud**
La función de pérdida la podemos construir asumiendo una distribución de probabilidad $Pr(y|\theta)$ y usando el modelo $f[x,Φ]$ para predecir sus parámetros $\theta$. 

La optimización generalmente consiste en minimizar el logaritmo negativo de la verosimilitud.

| Problema                 | Distribución Asumida | Función de Activación de Salida                   | Pérdida Resultante                                   |
| ------------------------ | -------------------- | ------------------------------------------------- | ---------------------------------------------------- |
| Regresión Univariante    | Normal (Gaussiana)   | Ninguna (salida continua)                         | **Error Cuadrático Medio (MSE)** - Mínimos cuadrados |
| Clasificación Binaria    | Bernoulli            | **Sigmoide** (para obtener p $\in$)               | **Entropía Cruzada Binaria (BCE)**                   |
| Clasificación Multiclase | Categórica           | Softmax (para obtener probabilidades que sumen 1) | **Entropía Cruzada Multiclase**                      |

**Funciones de pérdida para regresión** (valores continuos)
1. **Error Cuadrático Medio (MSE) / $L_2$ Loss**: $L(y,\hat{y})=(y-\hat{y})²$. Es la más sensible a **outliers (desvíos significativos del patrón general y del resto de datos)** 
2. **Error Absoluto Medio (MAE) / $L_1$ Loss**: $L(y,\hat{y})=|y-\hat{y}|$. Penaliza fundamentalmente los errores pequeños (comparado con MSE)
3. **Huber / Smooth $L_1$**: Combina $L_2$ para errores pequeños y $L_1$ para errores grandes.

**Funciones de pérdida basadas en el margen** (clasificación $y\in\{1,-1\}$)
 El margen es $y_i·f(x_i;Φ)$ siendo positivo si la predicción es correcta y negativo si es incorrecta.
 - **Pérdida 0/1-Loss**: $L_{0-1} = I(y·f(x;Φ)<0).$ Es 1 si se falla, 0 si se acierta
 - **Pérdida exponencial ($L_{exp}$):** $e^{-y·f(x;Φ)}$. Utilizada por **AdaBoost** 
 - **Pérdida Hinge ($L_{Hinge}$)**: $max(0,1-y·f(x;Φ))$.
## Entrenamiento de modelos

**Descenso de gradiente** (Gradient Descent - GD)
El algoritmo busca moverse en la dirección opuesta al vector gradiente $(∇Φ​J)$ que indica la **dirección de máximo incremento de $J$**. 
- **Actualización**: $Φ​_{t+1}\leftarrow Φ_t-\alpha\frac{∂J(Φ)}{∂Φ}|_{Φ=Φ_t}$
- **Tasa de aprendizaje ($\alpha$)**: Escalar positivo que determina la magnitud del cambio (o *learning rate*)
- **Gradiente: $∇Φ​J$** indica los cambios que sufre $J$ ante pequeños cambios en los parámetros. Es lineal con respecto a los ejemplos, pero no lineal con respecto a los parámetros.

**Descenso de Gradiente Estocástico (SGD) con Mini-batches**
Usa una muestra de datos ($B_t$) para estimar el gradiente, lo cual es menos costoso computacionalmente que usar todo el *batch* completo (GD) 

>[!NOTE]
>Queremos decir básicamente, que es más fácil empezar a trabajar con un subconjunto de todos nuestros ejemplos que con todos a la vez.

- **Estimación del Gradiente:** Se calcula como el promedio de los gradientes de la pérdida para los ejemplos dentro del mini-batch
- **Época (Epoch):** Una vez que todos los datos de entrenamiento han sido procesados (usando mini-batches) se completa una época.
- **Cálculo de iteraciones**: El número de iteraciones necesarias para completar 1 época es $N/N_B$. Por ejemplo, 1500 ejemplos con batches de 128 requieren **12 iteraciones**.

**Optimizadores avanzados**
- **Momento (momentum):** Suma ponderada del gradiente actual y los anteriores. Ayuda a reducir el comportamiento oscilatorio en los valles, logrando una trayectoria más suave y acercándose al óptimo en menos iteraciones.
- **Adam (Adaptive Moment Estimation):** Utiliza el momentum para estimar tanto el gradiente como el gradiente al cuadrado. Permite que **cada parámetro tenga su propio *learning rate* efectivo** que se recalcula en cada iteración. Con Adam, no es estrictamente necesario aplicar una planificación del *learning rate* (aunque a menudo se usa)
## Cálculo eficiente del gradiente (Backpropagation)

**Grafos de Cómputo y Regla de la Cadena**
Los modelos complejos se representan como un **gráfo de cómputo** (composición de funciones).
- El cálculo del gradiente se basa en la **regla de la cadena**
- Si un parámetro o entrada influye en la pérdida a traves de **múltiples caminos** en el grafo, las derivadas calculadas a través de cada camino **se suman** para obtener la derivada total.

**Retropropagación (Backpropagation)**
Técnica para el **cálculo eficiente del gradiente en redes de neuronas**
1. **Fase forward** - Se ejecuta el grafo, obteniendo la salida y almacenando los valores de los nodos y las derivadas locales (derivadas de la salida de un nodo con respecto a sus entradas)
2. **Fase Backward** - Se aplica la regla de la cadena desde el nodo final (la pérdida $J$) hacia el principio, multiplicando las derivadas locales a medida que el gradiente "retrocede". Esto calcula la derivada de $J$ con respecto a cada parámetro o entrada.
## Estimación del rendimiento: sesgo y varianza
La capacidad de un modelo para generalizar se analiza mediante el **sesgo (bias)** y la **varianza (variance)**

| Concepto              | Descripción                                                                                                       | Consecuencia en el error                                                                                            | Cómo reducirlo                                                     |
| --------------------- | ----------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------ |
| **Sesgo/Bias**        | Desviación sistemática de la media de la función real, debida a limitaciones del modelo (modelo demasiado simple) | **Subajuste (Underfitting)**: El modelo no puede capturar la complejidad de los datos                               | Aumentar la complejidad o número de parámetros del modelo          |
| **Varianza/Variance** |                                                                                                                   | **Sobreajuste (Overfitting)**: El modelo describe peculiaridades estadísticas (ruido) del conjunto de entrenamiento | Aumentar el número de datos de entrenamiento o usar regularización |

**Relación Sesgo-Varianza (Trade-off)**
Existe un compromiso: aumentar la complejidad del modelo (en pos de reducir el sesgo) generalmente aumenta la varianza.

**Métodos de evaluación**
- **Hold-out**: Dividir los datos en entrenamiento ($D_e$) y prueba ($D_t$)
- **Validación Cruzada (Cross-Validation)**: Partir los datos en $V$ grupos. Se entrenan $V$ modelos, usando $V-1$ grupos para entrenar y 1 para validar, promediando la pérdida.
- **Leave-One-Out (LOO)**: Caso especial de CV donde $V=N$ (el número de datos)

**Usos de conjuntos de datos**
Para un método de trabajo adecuado, dividimos los datos en tres conjuntos:
1. **Entrenamiento ($D_{train}$)**: Usado para la optimización de los parámetros (Φ)
2. **Validación ($D_{val}$) :** Usado para **seleccionar hiperparámetros** (ej. *learning rate*, fuerza de regularización) y detectar sobreajuste/subajuste
3. **Test ($D_{test}$)** Únicamente para reportar el **rendimiento final**
## Regularización
La regularización incluye métodos diseñados para reducir el **error de generalización** (normalmente reduciendo la varianza).

**Regularización explícita**
Consiste en añadir un término $g[Φ]$ a la función de coste.$$Φ=arg \space min_Φ[\sum_{i=1}^NL(f(x_i,Φ),y_i)+\lambda·g[Φ]]$$
Siendo:
- $\lambda$ **(Lambda)**: Lo que controla la fuerza de la regularización
- **Interpretación probabilista:** La regularización explícita es equivalente a imponer una **distribución a priori ($Pr(Φ)$)** sobre los parámetros.
- **Regularización $L_2$ (Ridge Regression/Weight Decay):** $g[Φ]=\sum_jϕ_j²$. Favorece parámetros más pequeños, lo que aumenta la suavidad fuera de los datos de entrenamiento y ayuda a reducir el sobreajuste.

**Regularización implícita**
Métodos que reducen el error de generalización sin modificar la función de coste:
- **Early Stopping**: Detener el entrenamiento cuando la pérdida en el conjunto de validación ($J(D_{val})$) comienza a aumentar. Tiene un efecto similar a la regularización $L_2$
- **Aumento de datos (Data Augmentation)**
- Usar *learning rates* más grandes o *mini-batches* más pequeños.
















































