Este es un intento de resumir de forma adecuada los contenidos teóricos en su mayoría que pertenecen al primer examen de la materia de ML. Este examen consta de dos bloques con diversos apartados
## Bloque I
### Introducción
### Tipos de datos
Trabajaremos sobre la base: datos tabulados. Esto significa que los ejemplos a través de los cuales aprende el modelo se representan en una tabla donde cada fila es un ejemplo y cada columna es un atributo de dicho ejemplo (medido en proceso de poca importancia). Entonces decimos que hay N ejemplos y D columnas, haciendo D referencia a la dimensionalidad. 

Aunque presentamos los datos en forma de tabla numérica, cada columna puede tener un carácter diferente. Así podemos distinguir entre:
- **atributos continuos** -> pueden tomar cualquier valor en un intervalo $\mathbb{R}$    
- **atributos discretos** -> sólo pueden tomar un número finito de valores en intervalo $(a,b)$ 
- **atributos categóricos** -> pueden tomar un número finito de valores dentro de un conjunto que puede no tener relación de orden entre miembros

Hay que codificar los categóricos porque no son números. Existe una relación biyectiva significando que a cada elemento del conjunto de categorías se les puede asignar un número natural. Podemos o asignar un entero a cada elemento o usar *One-Hot* 

En *One-Hot* creamos tantas columnas como categorías diferentes haya por cada atributo categórico. Se codifica escribiendo 1 en aquella columna que se corresponde con la categoría y un 0 en las demás.
### Separar, explorar y rellenar

**Separación**
Nunca podemos usar todos los ejemplos dados para aprender la tarea. Queremos tener una máquina autónoma, que reaccione a nuevos ejemplos que le lleguen ya desplegada. Por ello, para probar el modelo, reservamos una parte del conjunto de datos para formar el **Conjunto de Test** (10-20% de los datos), el resto siendo el de **Entrenamiento**. 

NO usamos el conjunto de testeo hasta llegar al final y dárselo a la máquina para que realice la tarea.

**Exploración**
Proceso de comprender datos y relaciones entre ellos. Primero hacemos una descripción estadística básica del conjunto de ejemplos. Necesitamos generar un informe que nos trate toda la información relevante como es el tamaño del conjunto de datos, los atributos NO numéricos para convertirlos, la media y desv. estándar de cada atributo, la mediana, moda, máximo y mínimo de cada atributo. 

Estos son todos estadísticos básicos que asumen que TODOS los atributos $x_i$ con *i = 1 ... D* son numéricos. Los categóricos hay que recogerlos aparte y explicar el cambio.

**Preprocesado**
A veces es más práctico desarrollar métodos capaces de procesar y preparar los datos de forma automática, requiriendo una intervención humana casi nula. Podemos automatizar la localización y tratamiento de datos perdidos además de eliminar atributos innecesarios o seleccionar los que vamos a usar finalmente.

***Valores perdidos***
Más frecuentes de lo pensado. Hemos de averiguar su ubicación, valorar si rellenamos los huecso o eliminamos el ejemplo del atributo. A veces podemos añadir una nueva columna a la derecha de aquella donde tengamos los valores imputados, marcando celdas donde ha habido imputación.

**Imputación univariada**
Imputamos valores al resto de los NaN. La técnica más sencilla es esta: asignar un estadístico de la columna a todos los NaN que haya en ella, y repetir para cada columna. Podemos usar la media (si valores distribuidos según normal), mediana (mejor opción con valores muy extremos dentro de esa columna) o el valor más repetido (para valores categóricos)

Puede crear casos imposibles, es lo malo.

**Imputación multivariada**
Lo calculamos en función del resto de atributos. Lo hacemos usando regresión, la cual se calcula ajustando parámetros de una recta (o hiperplano si hay varias dimensiones) mediante mínimos cuadrados.
### Ingeniería de características
En ocasiones los datos tabulados no nos dan lo suficiente para realizar la tarea. En estos casos creamos nuevas columnas a partir de las hay con esperanzas de lograr mejores resultados. Un vector-características es lo que describe cada ejemplo de forma definitiva, es decir, el vector que finalmente usamos para aprender la tarea. Puede coincidir con los atributos pero también puede ser menor o mayor. Será menor si hemos eliminados atributos no útiles, mayor si hemos metido nuevas columnas calculadas a partir de las iniciales e igual si nos quedamos con los atributos dados o creamos tantas columnas como las eliminadas

**Aumento de la dimensionalidad**
Significa añadir nuevas características calculadas a partir de las que tenemos. Somos nosotros los que elegimos el modo en el que construimos las características

**Reducción de la dimensionalidad**
- **Transformaciones sin modificar dimensionalidad**
	Consideramos que las modificaciones sobre un atributo, aunque no creemos otro nuevo, es parte de la ingeniería de características.
	- Escalado al intervalo unidad -> Tenemos la siguiente fórmula $x_{esc} = \frac{x-x_{min}}{x_{max} - x_{min}}$. Hemos de hacerlo columna a columna ya que $x_i$ puede ser distinta de $x_j$ 
	- Escalado al máximo en valor absoluto -> ahora dada una columna $x$ tenemos la siguiente fórmula $x_{esc} = \frac{x}{max(|x|)}$. Esto hemos de hacerlo columna a columna nuevamente, que puede cambiar.
	- Estandarización -> Dada columna $x$ con media $\mu$ y desviación $\sigma$ entonces usamos $x_{std}=\frac{x-\mu}{\sigma}$. Estandarizar es que tiene media cero y desviación unidad. NO estamos convirtiendo la distribución de $x$ a una normal.
### Reducción filtrado
Para cada característica de la tabla de datos se calcula una puntuación (*score*) de cuanta relevancia tiene o de sus posibilidades para contribuir a realizar la tarea. En este filtrado se eliminan aquellas características cuya puntuación no supera un umbral (*threshold*) elegido por nosotros. Por esto decimos que son técnicas de selección de características. Veremos las siguientes:
- **Varianza** 
	Promedio de las diferencias con la media elevadas al cuadrado. Para una variable $x = [x_1, x_2, ..., x_N]$ con media $\mu$ la varianza de $x$ es $Var(x)=\frac{1}{N}\sum_{k=1}^N(\mu - x_k)²$. Siendo la desv. estándar la raíz cuadrada de la varianza. 
	
	Decimos que este filtrado es eliminar las columnas cuya varianza no supere un cierto umbral.
	
	Si una característica tiene una varianza pequeña significa que no aporta nada pues es casi constante en su mayoría. Por ende, hemos de fijar un umbral relativamente bajo para asegurar esta condición.
- **Correlación**
	Si dos características tienen correlación significa que entre ambas existe una relación lineal. Cuando una crece o decrece, la otra lo hace proporcionalmente. Por tanto no necesitamos ambas, basta con una de ellas ya que nos da lo mismo salvo por escala o desplazamiento.
	
	Esto sólo ocurre si la correlación entre ambas es $+1$ o $-1$. Cuanto más cerca a los extremos, mejor. Obtenemos entonces una matriz de correlación y buscamos las celdas próximas a estos valores
- **Información mutua**
	Medimos la reducción de la incertidumbre (entropía) de una variable aleatoria $X$ cuando conocemos el valor de otra $Y$. Dejamos esta técnica para más adelante.
### PCA - Principal Component Analysis
Si bien sabemos generar características en función de las que tenemos, no hay forma sistemática de hacerlo. La función más sencilla para combinar características es la **combinación lineal**. Cada característica es ponderada por un coeficiente y después las sumamos todas. Decimos entonces que PCA es una técnica para sustituir las características originales por nuevas que sean mediante combinaciones lineales de las originales. 

¿El problema? Calcular los coeficientes. 

Además, PCA es una técnica de reducción de dimensión. Por tanto es de esperar que las nuevas características que sustituyen a las originales sean en su total, menos.

**Ideas clave**
- PCA NO selecciona características, crea nuevas
- Podemos crear tantas como las que tenemos inicialmente, $D$ 
- Además, PCA las ordena en importancia de mayor a menor, para reducir la dimensión podemos empezar a eliminar de la última a la primera

**Cuestiones clave**
- ¿Cómo creamos las nuevas características?
- ¿Cómo medimos la importancia de esas nuevas características?
- Si eliminamos características, ¿cuánta información estamos perdiendo?

**Breve notación**
- $N$ y $D$ como filas y columnas
- $d$ como número de componentes principales (dimensionalidad reducida, $d \leq D$)
- $x_i^{(k)}$ como indicador de la i-ésima característica del ejemplo k-ésimo
- De forma similar, usaremos $z_j^{(k)}$ para indicar el j-ésimo componente principal del ejemplo k-ésimo.
- Los vectores son siempre vectores columna y un ejemplo aislado es un vector de características. Sin embargo, al representar un conjunto de datos como una tabla, los ejemplos son sus filas.

Al aplicar PCA reducimos el número de columnas de $D$ a $d$, las columnas son características y por tanto se representan por la letra $x$ y las columnas del conjunto reducido son componentes principales representados por $z$. 

#### Fundamento teórico de PCA

**Intuición**
Sea un vector $x \in \mathbb{R}^D$ (ejemplo con $D$ características de forma que $x = [x_1,x_2,x_3,...,x_D]$ siendo $x_1, x_2, x_3,...$ coordenadas de $x$ en base canónica)

Veamos dos imágenes que nos dan a entender un poco mejor este concepto:

![[Ejemplo 3 dimensiones PCA.png]]

Esto, al cambiar de base, tendrá unas coordenadas diferentes en la 
nueva base, digamos que ahora es $U = \{{u_1, u_2, u_3}\}$. 

![[Cambio de base PCA.png]]

Recordamos que el objetivo es REDUCIR dimensiones. Supondremos que quitamos la 3º dimensión $z_3$. Si da la casualidad que $z_3=0$ entonces $x=\hat{x}$.

Así, no hemos perdido info., hemos encontrado una manera de representar $x$ con menos dimensiones. 

Con más dimensiones lo que buscamos sería dividir los vectores en dos potenciales partes. Buscaríamos luego obtener una nueva representación con sólo *d* dimensiones. Si logramos que sea 0 en su transformación hasta $D$ desde $d+1$ genial, sino, intentaremos hacer el acercamiento. 

Tenemos que tener el siguiente residuo de reconstrucción $\hat{x}$ en cuenta:

$\epsilon = \sum_{k=d+1}^D z_k · u_k$ 

Esto es un vector formado por coordenadas de $\hat{x}$ que se quedan fuera por usar solo $d$ dimensiones. **Cuan MENOR el residuo, más parecido $\hat{x}$ al original $x$**.

*¿Qué podemos manejar para lograrlo?*
Hemos de encontrar la base $U$ que minimice el residuo. Como este es un vector, minimizamos su norma-2 al cuadrado $||\epsilon||_2² = \epsilon^T\epsilon$

Buscamos $u_k$ pero cómo obtenemos $z_k$, pues estos son la proyección del vector $x$ sobre el vector de la base $u_k$ que se calculaba con el producto escalar de ambos, $z_k = x^T u_k$. Ahora ya podemos formalizar el problema y resolver.

**Formalización**
Nuestro objetivo es minimizar el valor esperado de la norma-2 (medida de longitud o magnitud de un vector, es la raíz cuadrada de la suma de los cuadrados de sus componentes) al cuadrado del residuo. Podemos cambiar los vectores de la base $U$ para lograrlo

$$

\begin{align}

\mathop{\arg\min}\limits_{\bf U}{\mathbb E}\Vert \varepsilon \Vert_2^2 &=

\mathop{\arg\min}\limits_{\bf U}{\mathbb E}\big[\varepsilon^\top\varepsilon\big] \\ &=

\mathop{\arg\min}\limits_{\bf U}{\mathbb E}\left[\left(\sum\limits_{k=d+1}^D z_k {\bf u}_k\right)^\top\left(\sum\limits_{k=d+1}^D z_k {\bf u}_k\right)\right]\\ &=

\mathop{\arg\min}\limits_{\bf U} \sum\limits_{k=d+1}^D {\mathbb E}\left[z_k^\top z_k\right]

\end{align}

$$

Lo que hemos hecho es sabiendo que U es una base ortonomal lo que dice que $u_i T u_j=0$ cuando $i\neq j$ y en caso contrario es 1. Así como que $E[aX + b] = aE[X]$ donde $X$ es una variable aleatoria y $a, b$ son constantes.  

Luego introducimos la definición de $z_k$:
$$

\begin{align}

\mathbb E \left[ z_k^\top z_k \right] &=

\mathbb E \left[ \left( {\bf x}^\top{\bf u}_k \right)^\top \left( {\bf x}^\top{\bf u}_k \right) \right] =

\mathbb E \left[ {\bf u}_k^\top{\bf x} {\bf x}^\top{\bf u}_k \right]

= {\bf u}_k^\top \mathbb E\left[ {\bf x}{\bf x}^\top \right] {\bf u}_k

\end{align}

$$
Esto es para 1 ejemplo $x$ que se representa como un vector columna. PERO si tenemos N vectores en una tabla $X \in \mathbb{R}^{NxD}$ donde cada ejemplo es una fila, podemos hacer todos a la vez calculando $X^T X$. Pero si los datos están estandarizados entonces $E[X^TX]=\sum$ siendo $\sum$ la matriz de covarianza de los datos.

Tenemos por ende que resolver el siguiente problema de optimización:
$$

\left\lbrace

\begin{array}{l}

\mathop{\arg\min}\limits_{\bf U} \sum\limits_{k=d+1}^D {\bf u}_k^\top \Sigma {\bf u}_k \\

\text{ sujeto a } ~ {\bf u}_k^\top{\bf u}_k = 1 ;~ k=d+1,\ldots,D

\end{array}

\right.

$$
Este es el **problema de optimización de componentes principales**

**Solución**
Hemos planteado un problema de optimización cuadrática con **restricciones** (lo que queremos optimizar aparece elevado al cuadrado o en caso de matrices, multiplicado por su traspuesta y no vale cualquier solución).

Localizamos el mínimo haciendo la derivada de la función respecto de las variables objetivo. Para resolverlo, necesitamos recurrir a los multiplicadores de Lagrange, que transforman nuestra optimización cuadrática en otra sin restricciones sobre u. 

Esto nos introduce un multiplicador lambda por cada restricción-. Así, y tomando una fila cualquiera de la expresión de arriba, tenemos el planteamiento dual. Llegamos así a la base buscada. 
$$

\mathop{\arg\min}\limits_{{\bf u}_k} \left( {\bf u}_k^\top{\Sigma}{\bf u}_k\right) - \lambda_k\left( {\bf u}_{k}^\top{\bf u}_{k} - 1 \right)

~,\quad k=d+1,\ldots,D.

$$

Y por tanto

$$

\frac{\partial}{\partial{\bf u}_k} \left( {\bf u}_k^\top{\Sigma}{\bf u}_k\right) - \lambda_k\left( {\bf u}_{k}^\top{\bf u}_{k} - 1 \right) = 0,

$$

haciendo la derivada llegamos a

$$

{\Sigma}\cdot {\bf u}_{k} - \lambda_{k} \cdot {\bf u}_{k} = 0,

$$

es decir

$${{\Sigma}\cdot {\bf u}_{k} = \lambda_{k} \cdot {\bf u}_{k}}.$$
Resumen: calculando la matriz de covarianza de los datos y obteniendo sus autovalores y autovectores encontramos la base que minimiza el residuo.

**Interpretación**
Podríamos en vez de minimizar el residuo, maximizar la reconstrucción. Ambos son equivalentes.

$$

\mathop{\arg\min}\limits_{\bf U} \sum\limits_{k=d+1}^D {\bf u}_k^\top \Sigma {\bf u}_k

=

\mathop{\arg\max}\limits_{\bf U} \sum\limits_{k=1}^d {\bf u}_k^\top \Sigma {\bf u}_k

$$
Tomemos el caso extremo de $d=1$; entonces el término de la izquierda queda:
$$

\mathop{\arg\max}\limits_{{\bf u}_1} \left({\bf u}_1^\top \Sigma {\bf u}_1 \right) =

\mathop{\arg\max}\limits_{{\bf u}_1} \left({\bf u}_1^\top \lambda_1 {\bf u}_1 \right) =

\mathop{\arg\max}\limits_{{\bf u}_1} \left(\lambda_1 {\bf u}_1^\top {\bf u}_1 \right) = \lambda_1.

$$
Es decir, que si ordenamos los autovectores tal que $λ_1>λ_2>⋯>λ_D$, entonces estaremos ordenando los autovectores de manera que $u_1$ proporciona la máxima reconstrucción posible, después $u_2$, y así hasta $u_D$ que proporciona la menor.

Es importante señalar que la información que acumula cada componente principal es en realidad un porcentaje de la varianza total de los datos y que no se puede aplicar PCA sin haber estandarizado previamente la matriz de datos.
#### Datos de interés
**Matriz de covarianza**
La covarianza de dos variables aleatorias $X$ e $Y$ de las cuales tenemos población de $N$ muestras se define como $\sum_{X, Y} = E[(X-E[X])^T (Y-E[Y])]$ siempre que la población se represente como vectores columna. 

**Aplicado a nuestro problema**
- las variables aleatorias son dos atributos cualesquiera, $~x_i~$ y $~x_j~$, con $~i,j=1,2,\ldots,D$.
- el valor esperado se puede aproximar por el promedio, de tal modo que

$\mathbb E[x_i] \approx \frac{1}{N}\sum\nolimits_{k=1}^{N}x_i^{(k)}~, \forall i.$

Por tanto, si $~\mu_i~$ y $~\mu_j~$ son el promedio de la $i$-ésima y $j$-ésima características respectivamente, entonces la covarianza entre ambas es

$$

\Sigma_{i,j} = \frac{1}{N} \sum\limits_{k=1}^{N}\left( (x_i^{(k)}-\mu_i) (x_j^{(k)}-\mu_j) \right)

$$
Si las medias son cero, lo que ocurre cuando los atributos están estandarizados, entonces
$$
\Sigma_{i,j} = \frac{1}{N} \sum\limits_{k=1}^{N}\left( x_i^{(k)}\cdot x_j^{(k)} \right) = x_i^\top x_j,
$$
donde recordamos que tanto $x_i$ como $x_j$ son dos características, es decir dos columnas de la matriz $\bf X$.

**Cálculo eficiente**
En vez de calcular la covarianza de cada par de características, calculamos en un solo paso la matriz de covarianza de la tabla $~\bf X~$ completa si:
1. Estandarizamos la tabla, de manera que la media de cada columna sea 0
2. Aplicamos la siguiente fórmula
$$
\Sigma = {\bf X}^\top{\bf X}.

$$
#### Autovectores y autovalores

**Definición y significado**

Cuando multiplicamos una matriz cuadrada ${\bf A} \in \mathbb R ^{n\times n}$ por un vector ${\bf u} \in \mathbb R^n$ obtenemos otro vector del mismo tamaño que $\bf u$ pero, en general, diferente. <br>
Sin embargo hay ocasiones en que el vector obtenido es $\bf u$, pero multiplicado por un número $\lambda \in \mathbb R$ que lo hace más grande o más pequeño. <br>
Cuando ocurre esto el vector $\bf u$ se llama **autovector** y el número $\lambda$ **autovalor**. Matemáticamente se expresa:

$${\bf A}{\bf u} = \lambda{\bf u}.$$
**Propiedades**
- Una matriz cuadrada ${\bf A} \in \mathbb R ^{n\times n}$ tiene $~n~$ autovalores sólo si su determinante $|{\bf A}|\neq 0$.<br>
Si la matriz no es cuadrada o no tiene determinante distinto de cero entonces **no** tiene autovalores.

- Los autovalores no tienen por qué ser todos distintos.

- Sea ${\bf X} \in \mathbb R ^{n\times m}$ (por tanto NO cuadrada),

si $\lambda$ es autovalor de ${\bf X}^\top$

${\bf X}$ también lo es de ${\bf X}

${\bf X}^\top$  

<u>Demostración</u><br>
Sean dos matrices $~{\bf A~}$ y ${~\bf B},~$ cuadradas y del mismo tamaño; tal que ambas tienen el autovalor $\lambda$.<br>
Sea $\bf u$ el autovalor de ${\bf A~}$ asociado a $\lambda$,
y sea $\bf v$ el autovalor de ${\bf B~}$ asociado a $\lambda$; es decir:
$${\bf A}{\bf u} = \lambda{\bf u} \quad\text{y}\quad {\bf B}{\bf v} = \lambda{\bf v}$$
Si ${\bf A}={\bf X}^\top{\bf X}$ entonces
$~{\bf X}^\top{\bf X}{\bf u} = \lambda{\bf u}.$<br>
Multiplicando por la izquierda por $\bf X$ tenemos
$~{\bf X}{\bf X}^\top{\bf X}{\bf u} = {\bf X}\lambda{\bf u} = \lambda{\bf X}{\bf u}.$<br>
Si al producto ${\bf X}{\bf X}^\top$ lo llamamos $\bf B,~$ y recordando que al multiplicar una matriz por un vector "cualquiera" se obtiene otro vector entonces podemos reescribir la última exprsión como
${\bf B}{\bf v} = \lambda{\bf v}.$<br>
En definitiva, $\lambda$ es autovalor tanto de $~{\bf A}={\bf X}^\top{\bf X}~$ como de $~{\bf B}={\bf X}{\bf X}^\top$.
### Puntos, rectas, planos e hiperplanos
Geometría básica para repasar. Lo más importante es:
- Un hiperplano es una combinación lineal de variables que da como resultado 0 y que modificando su vector característico modificamos todo el hiperplano.
#### Rectas
Se define a partir de un punto que se traslada en la dirección marcada por un vector director $v$. 

Para mostrarla, necesitamos un espacio de dos o más dimensiones. 

**Ecuación implícita**$\quad$

La recta que pasa por el punto $(a,b)$ y el vector director ${\bf v} = (v_1, v_2)^\top $ son todos aquellos puntos del espacio $x=(x_1, x_2)\in\mathbb R ^2$ que satisfacen:

$$

c_0 + c_1x_1 + c_2x_2 = 0, \\\text{tal que} \left\lbrace

\begin{array}{l}

c_0=a\frac{v_2}{v_1} - b \\

c_1=-\frac{v_2}{v_1} \\

c_2=1\\

\end{array}

\right.

$$

  

**Ecuación explícita**$\quad$ Si colocamos $x_1$ en el eje horizontal y $x_2$ en el eje vertical podemos generar puntos de la recta dando valores a $x_1\in \mathbb R$ y obteniendo $x_2$ mediante la ecuación

$$

x_2 = \left(\frac{v_2}{v_1}\right)x_1 + \left(b-a\frac{v_2}{v_1}\right),

$$

que se suele ver con esta otra expresión:

$$x_2 = m x_1 + x_0,$$

donde $x_0$ es el _punto de intercepción_ de la recta con el eje vertical, o sea el valor de $x_2$ cuando $x_1=0$.

  

**Vector característico**$\quad$

Es el vector perpependicular al vector director y se define

$${\bf c} = (c_1, c_2)^\top$$
#### Planos
Lo definimos a partir de un punto que se traslada por una superficie perpendicular a un vector característico $c$ 

> En un plano **no** podemos hablar de un vector director.<br> En todo caso sería de dos vectores generadores $~{\bf u}_1~$ y $~{\bf u}_2~$ tal que $~{\bf c} = {\bf u_1}\wedge {\bf u_2},~$ donde $\wedge$ es el producto vectorial.

Para mostrar una plano necesitamos un espacio de dimension $D\ge 3$.

**Ecuación implícita**$\quad$

La plano que pasa por el punto $(p,q,r)$ y tiene vector característico ${\bf c} = (c_1, c_2, c_3)^\top $ son todos aquellos puntos del espacio $x=(x_1, x_2, x_3)\in\mathbb R ^2$ que satisfacen:

$$

c_0 + c_1x_1 + c_2x_2 + c_3x_3= 0, \\\text{tal que }

\begin{array}{l}

c_0=-\big(pc_1 + qc_2 + rc_3\big)\\

\end{array}

$$

Es frecuente simplificar eligiendo directamente el valor del **término independiente** $~c_0.~$

**Ecuación explícita**$\quad$ Si colocamos $x_1$ en un eje horizontal y $x_2$ en el otro eje horizontal podemos generar puntos del plano dando pares $(x_1, x_2)\in \mathbb R^2$ y obteniendo $x_3$ en el eje vertical simplemente despejandolo
$$

x_3 = \left(-\frac{c_1}{c_3}\right)x_1

+ \left(-\frac{c_2}{c_3}\right)x_2

+ \left(-\frac{c_0}{c_3}\right)

$$
A partir de esta ecuación es fácil obtener el punto de intercepción del plano con el eje vertical. <br>Basta con hacer $~x_1=x_2=0.$
#### Hiperplano
Generalización a $D$ dimensiones de un plano. Viene definido por un vector característico $c = (c_1,...,c_D)^T$ y un término independiente $c_0$ con ecuación implícita:

$c_0+c_1x_1+...+c_Dx_D=0$ 

esto se suele simplificar usando el producto escalar del vector característico por un vector de variables $x=(x_1,...,x_D)^T$ es decir:
$c_0+c^Tx=0$

no se puede representar en pantalla. esta ecuación implícita y de los otros elementos vistos de dimensión menor, es la combi. lineal de las variables, donde los coeficientes son precisamente el vector característico. Los puntos del hiperplano son aquellos que satisfacen la ecuación, es decir, que al evaluarlos dan 0.

A veces se añade un término independiente como variable *dummy* para eliminarlo de la expresión. Es una variable fija a 1 que se añade al vector de variables, quedando la ecuación implícita del hiperplano como $c^Tx = 0$ lo que simplifica las cosas
## Bloque II
### Modelos lineales
Existen dos grandes problemas de aprendizaje supervisado:
- Regresión -> Aprender a emparejar los ejemplos dados con un *target* (valor objetivo) que toma valores en un intervalo continuo.
- Clasificación -> Emparejar los ejemplos dados con un número discreto, denominado *label* (etiqueta o clase también). A veces la clase toma valores dentro de un conjunto de categorías. Ahí o bien codificamos con enteros o por *one-hot*. Si sólo hay dos clases el problema es binario o de clasificación binaria, más es multi-clase
realmente son el mismo, regresión es clasificación con infinitas clases.

En ambos casos siempre tendremos un conjunto de datos de N ejemplos D dimensionales tal que cada ejemplo esté emparejado con su valor objetivo y un modelo para aprender cada ejemplo con su valor objetivo (regresión) o su etiqueta (clasificación)

Buscamos **estimar** con mayor tasa de acierto posible el target o el label de los ejemplos nuevos.

Entendemos modelo como parte de un sistema más grande que aprenderemos a construir posteriormente. 

**Modelo general para AS**
Llamaremos modelo a la función paramétrica $f(x; w)$ que:
- recibe un ejemplo $x \in \mathbb{R}^D$
- produce una salida, ya sea un vector $\textbf{y}$ o un escalar $y$ dependiendo del problema
- el vector **w** es el conjunto de parámetros que podemos modificar para transformar la entrada **x** en la salida **y**

**Modelo lineal**
Aquel en que la salida del modelo es una combinación lineal de la entrada y los parámetros. 

Es decir:
$f(w; x)=w_0+w_1x_1+...+w_Dx_D$

Hay una relación evidente entre modelo lineal y hiperplano. Dado un modelo lineal, existe un hiperplano cuyo vector característico $w=(w_1,...,w_D)^T$ y término independiente $w_0$ tal que $w_0+w^Tx = 0$ 

**Modelo lineal de regresión**
$\hat{y} = w_0+w^T x$ 

donde $\hat{y}$ es la estimación que hace el modelo para el ejemplo **x** dado los parámetros escogidos. 

El modelo lineal de regresión es lo que obtenemos al ajustar por mínimos cuadrados un conjunto de pares de puntos generalizado a mínimo 2 dimensiones.

Aprender significa encontrar los parámetros óptimos o los mejores posibles. Un primer modo es a través de un cálculo matricial

$$

{\bf X} =

\left[

\begin{matrix}

1 & x_1^{(1)} & x_2^{(1)} & \ldots & x_D^{(1)} \\

1 & x_1^{(2)} & x_2^{(2)} & \ldots & x_D^{(2)} \\

\vdots & \vdots & \vdots & \ddots & \vdots \\

1 & x_1^{(N)} & x_2^{(N)} & \ldots & x_D^{(N)} \\

\end{matrix}

\right]

\quad

{,}

\quad

{\bf Y} =

\left[

\begin{matrix}

y_1 \\ y_2 \\ \vdots \\ y_N

\end{matrix}

\right]

{,}

\quad

{\bf w} =

\left[

\begin{matrix}

w_0 \\ w_1 \\ w_2 \\ \vdots \\ w_D

\end{matrix}

\right]

$$
El modelo lineal para el conjunto de entrenamiento $\{{\bf X}, {\bf Y}\}$ queda entonces:
$$

\begin{align}

{\bf Y} &= {\bf X}{\bf w}~, \\

{\bf X}^\top{\bf Y} &= {\bf X}^\top{\bf X}{\bf w}~,\\

\big({\bf X}^\top{\bf X}\big)^{-1}{\bf X}^\top{\bf Y} &= \big({\bf X}^\top{\bf X}\big)^{-1}{\bf X}^\top{\bf X}{\bf w}~,\\

\big({\bf X}^\top{\bf X}\big)^{-1}{\bf X}^\top{\bf Y} &= \mathbb{I}{\bf w}~,\\

\end{align}

$$

donde $\mathbb{I}$ es la matriz identidad. Por tanto el vector óptimo de parámetros es
$$

{\bf w}^* = \big({\bf X}^\top{\bf X}\big)^{-1}{\bf X}^\top{\bf Y}

$$

Este método es costoso computacionalmente si X es muy grande, vamos a usar el **descenso de gradiente** para optimizar esto. 

**Modelo lineal de clasificación binaria**

$\hat{y} = Signo(w_0 + w^T x)$

Este modelo asume que tenemos dos clases etiquetadas como {+, -}

De nuevo $\hat{y}$ representa la estimación que hace el modelo. Pero cuando se trata de clasificación binaria aparecen dos términos importantes nuevos:
- superficie de decisión -> puntos de $\mathbb{R}^D$ que satisfacen la igualdad $w_0+w^T x = 0$ están exactamente sobre el hiperplano; no tienen signo positivo ni negativo. Por tanto, se sitúan exactamente sobre la frontera entre dos clases. Será un hiperplano sólo si el modelo es lineal
- función discriminante -> usamos la función *Signo* para estimar la etiqueta, discriminando a qué clase pertenece el ejemplo dado. Usarla NO es obligatorio. Se usa una función discriminante que transforme el resultado de $f(w;x)$ (lineal o no) en la etiqueta estimada.

<u>Ejemplo</u>
Función _Umbral_
$$

\hat y = \left\lbrace

\begin{array}{lll}

0 & \text{si} & f({\bf x};{\bf w}) > \theta \\

1 & \text{si} & f({\bf x};{\bf w}) \le \theta

\end{array}

\right.

$$
- La etiqueta puede ser {0, 1}.
- La función discriminante consiste en superar el umbral $\theta$.

Aplicamos la misma fórmula para aprender que en regresión, la superficie de decisión será el hiperplano que se forma con los parámetros óptimos para luego aplicar la función discriminante.
### Regresión logística
Necesitaremos la función sigmoide (gráfica que tiene forma de S). Cumple:
- $S : \mathbb{R} \rightarrow (a,b)$ con $a < b$ o sea, real y acotada
- Diferenciable con derivada no negativa en cada punto y 1 punto de inflexión, siempre crece. 

La que usaremos es la logística que es la siguiente: $S(x)=\frac{1}{1+e^{-x}}$ donde $x$ hace referencia a la entrada de la función, no a un ejemplo del conjunto de datos. 

Esta función tiene las siguientes propiedades:
- Continua y siempre creciente
- En sus límites de infinito (negativo y positivo) tiende a 0 y 1 (respectivamente)

Cumple las condiciones para ser una distribución de probabilidad.

un ejemplo $~\bf x = (1, x_1, \ldots, x_D)^\top$ evaluado en el hiperplano que representa el modelo $f({\bf w},{\bf x}) = {\bf w}^\top{\bf x}~~$ puede dar tres resultados:

$\quad f({\bf w},{\bf x})=0$, entonces el ejemplo $\bf x$ está **exactamente sobre** el hiperplano de decisión.
$$\left.\begin{matrix}
\quad f({\bf w},{\bf x})>0\\
\quad f({\bf w},{\bf x})<0
\end{matrix}\right\rbrace
$$

Entonces el ejemplo está **separado** del hiperplano de decisión, por un lado o por el otro.

En este último caso, dependiendo del ejemplo, la separacíón puede ser pequeña o grande. No hay límites.

PERO lo que buscamos es asignar una etiqueta a cada ejemplo, no saber a qué distancia se encuentra del plano de decisión. 

Esta claro que si está muy lejos es lo mismo que si esta muy-muy-muy lejos.<br>
Por tanto podríamos pensar en **saturar** el valor de $ f({\bf w},{\bf x})$ de modo que por encima de esa saturación valga siempre lo mismo.

La función sigmoide se encarga de hacer esta saturación de $ f({\bf w},{\bf x})$, convirtiendolo a una medida de la probabilidad de que el ejemplo pertenezca a una de las dos clases.

Sea **Logit** el nombre que recibe el resultado de la función lineal $f(w,x)=w^Tx$ 

Entonces, la función logística aplicada al logit nos devuelve una medida de la probabilidad de que $\bf x$ pertenezca a la clase "$+1$", más exactamente:
$$

\Pr(y=+1|\text{logit}={\bf w}^\top{\bf x}) =

\frac{1}{1+e^{-{\bf w}^\top{\bf x}}}

$$
El aprendizaje es igual ya que son los parámetros de un modelo lineal. Simplemente hemos de transformar el resultado mediante la función logística.
#### Datos importantes
- La regresión logística es un modelo lineal generalizado ya que calculamos los logits mediante un modelo lineal
- También tiene una función discriminante
	$$
	
	\hat y = \left\lbrace
	
	\begin{array}{llll}
	
	+1 & \text{si} & \hat p > \theta \\
	
	-1 & \text{si} & \hat p \le \theta
	
	\end{array}
	
	\right.
	
	\quad\text{donde}\quad
	
	\hat p = \frac{1}{1+e^{-{\bf w}^\top{\bf x}}}
	
	$$
	con $\theta = 0.5$.
### Evaluación modelos
Hemos de analizar la calidad de ellos. La métrica típica en regresión es el valor R² 
$$R^2(y, \hat{y}) = 1 - \frac{\sum_{i=1}^{N} (y^{(i)} - \hat{y}^{(i)})^2}{\sum_{i=1}^{N} (y^{(i)} - \bar{y})^2}$$
donde $\hat{y}$ es la media de los valores de y. A la diferencia de ys se le llama **residuo**. Con esto comparamos el cuadrado de los residuos con la dispersión de los targets respecto de su media. R² = 1 sólo si todos los residuos son 0. Cuanto más cercano a 1, mejor el modelo.

**Calidad de los modelos**
Si hay que predecir entre dos clases podemos acertar de dos maneras y fallar de dos también:
- Aciertos: 
	- **Verdadero positivo**
		- $\hat{y} = + \space , \space y = +$ Estimación positivo y clase positiva
	- **Verdadero negativo**
		- $\hat{y} = - \space , \space y = -$ Estimación negativo y clase negativa
- Fallos:
	- **Falso positivo**
		- $\hat{y} = + \space , \space y = -$ Estimación positivo y clase negativa
	- **Falso negativo**
		- $\hat{y} = - \space , \space y = +$ Estimación negativo y clase positiva
Reunimos estos casos en lo conocido como **matriz de confusión**

De esta matriz derivamos diferentes medidas:
- **Precision** significa que todos los ejemplos estimados como positivos efectivamente lo eran
- **Recall** todos los ejemplos positivos han sido estimados correctamente
- **F1-score** da media entre *Precision* y *Recall*
- **Accuracy** porcentaje total de aciertos

**Curva ROC y AUROC**
Dado un modelo que estima la probabilidad $p(y = 1|x)$ tal que $\hat{y}=1$ si $p(y=1|x)>0$; la curva ROC es el trazado de pares cuando hacemos variar el umbral 0 < $\theta$ < 1

Es diferente la ROC a la matriz de confusión porque la calculamos para todo el rango de posibles umbrales $\theta$, mientras que la matriz de confusión ya asume un $\theta$ fijado. 

Si elegimos el umbral que da lugar al par (FPR, TPR) más cercano al punto (0, 1) estaremos tomando un buen compromiso de rendimiento.

Por otro lado, midiendo el área bajo la curva ROC podemos comparar modelos, cuanto **mayor** sea **AUROC**, **mejor** es el **modelo**
### Función de pérdida
Hay que recordar que un problema supervisado es aquel donde cada ejemplo está emparejado a una etiqueta o clase (clasificación) o con un valor objetivo o target (regresión)

Tenemos a nuestra disposición:
- conjunto de datos X en forma de tabla N x D
- conjunto Y de valores objetivos o etiquetas:
	- regresión: vector columna de N elementos en el primer caso
	- clasificación: vector columna o matriz si se usa *one-hot*. A este conjunto se le denomina por su término en inglés, *ground-truth*. 

Se supone que tenemos un modelo también, la función paramétrica $f(x;w)$

¿Por qué unos parámetros son mejores que otros?

El objetivo es predicir con la mayor tasa de acierto posible, el valor objetivo o la etiqueta de los ejemplos que reciba. Cuando pertenecen al conjunto de entrenamiento conocemos el valor objetivo o la etiqueta real de cada ejemplo. La **función de pérdida** devuelve una medida relacionada con los fallos cometidos por el modelo respecto al *ground truth*. 

Sea $~\mathcal L \big( {\bf Y}, f({\bf X};{\bf w}) \big)$ esa función

**Expresión general**
Cuantos menos fallos, mejor es el modelo. Por tanto, el problema de AS es el siguiente problema de optimización:
$$w*=arg_w min~\mathcal L \big( {\bf Y}, f({\bf X};{\bf w}) \big)$$
Necesitamos para realizar una tarea supervisada:
- un **conjunto de datos etiquetado** dado por el "cliente"
- un **modelo** y una **función de pérdida** que es decisión nuestra

Viendo sólo modelos lineales por ahora tenemos que $f(x; w) = w^Tx$ (asumiendo una característica dummy). Veamos las posibles funciones de pérdida

**FP para regresión**
En estos casos $f(x; w) : (\mathbb{R}^D, \mathbb{R}^D) \rightarrow \mathbb{R}$ y el valor objetivo $y \in \mathbb{R}$

Por tanto una función de pérdida para regresión debe tener las siguientes características:
- Calcular $\delta_{(i)} = \left(y^{(i)} - f({\bf x}^{(i)},{\bf w}) \right)$ para cada $i = 1,2,\ldots,N.$
- Convertir $\delta_{(i)}$ en un valor positivo para todo $i$.
- Hacer el promedio para todos los ejemplos.

Algunas funciones de pérdida con estas características son:

**MSE** (_Mean Squared Error_)
$$

\mathcal L \big( {\bf Y}, f({\bf X};{\bf w}) \big)

=\frac{1}{N}\sum\limits_{i=1}^{N}\left(y^{(i)} - f({\bf x}^{(i)},{\bf w})\right)^2

$$
**MAE** (_Mean Absolute Error_)
$$

\mathcal L \big( {\bf Y}, f({\bf X};{\bf w}) \big)

=\frac{1}{N}\sum\limits_{i=1}^{N}\left\vert y^{(i)} - f({\bf x}^{(i)},{\bf w})\right\vert

$$
**Log-cosh**
$$

\mathcal L \big( {\bf Y}, f({\bf X};{\bf w}) \big)

=\frac{1}{N}\sum\limits_{i=1}^{N} \log\left(\cosh\big( y^{(i)} - f({\bf x}^{(i)})\big)\right)

$$

**FP para clasificación**
A diferencia de regresión, la clasificación puede tener varias formas:
1. Clasificación binaria:
	*un ejemplo puede pertenecer a 2 clases excluyentes*
2. Clasificación multi-clase
	*un ejemplo puede pertenecer a varias clases pero excluyentes*
3. Clasificación multi-etiqueta
	*un ejemplo puede pertenecer a una o varias clases al mismo tiempo*
Los tres casos se pueden abordar como un problema de regresión y después usar una función discriminante. PERO la regresión logística es un modo mucho más natural de abordar la clasificación porque incorpora una medida de la probabilidad de pertenecer a una cierta clase. 

Cuando trabajamos con probabilidades las pérdidas citadas arriba NO son apropiadas. Veremos un cuaderno para esto solo
### Descenso de gradiente
#### Qué es
Vector que marca la dirección de máxima pendiente de una función en un punto dado.

Sea $\mathcal L(w):\mathbb{R}^D \rightarrow \mathbb{R}$ entonces el gradiente de $\mathcal L$ respecto de **w** es el vector:
$$

\nabla_w \mathcal L = \left[

\frac{\partial \mathcal L}{\partial w_1},~

\frac{\partial \mathcal L}{\partial w_2},~

\cdots,~

\frac{\partial \mathcal L}{\partial w_D}

\right]

$$
Decimos que $\mathcal L(w)$ es una superficie en un espacio D-dimensional. En esto, según viajamos por $\mathbb{R}^D$ vamos obteniendo valores de $\mathcal L(w)$. Subiendo o bajando, a veces ni uno de estos.

El gradiente en un punto concreto w nos indica la dirección en la que moverse para subir más rápido que en ninguna otra dirección. 

Para haber un gradiente debe de ser la función $\mathcal L$ derivable en todas las direcciones

**Algoritmo del descenso**
Es un algoritmo para localizar el mínimo de una función de manera iterativa.

Nos desplazamos por w en la dirección que marca $\mathcal L$. Comenzamos en un punto aleatorio y el desplazamiento produce un nuevo punto. Esto se repite, tomando como punto de partida el punto alcanzado en la iteración anterior, hasta que se cumple una condición de parada.
- **Regla de actualización**
	- Sacamos el siguiente punto descendiendo por el gradiente tal que $w^{nuevo}=w^{actual}-\eta · \cdot\nabla_{\bf w}{\mathcal L({\bf w}^\text{actual})}$  donde $\eta \in (0,1)$ es el ratio de aprendizaje 
- **Ratio de aprendizaje** 
	- En vez de usar el valor del gradiente evaluado en el punto se usa sólo el $\eta$ porcentaje. Se empieza probando en 0.1 de normal  
- **Condición de parada**
	- Se detiene si ocurre uno de los dos casos:
		- iteraciones alcanzan tope
		- $\mathcal L$ ya no decrece más
### Aplicando descenso de gradiente
Recordando las expresiones importantes:
$$

\begin{align}

\text{Problema de optimización} &:\quad

{\bf w}^* =

\mathop{\arg\min}\limits_{{\bf w}}

~\mathcal L \big( {\bf Y}, f({\bf X};{\bf w}) \big) \\

\text{Regla de actualización} &:\quad

{\bf w}^\text{nuevo} = {\bf w}^\text{actual} - \eta\cdot\nabla_{\bf w}{\mathcal L({\bf w}^\text{actual})}

\end{align}

$$
Vamos primero a calcular el gradiente de la pérdida. $$

\begin{align}

\nabla_{\bf w}\mathcal L &=

\left[ \frac{\partial \mathcal L}{\partial w_i}

\right]_{i=1,\ldots,D}

\end{align}

$$
Para calcular la derivada parcial de la pérdida respecto del parámetro $i$-ésimo vamos a reescribir la pérdida del siguiente modo:
$$

\mathcal L =

\frac{1}{N}\sum\limits_{k=1}^N \delta_{(k)}^2,

$$
con

$$\delta_{(k)} = y^{(k)} - f({\bf x}^{(k)},{\bf w}),$$

y con

$$

f({\bf x}^{(k)},{\bf w}) = x_1^{(k)}w_1 + x_2^{(k)}w_2 + \cdots + x_D^{(k)}w_D.

$$
Así podemos aplicar la regla de la cadena de la derivada, de modo que para el ejemplo $k$-ésimo tenemos:
$$

\frac{\partial \mathcal L}{\partial w_i} =

\frac{\partial \mathcal L}{\partial \delta_{(k)}}\cdot

\frac{\partial \delta_{(k)}}{\partial f}\cdot

\frac{\partial \mathcal f}{\partial w_i}

$$
Estos 3 términos son:

$$

\begin{array}{llllll}

\frac{\partial \mathcal L}{\partial \delta_{(k)}} &= \frac{1}{N}2\delta_{(k)} &,&

\frac{\partial \delta^{(k)}}{\partial f} &= -1 &,&

\frac{\partial \mathcal f}{\partial w_i} &= x_i^{(k)} \\

\end{array}

$$
Juntando todo y recordando que tenemos el sumatorio de $N$ términos $\delta^2$:
$$

\frac{\partial \mathcal L}{\partial w_i} =

\frac{1}{N}\sum\limits_{k=1}^{N}

2\delta_{(k)}(-1)x_i^{(k)} =

\frac{2}{N}\sum\limits_{k=1}^{N}

\left( f({\bf x}^{(k)},{\bf w}) - y^{(k)} \right)\left( x_i^{(k)} \right),

$$

que para el caso de modelos lineales es
$$

\frac{\partial \mathcal L}{\partial w_i} =

\frac{2}{N}\sum\limits_{k=1}^{N}

\left( {\bf w}^\top{\bf x}^{(k)} - y^{(k)} \right)\left( x_i^{(k)} \right)

$$
Una vez conocida la expresión del gradiente en todo punto, sólo hay que usarla en la regla de actualización del descenso de gradiente.
### Regularización
La función de pérdida se ve tal que:
$$\mathcal L(Y, f(X;w))$$
tal que Y es *ground truth*, X es el conjunto de datos de entreno, después de ser preprocesado y lo otro es el modelo paramétrico siendo w el conjunto de parámetros. 

La regla es que los parámetros elegidos minimicen la función. La regularización busca añadir más reglas. Sólo podemos imponer reglas sobre los pesos. Se termina convirtiendo la función en lo siguiente:
$$\mathcal L(Y, f(X;w)) + \mathcal R(w)$$
Hay 3 métodos:
- Lasso
- Ridge
- Elastic Net
#### Lasso
Añadimos el término $$\mathcal R_L=\alpha\sum_{i=1}^D|w_i|$$
a la función de pérdida donde alpha mayor o igual a cero es un valor elegido por nosotros para controlar el efecto. 
- $\alpha \rightarrow 0$ Obtenemos el mismo w* que con la regresión lineal, desaparece el término de regularización
- $\alpha > 0$ algunos parámetros tenderán a ir hacia 0
- $\alpha \rightarrow \infty$  todos los parámetros se anulan

El efecto de este regulador es **lograr que haya menos parámetros** porque muchos tenderán a 0. También se le llama a esta regularización L1 por la norma-1 
#### Ridge
Añadimos:
$$\mathcal R_R=\frac{\alpha}{2}\sum_{i=1}^D(w_i)²$$
nuevamente:
- $\alpha \rightarrow 0$ Obtenemos el mismo w* que con la regresión lineal, desaparece el término de regularización al igual que con Lasso
- $\alpha > 0$ impide que los parámetros se separen mucho o que alguno crezca demasiado
- $\alpha \rightarrow \infty$  todos los parámetros se anulan igual que con Lasso
Quitando los casos extremos nuevamente, buscamos **lograr que todos los parámetros tengan valores pequeños pero no necesariamente nulos**

También se le llama Regularización L2 por la norma-2. El factor 1/2 se añade para que al derivar el término el exponente se cancele con él
#### Elastic Net
Combinación lineal de ambos:
$$\mathcal R_E = \alpha_1\mathcal R_L + \alpha_2\mathcal R_R = \alpha_1||w||_1+\frac{\alpha_2}{2}||w||²_2$$ Esto causa una doble reducción de los parámetros, la de Lasso y la de Ridge. Para tener más control y además mejor interpretación de las alphas, se usa una combi. lineal convexa de ambos términos. Es decir:
$$\mathcal R_E=\alpha(r·\mathcal R_L + (1-r)·\mathcal R_R)$$
siendo r el porcentaje o ratio de regularización Lasso que aplicamos y por tanto el complementario es el de regularización Ridge, siendo $\alpha$ un multiplicador para dar más o menos peso al término.
#### Hiperparámetros
Aparece con los términos de regularización. Mientras que los parámetros se usan para ajustar un modelo a un conjunto de datos supervisado, los hiperparámetros son los elementos que se han añadido al modelo o al algoritmo para controlar la ejecución.

<u>Ejemplos</u>
>- En la regla de actualización de parámetros mediante descenso del gradiente aparecía el _learning rate_ $\eta$, que controlaba la velocidad a la que viajamos por el espacio de parámetros.
>- En los términos de regularización aparece $\alpha$ para dar más o menos peso al regularizador
>- En la regularización Elastic Net aparece $r$ para dar más o menos porcentaje a Lasso.

