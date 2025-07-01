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
## Separar, explorar y rellenar

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