## ¿Cómo de bueno es mi modelo?
Aprendido un modelo, hay que evaluarlo. En caso de aprender varios, necesitamos una medida para elegir el que implementamos en el sistema a desplegar. Esto lo implementa `sklearn.metrics`. 
## Calidad de los modelos de regresión
Esta es la métrica típica:$$R^2(y, \hat{y}) = 1 - \frac{\sum_{i=1}^{N} (y^{(i)} - \hat{y}^{(i)})^2}{\sum_{i=1}^{N} (y^{(i)} - \bar{y})^2}$$<br>
donde $\overline{y}$ es la media de los valores de $y$, siendo ${\hat{y}^{(i)}}$ la estimación del modelo para el ejemplo i-ésimo. A la diferencia interior de ys se le llama residuo. Con la división comparamos el cuadrado de los residuos con la dispersión de los targets respecto de su media. $R^2 = 1$ sólo si ambos residuos son 0. Por tanto, cuanto más cercano a 1, mejor el modelo. 
## Calidad de los modelos de clasificación binaria
Al predecir entre dos clases o se acierta de dos formas o se falla de dos. Veamos la imagen qu    dice el siguiente ejemplo:    
![[Ejemplo Clasificación Binaria.png]]
Si hacemos un recuento para cada ejemplo del conjunto de test, podemos escribir los cuatro casos en una tabla llamada **matriz de confusión**. 
![[Matriz de confusión.png]]
### Medidas derivadas de la matriz de confusión
Podemos sacar las siguientes:
- **Precision**
	- Significa que todos los ejemplos estimados como positivos lo eran cuando = 1
- **Recall**
	- Es que todos los ejemplos positivos están bien estimados cuando = 1
- **F1-score**
	- Media entre las dos de arriba
- **Accuracy**
	- Porcentaje total de aciertos
## Curva ROC y AUROC
Dado un modelo que estima la probabilidad $p(y=1|x)$ tal que $\hat{y}=1$ si $p(y=1|x) > \theta$; la curva **ROC**es el trazado de pares cuando hacemos variar el umbral $0 < \theta < 1$. 

La curva es diferente a la matriz de confusión porque se calcula para todo el rango de posibles umbrales $\theta$ mientras que la matriz de confusión ya asume uno fijado. Gracias a ello, si elegimos el umbral que da lugar al par más cercano al punto (0, 1), estaremos tomando un buen compromiso de rendimiento.

Por otro lado midiendo el área bajo la curva ROC (*Area Under ROC*, AUROC) podemos comparar modelos: cuanto mayor sea **AUROC**, **mejor es el modelo**.
