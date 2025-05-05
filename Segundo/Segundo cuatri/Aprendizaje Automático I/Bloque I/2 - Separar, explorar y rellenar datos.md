## Separar
NUNCA hemos de usar todos los ejemplos para una tarea. Esto es porque nuestro objetivo es tener una máquina autónoma que reacciona a nuevos ejemplos que le lleguen una vez desplegada y arrancada. Así, necesitamos guardarnos algunos ejemplos para usarlos ya después de entrenar la máquina.

Cuando tenemos un conjunto de datos, reservamos entre un 10% y un 20% de estos, formando el **Conjunto de Test**. El resto es el **Conjunto de Entrenamiento**. El de test no se usa hasta estar la máquina terminada del todo
## Explorar
Proceso para comprender datos y relacionarlos
### Descripción estadística básica
Hay que hacer un informe que resume y proporcione información a ser posible, sobre el tipo de dato de los ejemplos y cómo se describen. 

Nuestro informe tiene que tener:
- Tamaño del conjunto de datos
- Atributos NO numéricos y convertirlos
- Media y desviación estándar de cada atributo
- Mediana de cada atributo
- Moda de cada
- Máximo y mínimo de cada
## Preprocesado de datos
Buscamos desarrollar métodos capaces de procesar y preparar los datos de forma automática, requiriendo en lo menos posible al humano.

Tenemos los siguientes tipos de tareas a automatizar:
- Tratamiento de valores perdidos
- Eliminar atributos innecesarios o seleccionar los que vamos a usar
### Tratamiento de valores perdidos
Estos son más comunes de lo que uno piensa. Para tratarlos tenemos que:
- Averiguar dónde están
- Valorar si rellenamos los huecos (imputación) o tomamos otra decisión como borrar el ejemplo o el atributo.
- Opcional pero podemos añadir una nueva columna a la derecha de aquella donde hayamos imputado valores, marcando las celdas donde ha habido imputación como muestra la figura de abajo.
#### Localización
En Pandas usamos un `isnull()` o un `isna()` que devuelven True o False por cada celda del dataframe con un NaN. Son idénticos ambos métodos
#### Imputación univariada
Vamos a imputar valores al resto de los NaN. La técnica más sencilla es esta, que consiste en asignar un estadístico de la columna a todos los NaN que haya en ella, y repetir este proceso para cada columna. Este estadístico puede ser:
- la **media**, si los valores de ese atributo están distribuidos según una normal.
- la **mediana** si no lo están. Mejor opción por lo general
- el **valor más repetido**
Lo malo es que esta técnica puede crear ejemplos imposibles:
1. Caso de columna con tiempo -> No tiene sentido rellenar con la media o mediana de marcas de tiempo, sería mejor interpolar la serie, con `interpolate()`
2. Con datos médicos podría pasar que si tenemos que rellenar el género de un individuo y la media es ser mujer, al poner este dato y luego verificar que por ejemplo se ha operado de la próstata, se nos crea un ejemplo imposible. Para evitar esto usamos la imputación multivariada
#### Imputación multivariada
Calculamos el valor imputado en función del resto de atributos. Desconocemos por completo la función, pero siendo pocos los valores perdidos, una solución es estimarlo mediante una regresión.

Cuando haya varios valores perdidos se repite el proceso iterativamente rellenando consecutivamente, siendo esto conocido como **imputación iterativa**

**¿Cómo calculamos las funciones de regresión?**
Es una de las tareas básicas de ML. Anteriormente sabíamos que una manera es ir ajustando los parámetros de una recta mediante mínimos cuadrados, como vimos en [[Métodos Operativos y Estadísticos de Gestión]].

Esto habríamos de hacerlo en cada iteración pero:
1. La función de regresión sería muy básica -> Es raro que todos los atributos perdidos se adecuen a un modelo lineal
2. Conlleva bastante código