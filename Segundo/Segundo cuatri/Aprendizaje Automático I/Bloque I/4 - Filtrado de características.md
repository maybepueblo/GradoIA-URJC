## Reducción de dimensionalidad por filtrado
Para cada característica de la tabla de datos calculamos una puntuación de cuanta relevancia tiene o de sus posibilidades para contribuir a realizar la tarea. En este filtrado eliminamos todas aquellas características cuya puntuación no supera un umbral (*threshold*) elegido por nosotros. Por esto se dice que son técnicas de selección de características.

Aprendemos a filtrar por:
- varianza
- correlación
- información mutua 
### Por varianza
Decimos que la varianza es el promedio de las diferencias con la media elevadas al cuadrado. Este filtrado consiste en eliminar todas las columnas cuya varianza no supere un umbral.

**¿Qué ocurre si una característica tiene una varianza pequeña?**
Significa que esa columna no aporta nada. Podríamos convertirla en una columna de unos simplemente diviendo por el valor repetido una y otra vez. Sin llegar ahí, cuanto más pequeña sea la varianza, menos variabilidad hay en la característica para la que se calcula. Una columna sin variabilidad es casi constante, lo que resulta en no aportar mucho a una máquina para tareas de ML.

Tenemos que fijar un umbral medianamente bajo para asegurar esa condición. La varianza es sensible al orden de magnitud de los datos. Si ***c*** es una constante entonces $~{\rm Var}(c·X) = c^2·{{\rm Var}}(x).$ Lo que significa que si escalamos los datos al intervalo unitario, cambiaremos su varianza.

En python:
- **Pandas**
	- Usamos var() de un DF
	- Calculamos la varianza de la muestra que divide entre N - 1
	- Se puede modificar con la opción `ddof=0`. Ahí estaremos dividiendo entre *N* y calculando la varianza de la población.
- **SciKit-Learn**
	- Usamos `sklearn.feature_selection.VarianceThreshold`
	- El propio método calcula la varianza poblacional de los datos
### Por correlación
Si están correlacionadas significa que existe entre ambas una relación lineal. Es decir, que cuando una crece o decrece, la otra lo hace proporcionalmente. Por tanto, no necesitamos ambas, basta con una de ellas porque la otra nos aporta exactamente la misma información, salvo por una escala y quizás, un desplazamiento (*offset*).

Esto solo ocurre si la correlación entre ambas es +1 o -1. Cuanto más cerca a los extremos, más correlación, lo inverso en cuanto al 0. Así, decimos que otra forma de filtrar características es obtener la matriz de correlación y buscar las celdas de la matriz próximas a 1 o -1. Supongamos que pij = Corr(xi, xj) es la correlación entre las características xi y xj. Si el valor absoluto de pij es 1 aprox, podemos eliminar xi o xj. 
## Por información mutua
Este mide la reducción de la incertidumbre (entropía) de una variable aleatoria X cuando se conoce el valor de otra Y. Estos conceptos se dejan para más adelante.