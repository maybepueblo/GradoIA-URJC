Datos almacenados a través de [números binarios]([Sistema binario - Wikipedia, la enciclopedia libre](https://es.wikipedia.org/wiki/Sistema_binario)). En contraposición a los ficheros de texto, estos no pueden ser leídos ni escritos por el usuario.

Si abrimos un fichero en modo binario, podemos escribir los bytes de las variables. Para ello contamos con las funciones *fread* y *fwrite*.

```
	fread(void *ptr, int size, int numElems, FILE *f);
```

- ptr: dirección de memoria de la variable que vamos a leer.
- size: número de bytes que ocupa cada elemento.
- numElems: número de elementos a leer.
- f: puntero al fichero.

```
	fwrite(void *ptr, int size, int numElems, FILE *f);
```

Como bien observamos, es literalmente lo mismo que fread, pero esta vez para la escritura. 

**Acceso directo**

Los ficheros binarios se pueden tratar como secuencias de bytes. El número de bytes es el índice del archivo. Se mantiene esta posición con el puntero a fichero.

La función ftell devuelve el valor en que se halla el puntero del fichero como número de bytes desde el inicio del archivo (byte 0).

```
	ftell(FILE *f);
```

Siendo f el puntero al fichero. Cabe destacar que ftell también se puede usar en ficheros de texto. 

Por último, la función fseek sitúa el puntero del fichero en una posición concreta del fichero. 

```
	fseek(FILE *f, long desplazamiento, int origen);
```

- f es nuevamente el puntero del fichero.
- desplazamiento --> número de bytes a mover el puntero de acceso. El desplazamiento puede ser negativo. 
- origen --> punto desde el que comenzamos a contar el desplazamiento. Puede tener tres valores: 
	- 0 (SEEK-SET) -> cuenta desde el inicio del archivo
	- 1 (SEEK-CUR) -> cuenta desde la posición actual del puntero del archivo
	- 2 (SEEK-END) -> cuenta desde el final del archivo