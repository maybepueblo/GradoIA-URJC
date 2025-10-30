Esto es un repaso, se vieron en [[Aprendizaje Automático I]] por primera vez.
## Estructura y funcionamiento básico
Modelo de aprendizaje supervisado cuya función es particionar el **espacio de características** de los datos en un conjunto finito de regiones.
1. **Partición del espacio:** El espacio se divide en regiones ({$R_j$})
2. **Respuesta constante:** Para cualquier punto que caiga dentro de una región $R_j$, el árbol devuelve siempre la misma respuesta, $γ_j$.
3. **Representación Matemática:** La función estimada por el árbol se representa como la suma de las respuestas $γ_j$ multiplicadas por una función indicadora que vale 1 si la entrada $x$ está en la región $R_j:T(x;\theta )= \sum_{j=1}^{N_R} γ_j·I(x\in R_j)$ 
## Entrenamiento: Partición Recursiva
El entrenamiento de un árbol implica un proceso de **partición recursiva** del conjunto de datos

**A. Reglas de Corte (Divisiones)**
En cada nodo, el árbol realiza una división basada en una prueba binaria sobre las características.
- **Cortes paralelos a los ejes:** La forma más habitual y rápida de evaluar es poner un umbral a una **única característica** $(x_i > T)$
- **Cortes sin restricciones**: Se pueden usar hiperplanos sin restricciones, aplicando un umbral a una combinación lineal de características ($w^Tx > T$), lo que es más costoso pero generalmente produce árboles más pequeños.
- El proceso recursivo continúa hasta que cada subconjunto (o región) contiene instancias de una sola clase.
**B. Criterios de optimización para clasificación**
Para decidir dónde realizar el corte, el algoritmo busca optimizar una medida de rendimiento en los subconjuntos de datos resultantes (nodos hijos)
- **Entropía:** En problemas de clasificación, se busca minimizar el **desorden o confusión** (entropía) en los nodos hijos.
	- La entropía de un conjunto de datos $A$ se define como $H(A)=-\sum_k(p_k^Alog(p_k^A))$ 
	- Una distribución uniforme tiene más desorden que una en la que una clase concentra toda la probabilidad.
- **Ganancia de información:** La ganancia de información ($I_E$) mide la disminución de la entropía al dividir el conjunto de datos, y se usa para elegir el mejor corte
**C. Criterios de optimización para regresión**
En los árboles de regresión, el lugar de corte se elige para que los subconjuntos de datos en los nodos hijos tengan el menor error cuadrático posible.
- La respuesta del árbol ($γ_m$) en cada región ($R_m$) se define como la media de los valores de las etiquetas de entrenamiento ($y_i$) que caen en esa región.
## Características de Sesgo y Varianza
Los árboles de decisión presentan un equilibrio específico de sesgo y varianza que define su comportamiento y por qué son adecuados para métodos de combinación

| Característica          | Descripción                                                                                                                                                                                                                  |
| ----------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Ventajas**            | Son modelos con **entrenamiento rápido** y son fáciles de implementar. Además, pueden manejar fácilmente un gran número de características.                                                                                  |
| **Sesgo (Bias)**        | Tienen un **sesgo bajo**. Se debe a que, si se les permite crecer sin restricciones, siempre pueden construir un árbol con un **100%** de acierto en el conjunto de datos de entrenamiento (se ajustan muy bien a los datos) |
| **Varianza (Variance)** | Debido a su gran flexibilidad y su ajuste excesivo a los datos de entrenamiento, tienden al **sobreaprendizaje (overfitting)** y no generalizan bien, lo que se traduce en una **varianza alta**                             |
## Uso en combinación de estimadores
Las limitaciones de un árbol individual (alta varianza/bajo sesgo) se convierten en su fortaleza cuando se usan en métodos de conjunto:
- **Bagging (Random Forest)**: El Bagging (y su implementación más famosa, _Random Forest_) está diseñado específicamente para **reducir la varianza**. Por lo tanto, se recomienda usar árboles de decisión **profundos** (con alta varianza, por ejemplo, 16 nodos hoja) como modelos base en Bagging, ya que el proceso de agregación mitigará su inestabilidad
- **Boosting (AdaBoost, Gradient Boosting)**: El Boosting está diseñado principalmente para **reducir el sesgo**. Por ello, requiere que los clasificadores básicos sean **débiles** (o _weak learners_), es decir, modelos con **sesgo alto y baja varianza**. Con Boosting, se utilizan árboles de decisión **simples** (por ejemplo, con solo 2 nodos hoja). El _Gradient Boost_ utiliza la combinación de árboles de regresión.