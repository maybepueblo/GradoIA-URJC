En este documento, abarcaré los diversos ejercicios que vayamos haciendo en clase y que haga en mi tiempo libre (poco).

##### 1º Ejercicio

```
int a = 0;
for (int = 1; i < n, i++) {
	a = a + 1;
}
```

Empezamos indicando desde dentro hacia afuera cada instrucción y lo que tarde cada una de ellas.

``` 
int a = 0; --> Instrucción 1
```

Nuestra primera instrucción es de una operación básica de asignación, que sabemos que significa que tarda 1s en ejecutarse. 

Segunda instrucción será:

```
a = a + 1 --> Instrucción 2
```

Al ser una asignación y operación básica de suma, podríamos considerarlo tanto de tiempo 1s como de 2s. En este caso, lo consideraré tiempo 2s.

La última instrucción que hemos de analizar es el bucle:

```
for (int i = 1; i < n; i++) {
	I2
} 
```

Para evaluarla, tenemos que tener en cuenta que estamos ante un bucle que va desde i = 1 hasta i = n, esto lo señalizaremos como un sumatorio, veamos cómo se calcula:

$$T(I_3)=\sum_{i=1}^nI_2=\sum_{i=1}^n2=2n$$
Como podemos ver, hemos usado el bucle para analizar el tiempo de ejecución (y por tanto la complejidad) del *for*, teniendo finalmente que tarda un 2n segundos. 

Finalmente, hemos de hallar el orden de nuestro algoritmo en la escala de complejidad. Para hallar el total, hemos de sumar todas las instrucciones:

$$T()=I_1+I_3 = 1+2n$$
Hallamos el grado mayor de nuestra ecuación para poder reconocer la complejidad de este algoritmo:

$$O(n)$$
Así decimos que nuestro algoritmo es de complejidad O(n)
##### 2º Ejercicio 

```
x = 0; I1
for (int i = 1; i <= n; i++) { I5
	for (int j = 1; j <= n; j++) { I4 
		for (int k = 1; k <= n; k++) { I3
			x = x + 1; I2
		}
	}
}
```

Empezamos por I1, que al ser una operación básica de asignación, tenemos que:
$$T(I_1)= 1s$$
Luego, I2, puede tomarse o de 1s o de 2, en mi caso, la tomaré de 2s.

Posteriormente, empezamos con los bucles, veamos el caso de I3:
$$T(I_3)=\sum_{k=1}^n 2=2n$$
Sigamos esta vez con I4:

$$T(I_4)=\sum_{j=1}^n2n=2n^2$$
Y por último, analizamos I5:
$$T(I_5)=\sum_{i=1}^n2n^2=2n^3$$
Finalmente, podemos hallar el tiempo total sumando todas nuestras instrucciones (recordamos que los bucles se cuentan como uno, siendo el que se cuenta el bucle final que reúne a todos los otros, en este caso I5):

$$T=T(I_1)+T(I_5)=1+2n^3$$
Elegimos el miembro de mayor grado y tenemos la complejidad de nuestro algoritmo:

$$O(n^3)$$
##### 3º Ejercicio

```
x = 0; I1
if (n % 2 == 0) { I6
	for (int i = 1; i <= n; i++) { I5
		for (int j = 1; j <= i; j++) { I4
			x = x + 1; I3
		}
	}
} else { I7
	x = -1; I2
}
```

Hallamos rápidamente los casos sencillos como I3, I2 e I1, que tienen complejidades de 1, 2 y 1 respectivamente.

Veamos ahora los bucles, teniendo en cuenta que se complica un poco el caso ya que ahora j itera hasta i, no hasta n:
$$T(I_4)=\sum_{j=1}^i = 2i$$
Ahora, estudiemos cómo afecta esto al bucle en I5:
$$T(I_5)=\sum_{i=1}^n2i=2\sum_{i=1}^ni=2·\frac{n(n+1)}{2}=n^2+n$$
¿De dónde sale esto? Vamos a explicarlo:

Lo que tenemos es un caso donde tenemos una sumatoria de 2i iterando i desde 1 hasta n, como 2 es una constante, podemos echarla fuera del sumatorio, lo que deja sola a la i, que si desarrollamos este mismo sumatorio, quedaría así:
$$\sum_{i=1}^ni=1+2+3+4+5+···+(n-2)+(n-1)+n$$
Esto podemos también expresarlo como parejas de n+1 ya que si juntamos n + 1, también podemos juntar n - 1 + 2 = n + 1, y así sucesivamente, esto nos da exactamente n/2 parejas, lo que significa que nuestro sumatorio lo hemos expresado así:
$$1+2+3+4+5+···+(n-2)+(n-1)+n=\frac{n}{2}·(n+1)\space parejas$$
Si ahora volvemos a añadir el 2 que habíamos sacado del sumatorio antes, se nos anula el 2 y se nos queda n(n+1), lo que multiplicandolo nos da n^2+n.

Ahora sólo nos queda evaluar la condicional, vamos a ello:
$$T(I_6,I_7)=Tmax(I_6,I_7)=T(I_6)=n^2+n$$
Así, sólo nos queda sumarlo y ya sabremos la complejidad de nuestro algoritmo:
$$T=I_1+I_6=n^2+n+1=>O(n^2)$$
##### 4º Ejercicio

```
x = 0; I1
for (int i = 1; i <= n; i++) { I5
	for (int j = 1; j <= i; j++) { I4
		for (int k = j; k <= n; k++) { I3
			x = x + 1; I2
		}
	}
}
```

De la misma forma, analicemos las simples I1 e I2, que son de 1s y 2s respectivamente.

Ahora toca los bucles:
$$T(I_3)=\sum_{k=j}^n2=\sum_{k=j-(j-1)}^{n-(j-1)}2=\sum_{k=1}^{n-j+1}2=2n-2j+2$$
$$T(I_4)=\sum_{j=1}^i2n-2j+2=\sum_{j=1}^i2n-2\sum_{j=1}^ij+\sum_{j=1}^i2=2ni-2\frac{i(i+1)}{2}+2i=2ni-i^2+i$$
$$T(I_5)=\sum_{i=1}^n2ni-i^2+i=2n\sum_{i=1}^ni-\sum_{i=1}^ni^2+\sum_{i=1}^ni=n(n(n+1))-\frac{n(n+1)(2n+1)}{6}+\frac{n(n+1)}{2}$$
$$T(I_5)=n^3+n^2-\frac{2n^3}{6}+n^2+\frac{n^2+n}{2}=>O(n^3)$$
##### 5º Ejercicio

```
for (int i = 1; i < n; i++) { I11
	int pos = i; I10
	int x = v[i] I9
	int seguir = 1; I8
	while (pos > 0 && seguir == 1) { I6
		if (x < v[pos-1]){ I5
			v[pos] = v[pos-1]; I3
			pos = pos-1; I2
		} else { I4
			seguir = 0; I1
		}
	}
	v[pos]=x I7
}
```

$$T(I_1)=1,T(I_2)=1,T(I_3)=1,T(I_7)=1$$
$$T(I_5, I_4)=Tmax(I_5,I_4)=I_5=2s$$
Ahora, para hallar I6, podemos darnos cuenta de que se asemeja a la estructura de un bucle *for*, pudiendo definirlo como `for(int pos = i; pos > 0; pos--)` lo cual nos lleva a un bucle como ya conocemos:
$$T(I_6)=\sum_{pos=i}^02=2i$$
Teniendo este, ya podemos hallar el resto de elementos rápidamente:
$$T(I_8)=1, T(I_9)=1,T(I_{10})=1$$
$$T(I_{11})=\sum_{i=1}^nI_6+(I_{10}+I_9+I_8+I_7)=\sum_{i=1}^n2i+\sum_{i=1}^n4=2\frac{n(n+1)}{2}+4n$$
Esto se nos queda como:
$$T=n^2+n+4n=n^2+5n=>O(n^2)$$
##### 6º Ejercicio

```
int factorial(int n) {
	if (n == 1) {
		return 1; O(1) caso base
	} else {
		return n·factorial(n-1) caso recursivo
	}
}
```

$$T(n)=1 \space caso \space base$$
$$T(n)=\space nºllamadas\space recursivas·tiempo\space llamada+\space tiempo\space  resultado => \space caso\space  recursivo$$
Nuestro caso recursivo por ende, se puede expresar de la siguiente manera:
$$T(n)=1·T(n-1)+2$$
Siendo el 1 porque llamamos una vez, el T(n-1) que lo usamos solamente al ser recursiva la llamada y el +2 porque es lo que tarda en computarse el resultado. 

Ahora, podemos hallar el resultado a nuestra ecuación de recurrencia:
$$

\begin{array}
TT(n)=T(n-1)+2 \\
n'=n-1 \\
T(n-1)=T(n')
\end{array}
$$
Ahora, teniendo nuestro n', lo que hemos de hacer es volver a nuestra función de caso recursivo que nos explica que T(n)=T(n-1)+2, como podemos observar, tenemos exactamente esa construcción, siendo n=n', lo que equivale a que hemos de desarrollar nuestro T(n'), es decir, llamar nuevamente a la función recursiva sobre nuestro cambio de variable:
$$
T(n')=T(n'-1)+2
$$
Luego, nos queda deshacer el cambio de variable y ya tenemos un punto de partida por donde seguir, esto lo repetiremos alrededor de unas tres veces.
$$
\begin{array}
eT(n'-1)+2 \\
T(n-1-1)+2 \\
T(n-2)+2
\end{array}
$$
OJO! Hay que tener en cuenta que lo que estábamos haciendo hasta ahora era solo en referencia a nuestra función recursiva o lo que es lo mismo T(n-1). Por ende, nos queda sustituir T(n-1)=T(n-2)+2 en nuestro inicio de función T(n)=T(n-1)+2 y luego repetiremos:
$$
\begin{array}
TT(n)=T(n-1)+2\\
T(n)=T(n-2)+2+2=T(n-2)+4\\
T(n-2)=>n''=n-2\\
T(n''-1)+2\\
T(n-2-1)+2\\
T(n-3)+2\\
T(n-2)=T(n'')\\
T(n)=T(n-3)+2+4\\
T(n)=T(n-3)+6
\end{array}
$$
Observamos un patrón en esto que estamos haciendo, si siguiésemos al infinito, poniendo que el infinito es k, podemos llegar a esta estructura:
$$
T(n)=T(n-1)+2=T(n-2)+4=T(n-3)+6=···=^{k}T(n-k)+2k
$$
Queremos llegar a que k sea nuestro caso base para poder así resolver la función recursiva no? Después de todo, así funcionan este tipo de algoritmos. Entonces, lo que hemos de hacer es igualar nuestro caso T(n-k) a nuestro caso base T(1):
$$
\begin{array}
aT(n-k)=T(1)\\
n-k=1\\
k=n-1
\end{array}
$$
Una vez conocemos el valor de nuestra k, probamos a resolver en nuestro T(n-k)+2k a ver cómo se comporta finalmente en tiempo este algoritmo:
$$
\begin{array}
aT(n-k)+2k\space siendo \space k=n-1\\
T(n-(n-1))+2(n-1)\\
T(n-n+1)+2n-2\\
T(1)+2n-2\\
1+2n-2\\
2n-1
\end{array}
$$
>[!NOTE] OJO
>El T(1) lo he sustituido por 1s porque es lo que sabemos desde el principio, que nuestro caso base T(1) es de un segundo.

Entonces tenemos un algoritmo de complejidad O(n), ya que la constante se ignora, lo que resulta en una función g(n)=n y una c = 2.
##### 7º Ejercicio - Búsqueda secuencial en array

$$T(n)= 1 \textbf{  caso base}$$ $$T(n) = 1 · T(n-1) + 1 \textbf{ caso recursivo}$$
Teniendo en cuenta las explicaciones del ejercicio anterior, hacemos este de forma directa:
$$
\begin{array}
eT(n)=T(n-1)+1\\
n'=n-1\\
T(n'-1)+1\\
T(n-2)+1\\
T(n)=T(n-2)+1+1=T(n-2)+2\\
n''=n-2\\
T(n''-1)+1\\
T(n-2-1)+1\\
T(n-3)+1\\
T(n)=T(n-3)+1+2=T(n-3)+3\\
T(n)=T(n-1)+1=T(n-2)+2=T(n-3)+3=···=T(n-k)+k
\end{array}
$$
Ahora, igualamos a nuestro caso base:
$$
\begin{array}
aT(n-k)=T(1)\\
n-k=1\\
k=n-1\\
T(n-k)+k=^{k=n-1}T(n-(n-1))+n-1=T(n-n+1)+n-1\\
T(1)+n-1=1+n-1=n\\
O(n)
\end{array}
$$
##### 8º Ejercicio - Búsqueda binaria

Array ordenado donde busco "p", está el valor en la mitad? No. Pues central derecho del array y así sucesivamente.

$$T(n) = 1 \textbf{ caso} \space n =1$$
$$T(n) = 1 · T(\frac{n}{2})+1\textbf{ caso}\space n>1$$
Esto es porque llamamos una vez a la función y solucionamos un problema de tamaño n/2 cada vez (por ser la siguiente mitad).

$$
\begin{array}
aT(n)=T(\frac{n}{2})+1\\
n'=\frac{n}{2}\\
T(n')=T(\frac{n'}{2})+1\\
T(\frac{\frac{n}{2}}{2})+1=T(\frac{n}{2^2})+1\\
T(\frac{n}{2^2})+1+1=T(\frac{n}{2^2})+2\\
n''=\frac{n}{2^2}\\
T(\frac{n''}{2})+1\\
T(\frac{\frac{n}{2^2}}{2})+1\\
T(\frac{n}{2^3})+1\\
T(\frac{n}{2^2})+2=T(\frac{n}{2^3})+1+2=T(\frac{n}{2^3})+3
\end{array}
$$
El desarrollo que hemos hecho se puede expresar de la siguiente forma:
$$
\begin{array}
aT(n)=T(\frac{n}{2})+1=T(\frac{n}{2^2})+2=T(\frac{n}{2^3})+3=···=^kT(\frac{n}{2^k})+k
\end{array}
$$
Ahora nos queda igualar al caso base:
$$
\begin{array}
aT(\frac{n}{2^k})=T(1)\\
\frac{n}{2^k}=1\\
n=2^k\\
log_2n=log_22^k\\
log_2n=klog_22\\
k=log_2n
\end{array}
$$
Sustituyamos en nuestra expresión evaluada en k:
$$
\begin{array}
aT(\frac{n}{2^{log_2n}})+log_2n\\
a^{log_ay}=y\\
T(\frac{n}{n})+log_2n\\
T(1)+log_2n\\
1+log_2n\\
O(log(n))
\end{array}
$$
##### 9º Ejercicio - Merge sort

Base 1 corta y listo. Si no, dividimos constantemente en partes iguales.

$$T(n) = 1 \textbf{ caso} \space n =1$$
$$T(n) = 2·T(\frac{n}{2})+2\frac{n}{2} \textbf{ caso}\space n>1$$

$$
\begin{array}
aT(n)=2T(\frac{n}{2})+n\\
n'=\frac{n}{2}\\
T(n')=2·T(\frac{n'}{2})+n\\
2·T(\frac{n}{2^2})+n\\
T(\frac{n}{2})=T(n')\\
2·(2·T(\frac{n}{2^2})+\frac{n}{2})+n\\
2^2·T(\frac{n}{2^2})+n+n\\
2^2·T(\frac{n}{2^2})+2n\\
n''= \frac{n}{2^2}\\
2·T(\frac{n''}{2})+n''\\
2·T(\frac{n}{2^3})+\frac{n}{2^2}\\
T(\frac{n}{2^2})=T(n'')\\
2^2(2·T(\frac{n}{2^3})+\frac{n}{2^2})+2n\\
2^3·T(\frac{n}{2^3})+n+2n\\
2^3·T(\frac{n}{2^3})+3n\\
\end{array}
$$
Ya se nota el patrón que sigue este problema:
$$
\begin{array}
lT(n)=2·T(\frac{n}{2})+n=2^2·T(\frac{n}{2^2})+2n=2^3·T(\frac{n}{2^3})+3n=···=2^k·T(\frac{n}{2^k})+kn
\end{array}
$$
Igualemos al caso base:
$$
\begin{array}
aT(\frac{n}{2^k})=T(1)\\
\frac{n}{2^k}=1\\
n=2^k\\
log_2n=log_22^k\\
log_2n=klog_22\\
k=log_2n
\end{array}
$$
Finalmente, podemos sustituir en nuestra función evaluada en k:
$$
\begin{array}
22^{log_2n}·T(\frac{n}{2^{log_2n}})+log_2n·n\\
a^{log_ay}=y\\
n·T(\frac{n}{n})+nlog_2n\\
n·T(1)+nlog_2n\\
n+nlog_2n
\end{array}
$$
Ahora sí que sí, ya tenemos la complejidad de nuestro algoritmo:
$$
O(n·\log n) 
$$
