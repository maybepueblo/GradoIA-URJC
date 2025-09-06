Ya comentábamos cómo se representan los ejemplos con los que aprenden nuestras máquinas en [[1 - Tipos de datos]]. En muchas ocasiones estos atributos son suficientes, pero en otras no nos dan todo lo que necesitamos para hacer la tarea. Ahí queremos crear nuevas columnas para intentar lograr mejores resultados.

En esta parte empezaremos con `Scikit-Learn`. Llamamos al **vector características** a lo que usamos para describir cada ejemplo de manera definitiva, es el vector que finalmente usamos para aprender la tarea. Este puede coincidir con los atributos o ser menor o mayor:
- **Menor**: Hemos eliminado atributos no útiles.
- **Mayor**: Hemos añadido calculando a partir de las existentes.
- **Igual**: Nos quedamos exactamente con los atributos dados o creamos tantas columnas como las eliminadas
## Aumento de la dimensionalidad
Esto significa añadir nuevas características calculadas a partir de lo que tenemos. A diferencia de la imputación iterativa, no tenemos que calcular una función de regresión; sino que somos nosotros los que elegimos el modo en el que construimos las características. 

Esto sale bien si sabemos sobre el problema, si no, aún teniendo experiencia podemos no dar con la fórmula para generar características "potentes". Un buen arreglo es lanzar una batería de transformaciones sobre las características; y un modo organizado es creando todas las combinaciones de un cierto grado polinómico a elegir.

Veamos cómo se hace con sklearn:
```python
# Ejemplo de como hacer aumentado de dimensionalidad mediante
# características polinómicas.

degree = 2 # máximo grado de polinomios resultantes
interaction_only = True # quitar las características que actúan consigo misma

df = pd.DataFrame({'x1': [1, 2, 3], 'x2': [4, 5, 6], 'x3': [7, 8, 9]})

polyf = PolynomialFeatures(degree=degree, # objeto de clase PolynomialFeatures
                           interaction_only=interaction_only)
polyf.set_output(transform="pandas")

# LLevan los objetos atributos (información) pero además métodos como fit y transform, que junto a predict son los que necesitamos siempre

polyf.fit(df)
df_poly = polyf.transform(df)
# Se podría hacer un fit_transform que existe, pero el profesor prefiere hacer fit sólo con el conjunto de train y el transform con el train y el test

print('Dataframe inicial:')
print(df)
print('\nDataframe aumentado:')
print(df_poly)
``` 

La salida de esto es:
```python
Dataframe inicial:
   x1  x2  x3
0   1   4   7
1   2   5   8
2   3   6   9

Dataframe aumentado:
     1   x1   x2   x3  x1 x2  x1 x3  x2 x3
0  1.0  1.0  4.0  7.0    4.0    7.0   28.0
1  1.0  2.0  5.0  8.0   10.0   16.0   40.0
2  1.0  3.0  6.0  9.0   18.0   27.0   54.0
```
## Reducción de la dimensionalidad
### Transformaciones sin modificar
Se considera que hacer modificaciones (sin crear uno nuevo) es parte de esto. Estudiaremos transformaciones lineales. En concreto:
- intervalo unidad
- máximo en valor absoluto
- estandarización
#### Intervalo unidad
Dada una columna x, la siguiente fórmula lo escala todo al intervalo [0, 1]
$$x_{esc}=\frac{x-x_{min}}{x_{max}-x_{min}}$$
- Se debe hacer la operación columna a columna ya que los valores máximo y mínimo de xi pueden ser diferentes a los de xj
- Como resultado tenemos todas las características a la misma escala.
- Podemos usar `sklearn.preprocessing.MinMaxScaler`
#### Máximo en valor absoluto
Escalamos de modo que:
- si todos son positivos, máximo 1 y mínimo mayor que cero
- si todos son negativos, mínimo -1 y todos menores a cero
- positivos y negativos pues se quedan en [-1, 1]
$$x_{esc}=\frac{x}{max(|x|)}$$
- Podemos hacerlo columna a columna ya que el máximo del valor absoluto de los valores de dos columnas pueden ser diferentes.
- Podemos usar `sklearn.preprocessing.MaxAbsScaler`
#### Estandarización
La fórmula de siempre de la estandarización con la media y la desviación.
$$x_{std}=\frac{x-\mu}{\sigma}$$
Esto significa que tiene media cero y desviación unidad. NO significa que hayamos convertido la distribución de **x** en una normal. Usaríamos `sklearn.preprocessing.StandardScaler`