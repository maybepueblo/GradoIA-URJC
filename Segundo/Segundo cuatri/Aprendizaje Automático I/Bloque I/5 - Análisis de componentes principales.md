También conocido como **PCA**. 

Sabemos ahora generar características en función de otras que ya tenemos. No tenemos sin embargo un modo **sistemático** de hacerlo. De momento es todo muy "artesano". La función más sencilla para esto sería la **combinación lineal**. Cada característica es ponderada por un coeficiente y después se suman todas.

El **PCA** es una técnica para sustituir las características originales por nuevas que sean mediante combinaciones lineales de las originales. Tenemos que resolver simplemente cómo calcular los coeficientes. Esto además teniendo en cuenta que el PCA es de reducción de dimensión. Las nuevas características que sustituyen a las originales serán en total menos.
## Ideas clave
- **PCA** no selecciona características, crea nuevas.
- Podemos crear tantas como las que tenemos inicialmente (***D***)
- PERO ADEMÁS, están ordenadas en importancia de mayor a menor. Para reducir la dimensión a d < D podemos empezar a eliminarlas por la última hacia la primera. 
## Cuestiones clave
- ¿Cómo se crean esas nuevas características?
- ¿Cómo se mide la importancia de las nuevas?
- Si eliminamos ¿cuánta info perdemos?
## Notación
Usaremos nuevamente ***N*** y ***D*** para indicar el número de filas y de columnas de la tabla de datos original respectivamente. 
- Usaremos ***d*** para indicar el número de componentes principales que usamos para representar los ejemplos; siendo la dimensionalidad reducida a la que llevamos nuestro conjunto de datos. Como límite: misma dimensionalidad
- x_i^{k} es lo que indica la i-ésima característica del ejemplo k-ésimo
- Similar, usaremos z_j^{k} para lo mismo.
- Los vectores son siempre vectores columna y que un ejemplo aislado es un vector de características. Sin embargo, al representar los conjuntos de datos como tabla, los ejemplos son filas. 
## Fundamento Teórico
### Intuición
Sea un vector x perteneciente a los reales con unas características ***D***. Tratamos de reducir las dimensiones de nuestro vector. No perdiendo información, sino encontrando una forma de representar **x** coon menos dimensiones. Si lo hiciésemos con más dimensiones sería lo mismo, si no logramos que la sumatoria de z hasta D sea igual a 0 pues intentaremos que $\hat{\bf x}$ nueva sea lo más similar posible a x. Siendo la siguiente fórmula el residuo:
$$\epsilon = \sum_{k=d+1}^{D}z_k·u_k$$Este es el vector formado por las coordenadas de  $\hat{\bf x}$ . Cuanto menor el residuo, más parecida será la reconstrucción $\hat{\bf x}$ al original x. 

Uno se pregunta qué podemos hacer nosotros para lograrlo. La idea es encontrar la base U que minimice el residuo. Esto al ser un vector es minimizar su norma-2 al cuadrado. Cómo obtenemos la z? Bueno, pues estas son la proyección del vector x sobre el vector de la base uk, calculado con el producto escalar de ambos:
$$z_k = x^\top u_k$$