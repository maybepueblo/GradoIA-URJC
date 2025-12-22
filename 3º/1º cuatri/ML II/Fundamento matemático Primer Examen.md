El siguiente resumen detalla y clasifica toda la matemática fundamental y las fórmulas específicas que se encuentran en los temas proporcionados (Modelos, Funciones de Pérdida, Optimización, Backpropagation y Combinación de Estimadores).

---
### I. Modelos y Notación

#### A. Notación General

La notación utilizada sigue convenciones estándar:

- **Escalar (Normal):** $x$.
- **Vector (Negrita):** $\mathbf{x}, \mathbf{w}, \mathbf{\Phi}$.
- **Matriz (Negrita Mayúsculas):** $\mathbf{X}, \mathbf{\Omega}$.

#### B. Modelos Lineales

1. **Modelo Lineal (Regresión Simple)**: $$y = f(x; \mathbf{w}) = w_0 + w_1x$$
2. **Modelo Lineal (Múltiples Variables, Ejemplo)**: $$f(x_1, x_2, \mathbf{w}) = w_0 + w_1x_1 + w_2x_2$$
3. **Modelo Lineal (Forma Vectorial/Matricial)**: $$\mathbf{y} = \mathbf{X}\mathbf{w} + \mathbf{b}$$ _Donde $\mathbf{X}$ son los datos de entrada, $\mathbf{w}$ son los pesos y $\mathbf{b}$ es el sesgo._

#### C. Estructura de Redes Neuronales (Shallow Network)

Una capa de una Red Neuronal se describe mediante transformaciones lineales seguidas de una activación:

1. **Pre-activación (Capa Lineal $0$):** $$\mathbf{z} = \mathbf{\Omega}^0\mathbf{x} + \mathbf{\beta}^0$$
    
2. **Activación de la Capa Oculta:** $$\mathbf{h} = a(\mathbf{z})$$
    
3. **Salida (Capa Lineal $1$):** $$\mathbf{y} = \mathbf{\Omega}^1\mathbf{h} + \mathbf{\beta}^1$$
    
4. **Función General del Modelo (Red de 1 capa oculta):** $$\mathbf{y} = \mathbf{\Omega}^1 a(\mathbf{\Omega}^0\mathbf{x} + \mathbf{\beta}^0) + \mathbf{\beta}^1$$
    
5. **Cálculo de Parámetros** (Para $D_i$ entradas, $D_h$ unidades ocultas, $D_o$ salidas): $$\text{Parámetros} = (\mathbf{\Omega}^0) + (\mathbf{\beta}^0) + (\mathbf{\Omega}^1) + (\mathbf{\beta}^1)$$ $$\text{Total} = (D_h \times D_i) + D_h + (D_o \times D_h) + D_o$$ _(Ejemplo: 5 entradas, 2 ocultas, 4 salidas: $(2 \times 5) + 2 + (4 \times 2) + 4 = 24$ parámetros)._
    

### II. Funciones de Pérdida y Coste

El entrenamiento consiste en minimizar la **Función de Coste Empírica** $J(\mathbf{\Phi})$ sobre el conjunto de entrenamiento $D={\mathbf{x}_i, y_i}_{i=1}^N$.

#### A. Definición de Coste

- **Pérdida (Loss) para un dato $i$**: $L(y_i, \hat{y}_i)$, donde $\hat{y}_i = f(\mathbf{x}_i; \mathbf{w})$.
- **Función de Coste Empírica (Riesgo Empírico)**: $$J(\mathbf{w}) = \frac{1}{N} \sum_{i=1}^N L(f(\mathbf{x}_i,\mathbf{w}), y_i)$$
- **Pérdida Ideal (Esperada)**: $$J(\mathbf{w}) = E_{(\mathbf{x}, \mathbf{y})\sim p(\mathbf{x}, \mathbf{y})}[L(f(\mathbf{x};\mathbf{w}), \mathbf{y})]$$

#### B. Pérdidas de Regresión

1. **Error Cuadrático Medio (Mean Squared Error - MSE)**: $$L(y_i, \hat{y}_i) = (y_i - \hat{y}_i)^2$$ _MSE es más sensible a _outliers_ que MAE._
    
2. **Error Absoluto Medio (Mean Absolute Error - MAE)**: $$L(y_i, \hat{y}_i) = |y_i - \hat{y}_i|$$ _MAE penaliza fundamentalmente los errores pequeños._
    
3. **Pérdida de Huber (Smooth L1)**: $$L_{\text{Huber}}(y, \hat{y}, \delta) = \begin{cases} \frac{1}{2} \cdot (y - \hat{y})^2 & \text{si } |y - \hat{y}| < \delta \ \delta \cdot (|y - \hat{y}| - \frac{\delta}{2}) & \text{si } |y - \hat{y}| \ge \delta \end{cases}$$
    

#### C. Pérdidas de Clasificación (Basadas en el Margen $y_i \cdot f(\mathbf{x}_i;\mathbf{\Phi})$)

Las pérdidas de clasificación binaria a menudo utilizan etiquetas $y \in {-1, 1}$.

1. **Pérdida $0/1$ (Error de Clasificación)**: $$L_{0-1}(y_i, f(\mathbf{x}_i;\mathbf{\Phi})) = I(y_i \cdot f(\mathbf{x}_i;\mathbf{\Phi}) < 0)$$ _Donde $I(\cdot)$ es la función indicadora._
2. **Pérdida Exponencial (Usada por AdaBoost)**: $$L_{\exp}(y_i, f(\mathbf{x}_i;\mathbf{\Phi})) = e^{-y_i \cdot f(\mathbf{x}_i;\mathbf{\Phi})}$$
3. **Pérdida Hinge (SVM)**: $$L_{\text{Hinge}}(y_i, f(\mathbf{x}_i;\mathbf{\Phi})) = \max(0, 1 - y_i \cdot f(\mathbf{x}_i;\mathbf{\Phi}))$$

#### D. Pérdidas de Clasificación (Basadas en Probabilidad $\hat{y} \in$)

1. **Entropía Cruzada Binaria (Binary Cross-Entropy - BCE)**: $$L(y, \hat{y}) = -y \cdot \log(\hat{y}) - (1 - y) \cdot \log(1 - \hat{y})$$ _Donde $y \in {0, 1}$ es la etiqueta y $\hat{y}$ es la probabilidad posterior estimada por el modelo, típicamente después de una función Sigmoide._
2. **Entropía Cruzada Multiclase (Multiclass Cross-Entropy Loss)**: _Se utiliza con la función Softmax en la salida._ $$J(\mathbf{l}, \mathbf{s}) = -\sum_{i=1}^K I(\mathbf{l}=i) \log(\mathbf{s}_i)$$ _Donde $\mathbf{s}$ son las probabilidades de salida (Softmax) y $\mathbf{l}$ es la etiqueta verdadera (codificada como vector unitario $I(\mathbf{l}=i)$)._

### III. Optimización y Descenso de Gradiente

#### A. Actualización de Parámetros (Descenso de Gradiente - GD)

El gradiente $\nabla_{\mathbf{\Phi}} J$ indica la dirección de máximo incremento de $J$. La actualización se realiza en la dirección opuesta, con tasa de aprendizaje $\alpha$: $$\mathbf{\Phi}^{t+1} \leftarrow \mathbf{\Phi}^t - \alpha \frac{\partial J(\mathbf{\Phi})}{\partial \mathbf{\Phi}} |_{\mathbf{\Phi}=\mathbf{\Phi}^t}$$

#### B. Descenso de Gradiente Estocástico (SGD con Mini-batches)

El gradiente se calcula como la media de las derivadas de la pérdida individual de los ejemplos en el mini-batch $B_t$ (con tamaño $N_B$): $$\frac{\partial J(\mathbf{\Phi})}{\partial \mathbf{\Phi}} |_{\mathbf{\Phi}=\mathbf{\Phi}^t} \leftarrow \frac{1}{N_B} \sum_{i \in B_t} \frac{\partial L(f(\mathbf{x}_i;\mathbf{\Phi}), y_i)}{\partial \mathbf{\Phi}} |_{\mathbf{\Phi}=\mathbf{\Phi}^t}$$

#### C. Estimación de Iteraciones por Época

Para $N$ datos y mini-batches de tamaño $N_B$, si el muestreo es sin reemplazamiento, el número de iteraciones para una época es: $$\text{Iteraciones por época} = \lceil N / N_B \rceil$$ _(Ejemplo: 1500 datos, $N_B=128$: $\lceil 1500/128 \rceil = 12$ iteraciones)._

#### D. Regularización Explícita (L2)

La regularización se añade como un término penalizador a la función de coste estándar: $$\hat{\mathbf{\Phi}} = \arg \min_{\mathbf{\Phi}} \left[ \sum_{i=1}^N L(f(\mathbf{x}_i, \mathbf{\Phi}), y_i) + \lambda \cdot g[\mathbf{\Phi}] \right]$$ **Regularización L2 (Ridge Regression)**: $$\hat{\mathbf{\Phi}} = \arg \min_{\mathbf{\Phi}} \left[ J(\mathbf{\Phi}, {\mathbf{x}_i, y_i}) + \lambda \cdot \sum_j \mathbf{\Phi}_j^2 \right]$$

### IV. Cálculo Eficiente del Gradiente (Backpropagation)

El algoritmo de Backpropagation se basa en la Regla de la Cadena y la retropropagación de gradientes a través de grafos de cómputo.

#### A. Regla de la Cadena

1. **Para Funciones Compuestas Escalares**: $$\frac{dz}{dx} = \frac{dy}{dx} \cdot \frac{dz}{dy}$$ _Si $z = f(y)$ y $y = g(x)$._
2. **Para Funciones Compuestas Vectoriales/Matriciales (Producto de Jacobianos)**: $$\frac{d \mathbf{z}}{d \mathbf{x}} = \frac{d \mathbf{y}}{d \mathbf{x}} \cdot \frac{d \mathbf{z}}{d \mathbf{y}}$$

#### B. Retropropagación en Grafos de Cómputo

- **Principio de la Retropropagación**: En un nodo, la derivada del coste total ($J$) con respecto a una entrada ($x$) se calcula multiplicando la derivada local del nodo por el gradiente que llega desde el final del grafo: $$\frac{\partial J}{\partial x} = \frac{\partial z}{\partial x} \cdot \frac{\partial J}{\partial z}$$
- **Suma de Gradientes (Múltiples Caminos)**: Si una variable de entrada ($a$) afecta al resultado final ($L$) a través de múltiples caminos en el grafo, se deben sumar las derivadas calculadas a través de cada camino: $$\frac{\partial L}{\partial a} = \left(\frac{dr}{da} \cdot \frac{dt}{dr} \cdot \frac{\partial w}{\partial t} \cdot \frac{dL}{dw}\right) + \left(\frac{\partial s}{\partial a} \cdot \frac{dv}{ds} \cdot \frac{\partial w}{\partial v} \cdot \frac{dL}{dw}\right)$$ _Fórmula específica del ejemplo de grafo donde $L$ depende de $a$ a través de $r$ y $s$._

#### C. Derivadas de Pérdidas Específicas (Ejemplo de Capa Lineal y Pérdida Exponencial)

Dadas las funciones $\mathbf{g}(\mathbf{x}) = \mathbf{b} + \mathbf{W}\mathbf{x}$ y $f(\mathbf{y}, \mathbf{t}) = e^{-\mathbf{y}^T\mathbf{t}}$:

- **Derivada del modelo respecto al sesgo (Jacobiano)**: $$\frac{\partial \mathbf{g}(\mathbf{x})}{\partial \mathbf{b}} = \begin{bmatrix} 1 & 0 \ 0 & 1 \end{bmatrix}$$
- **Derivada de la pérdida exponencial respecto a la pre-activación $\mathbf{t}$**: $$\frac{\partial f(\mathbf{y}, \mathbf{t})}{\partial \mathbf{t}} = \begin{bmatrix} -y_1 \cdot e^{-(y_1t_1 + y_2t_2)} \ -y_2 \cdot e^{-(y_1t_1 + y_2t_2)} \end{bmatrix}$$
- **Derivada compuesta por Regla de la Cadena** ($\mathbf{t} = \mathbf{g}(\mathbf{x})$): $$\frac{\partial f(\mathbf{y}, \mathbf{g}(\mathbf{x}))}{\partial \mathbf{b}} = \frac{\partial \mathbf{g}(\mathbf{x})}{\partial \mathbf{b}} \frac{\partial f(\mathbf{y}, \mathbf{t})}{\partial \mathbf{t}} = \begin{bmatrix} 1 & 0 \ 0 & 1 \end{bmatrix} \begin{bmatrix} -y_1 \cdot e^{-(\mathbf{y}^T\mathbf{t})} \ -y_2 \cdot e^{-(\mathbf{y}^T\mathbf{t})} \end{bmatrix} = \begin{bmatrix} -y_1 \cdot e^{-(\mathbf{y}^T\mathbf{t})} \ -y_2 \cdot e^{-(\mathbf{y}^T\mathbf{t})} \end{bmatrix}$$

### V. Combinación de Estimadores y Métrica Estadística

#### A. Compensación Sesgo-Varianza

El error total de un estimador de regresión se puede descomponer en tres componentes: $$\text{Error} = \text{Ruido} + \text{Varianza} + \text{Sesgo}^2$$

- **Varianza**: Incertidumbre en el modelo debido a la elección específica del conjunto de datos.
- **Sesgo**: Desviación sistemática de la media de la verdadera función debido a las limitaciones del modelo.
- **Ruido**: Incertidumbre inherente en la función verdadera.

#### B. Métricas de Árboles de Decisión

Los árboles de decisión utilizan métricas para determinar el mejor punto de partición:

1. **Entropía de un conjunto de datos $A$**: $$H(A) = - \sum_k \left(p_k^A \log(p_k^A)\right)$$ _Donde $p_k^A$ es la proporción de datos de la clase $k$ en $A$._
2. **Ganancia de Información ($I_E$)**: $$I_E = H(S) - \frac{|S_{\text{izq}}|}{|S|} H(S_{\text{izq}}) - \frac{|S_{\text{der}}|}{|S|} H(S_{\text{der}})$$

#### C. AdaBoost (Boosting Biclase)

- **Importancia del Clasificador Débil ($\alpha_m$)**: El peso asignado al clasificador $G_m$ se calcula a partir de su error $err_m$: $$\alpha_m = \log \left( \frac{1 - err_m}{err_m} \right)$$

#### D. Gradient Boosting

- **Ajuste del Estimador Básico**: En Gradient Boosting, el clasificador base $b$ debe entrenarse para estimar el gradiente de la función de pérdida $L$ cambiado de signo, evaluado en la aproximación actual del modelo $f_{m-1}$: $$g_m = \frac{\partial L(y, f(\mathbf{x}))}{\partial f(\mathbf{x})} |_{\mathbf{f}=f_{m-1}}$$ La actualización aditiva es: $f_m(\mathbf{x}) = f_{m-1}(\mathbf{x}) - \alpha \cdot g_m$.
