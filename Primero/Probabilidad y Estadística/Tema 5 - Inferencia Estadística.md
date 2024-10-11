En esta tema buscaremos trabajar con distribuciones donde los parámetros son desconocidos, por ello el nombre de nuestro tema es [[Inferencia Estadística]].

En la vida real no sabemos cuál es la distribución que depende de unos parámetros que tampoco se conocen. En este curso solo asumiremos la distribución, pero escasearán los parámetros, contrario al [[Tema 4 - Variables Aleatorias]] en el cual sí conocíamos la distribución y los parámetros que necesitábamos para aplicar una solución al problema. 

La inferencia se puede obtener de tres formas:

- Estimación puntual --> Dar un valor puntual para aproximar nuestros parámetros.
- Estimación intervalos --> Lo mismo que estimación puntual pero en intervalos.
- Contrastes Hipótesis --> Plantear una hipótesis, su alternativa, recogemos datos y lo que hemos de preguntarnos es si utilizando dichos datos, tendría sentido decir si mu es mayor que un dato o menos que el mismo.

#### Breve introducción a la inferencia estadística

Este apartado sirve a modo de aclaración de algunos conceptos, vamos a tratar los más importantes que ya tocamos en los primeros temas de la asignatura:

- `Población` -> Conjunto de elementos sometidos a estudio
- `Muestra` -> Subconjunto de la población pero que ha de ser representativa de esta.

Bien, entendido esto, vamos a ver qué tipo de problemas trataremos dentro de este tema, los llamados **problemas paramétricos**, estos consisten en asumir el tipo de distribución pero no sus parámetros. Por lo tanto, el objetivo es obtener información sobre los valores de estas medidas.

Como ya se comentó brevemente antes, dividimos los problemas de este tema en criterios estadísticos: 
1. **Estimación puntual**
2. **Intervalos de confianza**
3. **Contraste de Hipótesis**

#### Estimación Puntual 

**Estadístico** -> Es lo que conocemos como una función matemática de una muestra (como la media, la varianza, la cuasi varianza, etc.). Sin embargo, es en realidad una variable aleatoria con su consecuente distribución y sus medidas como la esperanza y la varianza. 

Si tenemos entonces una muestra aleatoria de una población X con una función de masa *f*. Un estimador puntual de cita es una función de la muestra que usamos como un aproximador de este mismo valor cita. Usaremos en este curso los siguientes parámetros:

$$
 Media -(\mu \space \space con \space \space \bar{x}) \\: Varianza -(\sigma^2 \space \space con \space \space s^2 ) \\: Desviación - (\sigma \space \space con \space \space s)
$$

No obstante, si X sigue una distribución de Bernoulli con parámetro p lo calculamos de la siguiente manera:

$$
p \space \space con \space \space \hat{p} = \frac{k}{n} \space \\: k \space siendo \space éxitos \\: n \space siendo \space pruebas totales
$$

#### Estimación por Intervalos de Confianza

Al estimar por este método tenemos que cita es ahora el nivel de confianza 1 - alpha, siendo alpha = 1 - nivel de confianza. En este caso, tendremos un vector de dos números, el menor posible y el mayor que definen el intervalo donde argumentamos que se encuentra el valor del parámetro. 

**¿Qué quiere decir exactamente el nivel de confianza?**

Nos referimos a que, con todas las muestras del mundo y metiendo un intervalo en cada una de ellas, decimos con una certeza del 95% que en estos intervalos de nuestras muestras se encuentra el verdadero valor que buscamos, mientras que el 5% restante de las muestras no tendrían en el intervalo el valor que queremos hallar. 

**Método de la cantidad pivotal**

Obtenemos una función denominada como el método nos dicta. En esta función sabemos la distribución y no dependemos del parámetro. A partir de esta función conoceremos dos números c1 y c2 tales que la probabilidad de que c1 sea menor que la función pero que c1 sea mayor que esta es igual a 1 - alpha, es decir, al nivel de confianza. Si despejamos cita de esta función tendríamos dos intervalos de confianza. Vamos a ilustrarlo matemáticamente para que se vea mejor:

$$
P(c_1 < C(X_1, ..., X_n, \theta) < c_2) = 1 - \alpha
$$
$$
\theta_1(X_1, ..., X_n) < \theta < \theta_2(X_1,...,X_n) 
$$
$$
Intervalo \space de \space confianza = [\theta_1(X_1, ..., X_n)\\,\theta_2(X_1,...,X_n)]
$$
Cabe destacar que el nivel de confianza lo denotamos como 1 - alpha y toma valores entre 0 y 1. Entonces, alpha suele tener valores próximos a cero. Así se verifica que en el centro de la distribución se encuentra nuestro nivel de confianza y en los extremos se encuentra alpha repartido.

![[Pasted image 20240503204558.png]]

Hay varias distribuciones, pero como se nos dan las fórmulas en todos los apuntes, poco hemos de tratar sobre ellas en este documento, dejaré posteriormente todas las fórmulas que nos interesan, ya que con R veremos que la mayoría de cálculos son muy fáciles de hacer.
##### Resumen de IC

He aquí una tabla con un pequeño resumen de los intervalos de confianza más comunes que estudiamos en esta asignatura. 

![[Pasted image 20240503205020.png]]

**¿Esto es todo?**
Es absolutamente todo lo que concierne a los posibles casos que pueden salir en este tema, pero como es mejor un código que mil palabras, luego pondré casos prácticos en R en un apartado de este documento dedicado expresamente a estos ejemplos.
#### Contrastes de Hipótesis

Siempre tenemos que contrastar dos hipótesis: la **hipótesis nula** (que siempre incluye un igual) y la **hipótesis alternativa** 

$$
Hipótesis \space nula = H_0
$$
$$
Hipótesis \space alternativa = H_1
$$

Luego dentro de las hipótesis alternativas tenemos diferentes tipos:

$$
Hipótesis \space  alternativa \space bilateral \rightarrow tipo \neq
$$
$$
Hipótesis \space alternativa \space unilateral \rightarrow tipo \space > o <
$$

Veamos entonces algunos ejemplos:

$$ H_0 \\: \mu \leq 12 \hspace{10mm} H_1 \\: \mu > 12$$
$$ H_0 \\: \mu_E = \mu_T \hspace{10mm} H_1 \\: \mu_E \neq \mu_T $$
$$ H_0 \\: p_M \leq p_H \hspace{10mm} H_1 \\: p_M > p_H $$
##### Observación

- Si se da evidencia contra Ho, se rechaza este hipótesis, y se da por válida la hipótesis alternativa.
- En caso contrario, no rechazaremos Ho pero no indica que sea cierto.

##### Errores

###### Tipo 1

Rechazar Ho cuando es cierto -> alpha = P(Error Tipo I)

$$
Significación \space \space \rightarrow \alpha = P(Rechazar H_0 | H_0 cierto) = P(Tipo I)
$$
###### Tipo 2

No rechazar Ho cuando es falsa -> beta = P(Error Tipo II)

$$ 1 - \beta = P(Rechazar H_0|H_0 falso) = 1 -P(Tipo II) $$
###### Estadístico del Contraste

Función de distribución conocida que da medida de cómo se acercan los resultados de la muestra a la hipótesis nula.

###### Contrastes

- **Contraste significativo** -> Ha de caer en la región de rechazo. Aporta evidencia a favor de la hipótesis alternativa.
- **Contraste no significativo** -> No cae en la región de rechazo. No existen razones para rechazar la hipótesis nula a favor de la alternativa.

### Apartado R 
	
En este apartado voy a tratar un poco algunos sobre teoría de R y ejercicios del tema, ofreciendo el código que uso para resolver los mismos.
#### Contrastes de hipótesis

Veamos un par de ejemplos que nos van a ayudar a entender un poco más sobre el funcionamiento de R a la hora de usarlo en contrastes de hipótesis. Tenemos las siguientes tres funciones que ahora veremos en profundidad.

- **t.test** -> media
- **var.test** -> varianza
- **prop.test** -> proporción

##### La función t.test()

Esta nos sirve para resolver problemas que conciernen a la media de una población comparadas con otra población hipotética o a la media de dos poblaciones comparadas entre sí. Todas estas pruebas tienen en común que se basan en una distribución **t de Student**. Vamos a desglosar la sintaxis de esta función:

```
t.test(x, y = NULL, alternative = c("two.sided", "less", "greater"), mu = 0, paired = FALSE, var.equal = FALSE, conf.level = 0.95)
```

- `x` -> Vector de datos correspondientes a una de las muestras o a la única.
- `y` -> Segunda muestra. Si no existe, no se incluye.
- `alternative` -> Dirección de la hipótesis alternativa, tiene los tres posibles valores que se ven en pantalla - bilateral, unilateral izquierda o unilateral derecha.
- `mu` -> Valor hipotético con el que se compara la media o diferencia de medias.
- `paired` -> Especifica si las dos muestras en caso de que aparezcan son apareadas o no. 
- `var.equal` -> Especifica si podemos suponer varianzas iguales si hay dos medias.
- `conf.level` -> Nivel de confianza.

###### Media de una población (Ejemplo 1 Manual R)

Estos ejemplos que se verán a continuación son sacados del manual de R aportado por la profesora, solamente vamos a comentarlos brevemente:

**Ejemplo 1** Se sospecha que el nivel medio de glucosa en sangre, en ayunas, de las personas diabéticas es de 108 mg/100ml. Para contrastar esta suposición se utilizan análisis de sangre realizados a 45 personas diabéticas en ayunas. Los datos se encuentran en el fichero _diabeticos.txt_. ¿Es correcto asumir que la media del nivel de glucosa en ayunas es de 108 mg/100ml? (Utilícese un nivel de significación del 5%.

Es evidente que la hipótesis busca confirmar que la media es 108mg/100ml. Si denotamos como mu al nivel medio de glucosa en sangre, podemos plantearnos el contraste siguiente:
$$ Ho : \mu = 108 \space frente \space a \space H1: \mu \neq 108$$
Teniendo un tamaño muestral grande (45), no necesitamos la hipótesis de normalidad de datos. Se trata de un contraste sobre la media de una distribución normal, contraste bilateral.

Digamos que tenemos el fichero *diabeticos.txt*. Veamos cómo habríamos de ejecutar el código para realizar el cálculo:

```
datos.diabeticos<-read.table("diabeticos.txt",header=TRUE,dec=".")
t.test(datos.diabeticos$glucosa,alternative="two.sided",mu=108)
```

Si ejecutásemos este código en R, nos otorgaría lo siguiente por pantalla:

```
## 
##  One Sample t-test
## 
## data:  datos.diabeticos$glucosa
## t = -1.6771, df = 44, p-value = 0.1006
## alternative hypothesis: true mean is not equal to 108
## 95 percent confidence interval:
##  103.5965 108.4035
## sample estimates:
## mean of x 
##       106
```

Analicemos esto:

- Nos informa del valor estadístico de contraste (*t = -1.6771*), de los grados de libertad (*df = 44*) y del p-valor (*p-value = 0.1006*). Así, podemos llegar a una conclusión. Dado que el p-valor no es inferior a 0.05 (el valor de alpha) no tenemos suficientes evidencias en los datos para rechazar la hipótesis nula de que la media es 108. 
- Nos recuerda la hipótesis nula que habíamos planteado. 
- Proporciona los estadísticos muestrales usados, como en este caso, la media muestral.

Por lo tanto, y a modo de conclusión, podemos decir que no hay evidencias de que la concentración de glucosa en sangre, en el caso de las personas diabéticas, no sea 108.

###### Diferencia de medias poblacionales independientes (Ejemplo 2 Manual R)

**Ejemplo 2** Un ingeniero industrial ha sintetizado en el laboratorio una feromona con la que pretende luchar contra una plaga de insectos. La feromona se aplica en trampas donde caen los insectos masivamente. Hasta ahora se trabajaba introduciendo otro producto que se supone que atraía al insecto, por lo que el ingeniero desearía demostrar que su feromona sintetizada es más efectiva que dicho producto. Para probar si esto ocurre, prepara 100 trampas con el producto tradicional y 100 con su feromona y las distribuye, contabilizando el número de insectos atrapados en cada una de las 200 trampas. Con esos datos, ¿puede concluir el ingeniero que su feromona es más efectiva que el producto tradicional?

Vamos a ver la terminología:

$$ \mu_V : media \space capturas \space viejo \space producto \\, \mu_N : media \space nueva \space feromona $$
$$H_0 : \mu_V \geq \mu_N \hspace{10mm} H_1 : \mu_V < \mu_N $$

Tenemos las siguientes perspectivas a ver:
- Las muestras son independientes. Es obvio que el producto antiguo no ha tenido nada que ver con el nuevo.
- Nos ha de preocupar la hipótesis de normalidad, si el tamaño es pequeño, debería proceder de una distribución normal, pero no es el caso: ambas muestras son mayores de 30.
- Debemos plantearnos si podemos suponer varianzas iguales o no.

Veamos cómo se usa el código:

```
feromona<-read.table("feromona.txt",header=TRUE)
t.test(x=feromona$Capturas.feromona, y=feromona$Capturas.producto.tradicional,
alternative="greater",mu=0)
```

Bien, ahora, esto es lo que nos da ejecutarlo:

```
## 
##  Welch Two Sample t-test
## 
## data:  feromona$Capturas.feromona and feromona$Capturas.producto.tradicional
## t = 20.437, df = 197.95, p-value < 2.2e-16
## alternative hypothesis: true difference in means is greater than 0
## 95 percent confidence interval:
##  14.2558     Inf
## sample estimates:
## mean of x mean of y 
##     64.94     49.43
```

Si lo analizamos punto por punto tenemos lo siguiente:
- Especifica que se trata de un test t para variables separadas
- Nos da nuevamente el valor de contraste, los grados de libertad y el p-valor. Como el p-valor es menor que alpha podemos concluir que tenemos evidencias en los datos para afirmar con un 95% de confianza que la media de las capturas con la feromona es superior a las capturas con el viejo producto.
- Especifica la hipótesis alternativa.
- Garantiza un intervalo de confianza para la diferencia de las media. El cero no es un valor plausible y hemos rechazado por ello la hipótesis nula.
- Brinda las dos medias muestrales.

Podemos concluir que con un 95% de confianza la feromona es más efectiva que el viejo producto.

###### Diferencia de medias apareadas (Ejemplo 3 Manual R)

**Ejemplo 3** En un programa de Control de Enfermedades Crónicas, la hipertensión está incluida como la primera patología a controlar. 15 pacientes hipertensos son sometidos al programa y su tensión asistólica es controlada antes y después de 6 meses de tratamiento. Los datos son los siguientes:

![[Pasted image 20240505211537.png]]

En este caso tenemos como mu de D al promedio de medidas de tensión asistólica después del tratamiento y por mu de A al mismo promedio antes del tratamiento.

$$ H_0 : \mu_D \geq \mu_A \space frente \space a \space H_1 : \mu_D < \mu_A$$

Veamos el código:

```
tension<-read.table("tension.txt",header=TRUE,dec=".")
t.test(x=tension$inicio, y=tension$fin, alternative="greater",mu=0,paired=TRUE)
```

Este código nos brinda la siguiente información:

```
## 
##  Paired t-test
## 
## data:  tension$inicio and tension$fin
## t = 4.8316, df = 14, p-value = 0.0001332
## alternative hypothesis: true mean difference is greater than 0
## 95 percent confidence interval:
##  16.09828      Inf
## sample estimates:
## mean difference 
##        25.33333
```

- En las dos primeras líneas se nos informa de un test para muestras apareadas.
- Aparece el valor estadístico de contraste, grados de libertad y el p-valor. Podemos concluir que existen evidencias en los datos de la muestra que el tratamiento disminuye el promedio de la tensión asistólica. El p-valor es muy bajo y por ello las diferencias detectadas son muy significativas.
- Aparece la hipótesis alternativa.
- Intervalo de confianza para la diferencia de medias que excluyendo al cero significa que podemos rechazar la nula en favor de la alternativa.
- Aparece el valor muestral de la diferencia de las medias.


##### La función prop.test()

R nos brinda este tipo de contraste de dos formas, mediante una prueba según la **distribución de Pearson** o mediante una prueba binomial exacta. 

En el primer caso se compara la frecuencia de casos favorables en la muestra de los datos con la muestra de casos favorables que habría en una muestra con el mismo número de datos si la hipótesis nula fuera cierta. Se usa estadístico:
$$
X^2 = \sum_i \frac{(O_i-E_i)^2}{E_i}
$$
Esto bajo el supuesto de que ninguna frecuencia esperada E es inferior a 5. En el caso de que lo fuera se usa la correción por continuidad de Yates:
$$
X^2 = \sum_i \frac{(|O_i-E_i|-0.5)^2}{E_i}
$$
La prueba binomial parte del hecho que si la hipótesis nula fuese cierta, la distribución del número de casos favorables en la muestra sería binomial. Valorando el número observado de casos favorables dentro de la distribución binomial se obtiene el p-valor. 

Vamos a partir de que conocemos el número de éxitos y fracasos en la muestra. Si no es así y solo tenemos los datos en una hoja de datos, podemos tabularla mediante la función a la que sólo hay que especificarle a la hoja de datos a tabular y si ésta tuviera más de una variable, cuál queremos tabular. 

Veamos la sintaxis de la función:

```
prop.test(x, n, p = NULL, alternative = c("two.sided", "less", "greater"),
conf.level = 0.95, correct = TRUE)
```

Mejor comentamos los argumentos de la función:
- Podemos especificar dos cosas, o bien el número de éxitos o bien mediante una matriz de dos columnas, el número de éxitos y de fracasos en cada muestra.
- Especifica el número de datos de la muestra en caso de que x sea el número de éxitos, es ignorado en el caso que proporcione también el número de fracasos. 
- Vector de probabilidades de éxito bajo la hipótesis nula. Debe ser un vector de la misma dimensión que el número de elementos especificados.
- Especifica la dirección de la hipótesis alternativa.
- Nivel de confianza.
- Correción por continuidad de Yates. Por defecto está activada.

###### Proporción en población (Ejemplo 4 Manual R)

**Ejemplo 4** En un determinado servicio de odontología se espera que aproximadamente el 75% de las visitas no requieran una extracción dentaria inmediata. En cierto año, de 1225 visitas, 926 no necesitaron una extracción inmediata. ¿Se puede decir que el porcentaje de ese año fue significativamente superior al porcentaje esperado?

Si denotamos por *p* la proporción de visitas que no requieren extracción, se nos pide que contrastemos lo siguiente:
$$H_0:p=0.75\hspace{10mm}H_1:p>0.75$$
Podemos resolver el contraste usando:

```
prop.test(x=926,n=1225,p=0.75,alternative="greater",correct=FALSE)
```

```
## 
##  1-sample proportions test without continuity correction
## 
## data:  926 out of 1225, null probability 0.75
## X-squared = 0.22884, df = 1, p-value = 0.3162
## alternative hypothesis: true p is greater than 0.75
## 95 percent confidence interval:
##  0.7351821 1.0000000
## sample estimates:
##         p 
## 0.7559184
```

Analizamos lo siguiente:

- Especificamos que se trata de un test para la proporción en una muestra.
- Especifica a continuación el valor hipotético en la hipótesis nula.
- Brinda el valor del estadístico y lo que más nos interesa, el *p-valor*. En este caso el p-valor es bastante superior es 0.05, luego sabiendo que no podemos rechazar la hipótesis nula en favor de la alternativa, es decir, no podemos concluir que el porcentaje de visitas esté por encima del 75%
- Recuerda la hipótesis alternativa
- Facilita un intervalo de confianza para la proporción.
- Proporción muestral.

###### Diferencia de las proporciones (Ejemplo 5 Manual R)

Este tipo de contrastes usan también la función pero hemos de indicar cómo usar los datos. Los éxitos y los fracasos de cada muestra deben ir en dos filas de una matriz de dos columnas, tal que así:

```
##      [,1]  [,2] 
## [1,] "n11" "n12"
## [2,] "n21" "n22"
```

Para crearla usamos la función *matrix* de esta forma:

```
matrix(c(n11, n12, n21, n22),2,2,byrow=TRUE)
```

Aquí lo que hemos hecho es especificarle mediante un vector los elementos, las dimensiones, y el sentido en el que vienen los elementos. También podríamos crearla así:

```
matrix(c(n11, n21, n12, n22),2,2,byrow=FALSE).
```

**Ejemplo 5** A raíz de la alarma creada entre la opinión pública por la repercusión que tuvo el caso de un bloque de edificios con un transformador en su planta baja y donde un gran porcentaje de vecinos sufrió cáncer, se decide realizar un estudio para tratar de encontrar relación entre la cercanía de un transformador eléctrico y la incidencia del cáncer.

Para ello, se eligió una muestra aleatoria de edificios con transformadores en su planta baja durante un periodo de más de 10 años, contabilizando el número de habitantes en ellos, 2150, y todos los casos de cáncer detectados en los 5 últimos años, 37. Por su parte, se recolectó otra muestra aleatoria de control con edificios que no tuvieran ningún transformador eléctrico cercano, contabilizando también el número de personas, 2200, y el número de casos de cáncer en ellos en los últimos 5 años, 33. En ambas muestras, los expertos procuraron eliminar la posibilidad de ruidos, es decir, la presencia de otros factores que pudieran incidir en variar la incidencia del cáncer en alguna de las muestras.

A la luz de los datos de este estudio, ¿podemos afirmar que la cercanía de un transformador eléctrico aumenta la proporción de casos de cáncer? (Utilícese un nivel de significación del 5%

Si llamamos pct a la proporción de casos de cáncer en los edificios con transformador cercano y pst a la proporción análoga en los edificios sin transformador, nos piden que contrastemos:

$$H_0 : p_{CT} = p_{ST} \hspace{10mm} H_1 : p_{CT} > p_{ST}$$

Usaríamos los siguientes comandos:

```
tabla<-matrix(c(37,2113,33,2167),2,2,byrow=TRUE)
```

Finalmente aplicamos la función:

```
prop.test(tabla, alternative='greater', correct=FALSE)
```

```
## 
##  2-sample test for equality of proportions without continuity correction
## 
## data:  tabla
## X-squared = 0.33521, df = 1, p-value = 0.2813
## alternative hypothesis: greater
## 95 percent confidence interval:
##  -0.004071904  1.000000000
## sample estimates:
##    prop 1    prop 2 
## 0.0172093 0.0150000
```

Lo que nos interesa es el p-valor. Aparece en la tercera línea y indica que no se puede rechazar la hipótesis nula en favor de la alternativa. 

##### La función var.test() (Ejemplo 6 Manual R)

**Ejemplo 6** Un grupo de personas participa en un estudio nutricional que trata de analizar los niveles asimilados de vitamina C en sangre de fumadores y no fumadores. Los resultados en mg/l𝑚𝑔/𝑙 se encuentran en el fichero _vitaminac.txt_. Si asumimos que los datos son normales, ¿se puede concluir que el nivel de vitamina C asimilado es superior en los no fumadores?

Con el fin de responder a la pregunta, planteamos las siguientes hipótesis:
$$H_0 : \mu_F \geq \mu_{NF} \hspace{10mm} H_1 : \mu_F < \mu_{NF} $$

Observamos que el enunciado no menciona nada relativo a la igualdad de varianzas en ambos grupos, por lo que vamos a plantear en primer lugar un contraste de igualdad de varianzas. Si denotamos sigmaF a la desviación típica del nivel de vitamina C asimilado en fumadores y sigmaNF a la desviación típica del nivel de vitamina C asimilado en no fumadores, se trata de contrastar:

$$H_0 : \sigma_F = \sigma_{NF} \hspace{10mm} H_1 : \sigma_F \neq \sigma_{NF} $$
De nuevo vamos a asumir que los datos proceden de distribuciones formales. La función *var.test()* tiene una sintaxis parecida a las previas funciones:

```
var.test(x, y, ratio = 1, alternative = c("two.sided", "less", "greater"),
conf.level = 0.95)
```

- *x* corresponde al vector de datos de la primera muestra.
- *y* vector de datos de la segunda muestra. 
- *ratio* es el cociente hipotético con el que comparamos. Habitualmente deseamos contrastar que las varianzas son distintas, o lo que no es lo mismo, que su cociente es 1, la opción por defecto es precisamente *ratio = 1*.
- *alternative* especifica la hipótesis alternativa "two.sided" para H1 sigmaF != sigma NF, para sigmaF < sigmaNF y para sigmaF > sigmaNF.
- *conf.level* es el nivel de confianza del intervalo para el cociente de varianzas.

```
datos.vitaminac<-read.table("vitaminac.txt",header=TRUE,sep=" ",dec=".") 
datos.vitaminac

##    nivel      tabaco
## 1   18.3   fumadores
## 2    9.3   fumadores
## 3   12.6   fumadores
## 4   15.7   fumadores
## 5   14.2   fumadores
## 6   13.1   fumadores
## 7   14.3   fumadores
## 8   16.2   fumadores
## 9   18.1   fumadores
## 10  19.4   fumadores
## 11  15.5   fumadores
## 12  11.7   fumadores
## 13  24.9 nofumadores
## 14  16.0 nofumadores
## 15  26.3 nofumadores
## 16  25.5 nofumadores
## 17  19.3 nofumadores
## 18  16.8 nofumadores
## 19  15.7 nofumadores
## 20  24.6 nofumadores
## 21  19.9 nofumadores
## 22   9.4 nofumadores
## 23  17.4 nofumadores
```

Veamos el uso de var.test():

```
var.test(datos.vitaminac$nivel[datos.vitaminac$tabaco=="fumadores"], 
datos.vitaminac$nivel[datos.vitaminac$tabaco=="nofumadores"], alternative="two.sided") 

## 
##  F test to compare two variances
## 
## data:  datos.vitaminac$nivel[datos.vitaminac$tabaco == "fumadores"] and datos.vitaminac$nivel[datos.vitaminac$tabaco == "nofumadores"]
## F = 0.31313, num df = 11, denom df = 10, p-value = 0.06976
## alternative hypothesis: true ratio of variances is not equal to 1
## 95 percent confidence interval:
##  0.08544081 1.10400497
## sample estimates:
## ratio of variances 
##          0.3131332
```

Alternativamente podríamos haber utilizado la función de *var.test()* de la forma:

```
var.test(nivel ~ tabaco, alternative='two.sided', conf.level=.95,
data=datos.vitaminac)

## 
##  F test to compare two variances
## 
## data:  nivel by tabaco
## F = 0.31313, num df = 11, denom df = 10, p-value = 0.06976
## alternative hypothesis: true ratio of variances is not equal to 1
## 95 percent confidence interval:
##  0.08544081 1.10400497
## sample estimates:
## ratio of variances 
##          0.3131332
```

Podemos ver en la tercera línea el valor estadístico, los grados de libertad en el numerador y el denominador, sin olvidarnos del p-valor. Este indica que no hay suficientes evidencias en los datos para rechazar la igualdad de varianzas. Por tanto, a la vista de los resultados, realizaríamos el contraste de medias planteado asumiendo igualdad de varianzas.

