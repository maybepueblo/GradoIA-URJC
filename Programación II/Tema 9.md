**Operaciones con ficheros**

Hasta el momento, en los temas anteriores, leíamos los datos a través del teclado y se imprimían en consola. Así, estos datos se perdían al finalizar el programa. Necesitamos entonces una forma de guardar los datos para poder acceder a ellos en otro momento. 

#### FILE *

Se define en stdio.h, crea un flujo, llamado **stream**, de datos que comunica con el fichero. Almacena lo siguiente:
- **Buffer** --> almacén intermedio por donde pasan bloques de datos antes de hacer la operación de I/O.
- **Cursor** --> puntero a la posición donde se realizará la siguiente operación.
- **EOF** --> indicador para saber si se ha leído el fichero completo.
- **Error** --> indicador de errores I/O

Al ejecutar un programa existen 3 streams de texto por defecto:
- stdin --> entrada estándar, para poder leer de teclado.
- stdout --> salida estándar, para poder escribir por pantalla. 
- stderr --> salida de error estándar, para informar sobre errores producidos. 
Cualquier programa con stdio.h puede usarlos. 

#### Cierre de ficheros - fclose

Cuando no vayamos a utilizar un fichero más, debemos cerrarlo con fclose(FILE * ).  Este finaliza las operaciones de I/O, libera la memoria apuntada por el puntero a fichero y elimina la comunicación entre programa y fichero. Se vuelca el contenido del buffer de E/S, que puede contener datos no enviados al fichero. 

Una vez cerrado, no podemos volver a escribir o leer de él hasta su reapertura. 

```
	int fclose(FILE * pFichero);
```

Devuelve un entero: 
- 0 si se cerró correctamente.
- != 0 si hubo algún error.

#### Lectura / Escritura

Las funciones fscanf y fprintf funcionan exactamente igual que scanf y printf, salvo que debemos indicar el fichero desde el que leemos o escribimos. 

**Lectura**

fscanf devolverá un entero cuyo valor es el número de variables leídas, un número negativo si no se ha leído ninguna variable, o un EOF si no se ha leído nada por encontrarse al final del fichero. 

Para comprobar la lectura, basta con verificar el número de variables leídas.

#### Otras funciones de los ficheros...

- La función *feof* permite comprobar si se ha alcanzado el final de un stream. Se devuelve un valor distinto de cero cuando se ha alcanzado el fin de fichero o cero en caso contrario.
- La función *rewind* permite situar el puntero del fichero al inicio del mismo.

#### Más información
---
Para saber más sobre ficheros haga click en [[Ficheros]]


