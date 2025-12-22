
Vamos a hacer una implementación parecida a la definida en [[Repaso ED Listas]] pero con un único array. De manera que quedara con esta estructura:

![[Pasted image 20241016093621.png]]

Veamos cómo implementarlo:

``` c
typedef struct {
	tElemento info;
	int sig;
} tNodo;
```

Y ahora nuestra nueva implementación:

```c
typedef struct {
	tNodo almacen[9]
	int primOcupada;
	int pimLibre;
} tLista
```

