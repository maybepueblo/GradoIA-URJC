**TEMA 4 - VARIABLES ALEATORIAS**

> [!NOTE] **Variable aleatoria**
> Función que va desde el espacio muestral que tenemos hasta R. Podemos decir que a cada suceso e del espacio muestral E, le atribuimos un único número real.
> 
> **Observación** -> Que sea una variable aleatoria no significa que los valores que toma son aleatorios, puesto que están definidos de forma precisa. Que sea aleatoria significa que la aplicamos a sucesos aleatorios.

Distribución de una variable aleatoria -> Definir la distribución consiste en especificar los posibles valores de la variable (es decir, el dominio que recorre la variable) con sus probabilidades respectivas.

Podemos clasificar las variables aleatorias dentro de dos grupos:

- **Variable Aleatoria Discreta** -> Dominio discreto
- **Variable Aleatoria Continua** -> Dominio continuo

#### Variables Aleatorias Discretas Desconocidas - VADD

Debemos primero especificar el dominio, lo haremos a través de la función de masa de probabilidad, denotada por *f*. Esta función nos da la probabilidad de que dicha variable tome ese valor xi. 

Se deben cumplir dos cosas:

- Cada valor oscile entre 0 e 1, pues es una probabilidad.
- El sumatorio de todos los elementos ha de ser igual a 1.

La variable tiene que ser un conjunto numerable, no finito, pero ha de poder enumerarse en todo momento.

> [!NOTE] Función de distribución
> Es la acumulación de la función de masa hasta cierto valor. Dada una variable aleatoria cualquiera, podemos hallar esta función. La denotamos como *F* y define la probabilidad de que la variable tome valores iguales o menores a un valor cualquiera.
> 
> Esta función siempre viene dada por intervalos y los límites de esos intervalos son los valores del dominio de la variable aleatoria, y en cada intervalo, se tomará un valor constante.

**Momentos de una variable aleatoria**

- **Esperanza o media de la variable aleatoria** -> E(X) 
$$
	 E(X) = \mu = \sum xif(xi)
$$
- **Varianza** -> Var(X) 

$$
	Var(X) = \sigma ^2 = \sum xi^2 f(xi) - \mu ^2
$$
- **Desviación típica**
$$
	sd(X) = \sigma = \sqrt(Var(X))
$$

**Formas alternativas de cálculo de medidas de una variable aleatoria**

Existe una serie de cálculos alternativos que facilitan los cálculos a posteriori de todos nuestros cálculos, veámoslo. 

En el caso de la varianza, podemos hacer lo siguiente:

1. Primero, hemos de calcular la esperanza de la variable aleatoria X al cuadrado

$$
	E(X^2) = \sum xi^2 f(xi)
$$

2. Luego, la varianza se nos vuelve este cálculo tan simple

$$
	Var(X) = E(X^2) - E(X)^2 
$$

Nótese que esto no nos exime de calcular la esperanza normal, sólo optimizamos el cálculo de la varianza, pero es suficiente

#### Variables Aleatorias Discretas Conocidas - VADC

- **Distribución de Bernoulli**
	- **Experimento** Ver si cierto suceso ocurre o no, siendo *p* el éxito y *q = (1 - p)* el fracaso. No significa que p sea positivo y q negativo. Han de sumar 1.
	- Podemos definir el experimento mediante una v.a. discreta X tal que:
		- X = 1 si el suceso ocurre
		- X = 0 si no
	- Decimos así que X ~ Bernoulli(p) si y solo si
	- **Función de masa de probabilidad** -> f(1) = p, f(0) = 1 - p
	- **Media y varianza**
		- E(X) = p
		- Var(X) = p·q
- **Distribución Binomial**
	- Misma situación que Bernoulli pero el experimento se repite n veces
	- Definimos la variable X como el número de éxitos obtenidos en esas n pruebas
	- Decimos entonces X sigue una distribución binomial X ~ B (n, p)
	- **Media y varianza** -> E(X) = np , Var(X) = np(1-p)
	- **Función de masa de probabilidad**
$$
		P (X = x) = \begin{vmatrix} n \\ x \end{vmatrix} p^x (1-p)^{n-x}
$$
- **Distribución Geométrica**
	- Consideramos repeticiones independientes. El número es indefinido pero lo que buscamos es el instante donde se produzca el primer éxito. Así, definimos la variable discreta X = instante en que observamos el primer éxito. Así, decimos que X sigue una distribución geométrica de parámetro p
		- X ~ G(p)
	- **Función de masa** -> P (X = x) = p (1 - p)^x-1, esto se debe a que la probabilidad ya que si la posibilidad de éxito se observa en la posición x, hemos tenido previamente x-1 fracasos.
	- *Observación* Se dice que la geométrica no tiene memoria, es decir que podríamos poner el contador a 0. Si sabemos que ha sido necesario más de x1 intentos para el primer éxito, y nos planteamos la probabilidad de x2, podríamos calcularlo con la probabilidad x2 - x1 casos
	- **Media y varianza** -> E(X) = 1/p , Var(X) = 1 / p^2 
- **Distribución Poisson**
	- X = número de sucesos o ocurrencias observados en un intervalo dado
	- La tasa de ocurrencias es conocida y proporcional a la longitud del intervalo, la llamamos lambda.
	- X ~ Po(lambda) donde lambda es el número medio de ocurrencias del suceso en dicho intervalo
	- **Media y varianza** -> E(X) = lambda , Var(X) = lambda
	- **Función de masa de probabilidad** 
$$
		P (X = x) = e^{-\lambda}\frac{\lambda ^x}{x!}
$$
**OBSERVACIÓN**

Podemos ver la Poisson como límite de la Binomial cuando n tiende a infinito, p tiende a cero, pero np se estabiliza. Así, definimos np = lambda.

#### Variables Aleatorias Continuas Desconocidas - VACD

Toda variable aleatoria continua tiene lo que conocemos como función de densidad. Dada una variable continua X, su función de densidad

$$
	f (x) > 0
$$
$$
	\int_{-\infty}^{\infty} f(x) dx = 1
$$
$$
	Dados a < b, P (a \leq X \leq b) = \int_b^a f(x) dx
$$
Hemos de recordar de que la probabilidad de un punto es nula y que ciertas probabilidades son equivalentes.

Veamos un ejemplo, ya que esto es un poco más abstracto y complejo que el resto del temario. 

$$
f(x) = \begin{cases} 0 & \text{si } x \leq 0 \\ kxe^{-4x^2} & \text{si } x > 0
\end{cases}
$$

Primero, para que f(x) sea una función de densidad, debe satisfacer las condiciones estipuladas anteriormente, por tanto, es lo que tenemos que calcular. Resumido: queremos hallar *k* para que se cumpla que *f(x)* es una función de densidad. 

Sabiendo que f(x) es mayor o igual que cero podemos decir que k es positiva. Asimismo, usando que la integral en toda la recta es igual a 1, si integramos obtenemos que k es exactamente igual a 8. Esto podemos hacerlo en R, veámoslo:

```
# Definimos una función cuya densidad depende de k y por tanto debe de ser de dos variables
f_x = function(x, k) {k * x * exp(-4 * x^2)}

# Usamos integrate para integrar con respecto a x, especificando los límites, esto nos permite obtener el resultado de la integral como una función de k
f1 = function(k) { integrate(f_x, 0, Inf, k = k)$value - 1}

# Uniroot nos deja obtener el valor de k que hace que la función integre a uno
(k <- uniroot(f1, interval = c(0, 10))$root)
```

**Función de distribución** Se define como la probabilidad acumulada hasta un valor x. La denominamos como *F(x)*, se calcula como:

$$
	F(x) = P (X \leq x) = \int_{-\infty}^x f(t) dt
$$
Veamos un ejemplo nuevamente:

$$
f(x) = \begin{cases} 1/5 & \text{si } x \in [0, 5] \\ 0 & \text{resto} \end{cases}
$$
Solución:

- Si x < 0
$$
F(x) = \int_{-\infty}^x f(t) dt = \int_{-\infty}^x 0 dt = 0
$$
- Si x pertenece a [0, 5]
$$
F(x) = \int_{-\infty}^x f(t) dt = \int_{-\infty}^0 0 dt + \int_0^x \frac{1}{5} dt = \frac{1}{5}x
$$
- Si x > 5
$$
F(x) = \int_{-\infty}^x f(t)dt = \int_{-\infty}^0 0 dt + \int_0^5 \frac{1}{5}dt + \int_0^x 0 dt = 1
$$
Así, la función de distribución resulta en lo siguiente:

$$
F(x) = \begin{cases} 0 & \text{si } x < 0 \\ \frac{x}{5} & \text{si } 0 \leq x \leq 5 \\ 1 & \text{si } x > 5 \end{cases}
$$
Veamos otro ejercicio y luego su implementación en R. Dada una función de densidad:
$$
f(x) = \begin{cases} 2e^{-2x} & \text{si } x > 0 \\ 0 & \text{resto} \end{cases}
$$
Calcular la probabilidad de que X esté entre 1 y 3:
$$
P(1 < X \leq 3) = \int_1^3 2e^{-2x} dx = [-e^{-2x}]^3_1 = e^{-2} - e^{-6} = 0.133
$$
Calcular la probabilidad de que X sea mayor que 0.5
$$
P (X \geq 0.5) = \int_{0.5}^\infty 2e^{-2x} dx = [-e^{-2x}]^\infty_{0.5} = e^{-1} = 0.368
$$
Veamos como se hace esto en R:
```
# Definimos nuestra función
f_X = function(x) {2 * exp(-2*x)} 

# Integramos imponiendo nuestros límites pedidos
integrate(f_x, lower=1, upper=3)

# Volvemos a hacerlo, esta vez con los nuevos límites
integrate(f_x, lower=0.5, upper=Inf)
```

En el caso de las variables continuas, las medidas son las siguientes: 

$$
E(X) = \int_{-\infty}^\infty xf(x) dx
$$
$$
Var(X) = \sigma^2 = \int_{-\infty}^\infty x^2f(x)dx  - \mu^2
$$
$$
\sigma = \sqrt{Var(X)}
$$
Imaginemos el siguiente caso, donde queremos calcular la esperanza y la varianza de la variable aleatoria del ejercicio anterior, veamos cómo se haría esto en R.

```
xf_x = function(x) {x*2*exp(-2*x)}

x2f_x = function(x) {x^2*2*exp(-2*x)}

(esperanza_x = integrate(xf_x, lower=0, upper=Inf)$value)

esperanza_x2 = integrate(x2f_x, lower=0, upper=Inf)$value

(varianza = esperanza_x2 - esperanza_x^2)
```

#### Variables Aleatorias Continuas Conocidas - VACC

- **Distribución Uniforme** X ~ U(a, b)
$$
FunciónDensidad = f(x) = \begin{cases} \frac{1}{b-a} & \text{a < x < b} \\ 0 & \text{resto} \end{cases} 
$$
$$
FuncDistribución = F(x) = \begin{cases} 0 & x\leq a \\ \frac{x-a}{b-a} & a < x < b \\ 1 & x \geq b \end{cases}
$$
$$
\mu = \frac{a+b}{2} \space\space\space\space  \sigma^2 = \frac{(b-a)^2}{12} 
$$
Veamos como se puede resolver uno de los problemas de esta distribución en R:

*La cantidad de miles de litros de gasolina despachada en una gasolinera en un día cualquiera es una variable aleatoria X que sigue una distribución uniforme en (7, 10)*

* *La probabilidad de que en un día cualquiera la cantidad despachada sea inferior a 8800 litros*
* *El valor esperado y la varianza del número de litros diarios*

```
a = 7

b = 10

punif(8.8, a, b) # Probabilidad de que la variable tome valores menores a 8.8 

media = (a+b)/2

varianza = (b-a)^2/12
```

- **Distribución exponencial** X ~Exp(alpha) con alpha > 0
$$
f(x) = \begin{cases} \alpha e^{-\alpha x} & \text{para } x > 0 \\ 0 & \text{resto} \end{cases}
$$
La exponencial es equivalente a la distribución geométrica, es decir, que nos interesa saber el tiempo que transcurre hasta que ocurra determinado evento. Veamos su función de densidad:
$$
F(x) = \begin{cases} 0 & x \leq 0 \\ 1-e^{-\alpha x} & \text{para } x > 0 \end{cases}
$$
Asimismo, veamos su media y varianza:
$$
\mu = \frac{1}{\alpha} \space \space y \space \space Var(X) = \frac{1}{\alpha^2}
$$
Esta distribución está estrechamente relacionada con la distribución de Poisson. Ya que si por ejemplo el número de llegadas sigue un proceso de Poisson, entonces los tiempos de llegada siguen una distribución exponencial. 

**Distribución Normal** X ~ N(mu, sigma^2) si su función de densidad es:

$$
f(x) = \frac{1}{\sqrt{2\pi}\sigma}e^{-\frac{x-\mu^2}{2\sigma^2}}, \space \space -\infty < \alpha < \infty
$$

De entre todas las distribuciones normales, destacamos la normal estándar con media 0 y varianza 1

$$
f(x) = \frac{1}{\sqrt{2\pi}}e^{\frac{-z^2}{2}}, \space \space \space -\infty < z < \infty
$$
Es interesante saber cómo se obtienen con R los percentiles de la N (0, 1)

```
# P(0.87 < Z < 1.28) 
pnorm(1.28) - pnorm(0.87)

# P(-0.34 <= Z <= 0.62)
pnorm(0.62) - pnorm(-0.34)

# P(Z >= -0.65)
1 - pnorm(-0.65) # o pnorm(0.65)

# z0.01 -> Percentil que deja por debajo de sí 1-0.01
qnorm(0.99) = 2.3263

# z0.05 -> Percentil que deja por debajo de sí 1-0.05
qnorm(0.95) = 1.6449
```

**Tipificación** 

Tradicionalmente, debíamos tipificar para calcular probabilidades de distribuciones normales que no fueran la estándar. En R no es necesario, ya que nos permite calcular la de cualquiera, introduciendo nosotros por ordenador las variables de la media y la desviación típica. Por ejemplo, veamos como podríamos hacerlo con el siguiente ejercicio:

*La radiación que recibe una persona ante una pantalla sigue una distribución N (media = 4.35, desviación = 0.59). Calcula la probabilidad de que la radiación esté entre 4.00 y 5.00 y la probabilidad de que la radiación sea mayor que 5.50*

```
# Probabilidad de que sea menor o igual que x sea menor o igual que 5 y luego que sea menor o igual que 4
pnorm(5, 4.35, 0.59) - pnorm(4, 4.35, 0.59) = 0.5582

# Hallamos el contrario de que sea x sea menor o igual que 5.5
1 - pnorm(5.5, 4.35, 0.59) = 0.0256
```

#### Extras

**Diferencias entre función de masa y función de densidad** 

- Función de masa: Da la probabilidad para cada punto según una fórmula.
- Función de densidad: Define la probabilidad en un intervalo como el área que queda por debajo de la curva de dicha función. 

**Diferencias entre distribuciones** - Datos de cara al examen 

- Binomial - estudiar el número de éxitos

- Geométrica - instante en el que se produce el primer éxito

- Poisson - contar el número de ocurrencias en un intervalo

- Uniforme - nos dirían cuando es, pero define cuando es constante

- Exponencial - tiempo hasta que ocurre algo

	- Exponencial y Poisson están relacionadas con la lambda de Poisson que es igual al parámetro alfa de la exponencial

- Normal - nos la suelen decir también, sale la palabra normal