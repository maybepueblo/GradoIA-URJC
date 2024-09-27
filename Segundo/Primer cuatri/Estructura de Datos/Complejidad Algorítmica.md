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
x = 0;
for (int i = 1; i <= n; i++) {
	for (int j = 1; j <= n; j++) {
		for (int k = 1; k <= n; k++) {
			x = x + 1;
		}
	}
}
```

##### 3º Ejercicio

```
x = 0;
if (n % 2 == 0) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			x = x + 1;
		}
	}
} else {
	x = -1;
}
```

##### 4º Ejercicio

```
x = 0;
for (int i = 1; i <= n; i++) {
	for (int j = 1; j <= i; j++) {
		for (int k = j; k <= n; k++) {
			x = x + 1;
		}
	}
}
```

##### 5º Ejercicio

```
for (int i = 1; i < n; i++) {
	int pos = i;
	int x = v[i]
	int seguir = 1;
	while (pos > 0 && seguir == 1) {
		if (x < v[pos-1]){
			v[pos] = v[pos-1];
			pos = pos-1;
		} else {
			seguir = 0;
		}
	}
}
```

##### 6º Ejercicio

```
int factorial(int n) {
	if (n == 1) {
		return 1;
	} else {
		return n·factorial(n-1)
	}
}
```

##### 7º Ejercicio

``` 
// Búsqueda secuencial en array
```


