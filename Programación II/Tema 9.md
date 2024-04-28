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

Cuando no vayamos a utilizar un fichero más, debemos cerrarlo con fclose(FILE * ). Este finaliza las operaciones de I/O, libera la memoria apuntada por el puntero a fichero y elimina la comunicación entre programa y fichero. Se vuelca el contenido del buffer de E/S, que puede contener datos no enviados al fichero. 

Una vez cerrado, no podemos volver a escribir o leer de él hasta su reapertura. 

```
	int fclose(FILE * pFichero);
```

Devuelve un entero: 
- 0 si se cerró correctamente.
- != 0 si hubo alagún error.

#### Lectura / Escritura

Las funciones fscanf y fprintf funcionan exactamente igual que scanf y printf, salvo que debemos indicar el fichero desde el que leemos o escribimos. 

**Lectura**

fscanf devolverá un entero cuyo valor es el número de variables leídas, un número negativo si no se ha leído ninguna variable, o un EOF si no se ha leído nada por encontrarse al final del fichero. 

Para comprobar la lectura, basta con verificar el número de variables leídas.

#### Otras funciones de los ficheros...

- La función *feof* permite comprobar si se ha alcanzado el final de un stream. Se devuelve un valor distinto de cero cuando se ha alcanzado el fin de fichero o cero en caso contrario.
- La función *rewind* permite situar el puntero del fichero al inicio del mismo.

#### Pero... ¿Cómo se ve esto en un programa?

Vamos a lo que verdaderamente importa, es decir, a por lo que en realidad estás leyendo esta inmensa cantidad de texto. Veamos cómo funciona todo en un programa real:

##### Ficheros de texto

En el caso de los ficheros de texto, veamos primero un código entero y vayamos desglosando el mismo poco a poco.

```
int main() {  
    int readAll;  
    int num = 123456;  
    // Definimos el archivo que vamos a crear y que abrimos además en modo           escritura exclusivamente
    FILE * testFile = fopen("test.txt", "w");  
    if (testFile == NULL) {  
        perror("Error when opening: ");  
    }  
  
    // Escribimos la variable en el archivo
    fprintf(testFile, "%d", num);  
  
    // Cerramos el archivo para que se guarden adecuadamente los cambios y así       poder ahora abrir en modo de lectura   
    fclose(testFile);  
  
    // Ahora, abrimos el archivo en modo de sólo lectura  
    testFile = fopen("test.txt", "r");  
    if (testFile == NULL) {  
        perror("Error when opening: "); // perror nos ayuda a saber si tenemos           algún error a la hora de abrir nuestro archivo  
    }  
  
    // Recibimos con fscanf todo el número que habíamos introducido  
    fscanf(testFile, "%d", &readAll);  
  
    fclose(testFile);  

	// Imprimimos el valor final que debería ser 123456
    printf("%i", readAll);  
  
    return 0;  
}
```

Como vemos, es un código simple pero que tiene margen a error si no sabemos lo que hace cada función. Cabe destacar que en el caso de fscanf, lo hemos usado para leer un número porque lee todo lo que coincida con el dato que tiene asignado a leer. No obstante, si quisiésemos leer un texto, no nos daría toda la frase, pues lee el primer dato que vea de ese tipo (en este caso considera a 123456 como un único dato). Si quisiésemos obtener una frase, hemos de usar *fgets*. Veamos un ejemplo para hacerlo más didáctico:

```
int main() {  
    FILE * test2 = fopen("test2.txt", "w+");  
    if (test2 == NULL) {  
        perror("Error when opening: ");  
        return 1;  
    }  
  
    fprintf(test2, "Here's me introducing myself to a bunch of people on the         Internet! \n Great!!!");  

	// Usamos un rewind para poner el puntero que señala al texto de vuelta en       el inicio del documento
    rewind(test2);  

	// Leemos hasta el primer salto de línea que encuentre el programa
    char readall[100];  
    fgets(readall, 100, test2);  
  
    fclose(test2);  
  
    printf("%s", readall);  
  
    return 0;  
}
```

Ahora sí que sí, el resultado final de este programa ha de ser la frase: *Here's me introducing myself to a bunch of people on the Internet!*. Pero, ¿por qué no se incluye el *Great!!!*? Pues por como funciona *fgets*, que lee hasta que encuentre un salto de línea, ideal para lo que buscábamos.

Cabe resaltar que he metido un *rewind* aposta, lo cual nos ahorra tener que volver a cerrar y abrir el archivo, lo cual nos lleva a un código mucho más limpio y menos tedioso. Lo que hace esta función es obvio, mueve el puntero que señala a la ubicación del fichero donde estamos ahora (ya sea para leer o escribir) al inicio del fichero nuevamente.
##### Ficheros binarios

Bien, una vez hemos visto un poco de todo lo que son los ficheros de texto, toca ponernos con los que tienen mayor complejidad, los binarios. 

```
int main() {  
    FILE * testBinary = fopen("testBinary.bin", "wb+");  
    if (testBinary == NULL) {  
        perror("Error when opening");  
        return -1;  
    }  
    int num[5] = {1, 2, 3, 4, 5};  
    int numread[5];  

	// (variable a introducir, tamaño del dato, cuánto escribimos, archivo)
    fwrite(num, sizeof(int), 5, testBinary);  
  
    rewind(testBinary);  

	// (variable para guardar dato, tamaño del dato, cuánto leemos, archivo)
    fread(numread, sizeof(int), 5, testBinary);  
  
    fclose(testBinary);  
  
    for (int i = 0; i < 5; ++i) {  
        printf("%i\n", numread[i]);  
    }  
  
    return 0;  
}
```

Ahora encontramos muchas similitudes frente a los ficheros de texto, sin embargo, cabe destacar que ahora tenemos la necesidad de usar funciones como *fwrite* o *fread*, no como las anteriores *fprintf* o *fscanf*.

Asimismo, existen los mismos comandos de modo que antes pero ahora se señalan los mismos con una b de binario que les acompaña. Existen muchas más funciones, comentemos superficialmente algunas que nos pueden ser de utilidad

##### Otras funciones de interés y un resumen de algunas conocidas

- `fopen`: Esta función se utiliza para abrir un archivo. Puedes especificar diferentes modos, como “r” para lectura y “w” para escritura.
    
- `fclose`: Esta función se utiliza para cerrar un archivo que ha sido abierto.
    
- `fgets`: Esta función se utiliza para leer una línea de un archivo de texto.
    
- `fputs`: Esta función se utiliza para escribir una línea en un archivo de texto.
    
- `fseek`: Esta función te permite mover el puntero de archivo a una posición específica. Es útil si necesitas leer o escribir en una ubicación específica en un archivo de texto.
    
- `ftell`: Esta función te devuelve la posición actual del puntero de archivo. Puede ser útil en combinación con `fseek`.
    
- `rewind`: Esta función mueve el puntero de archivo de vuelta al principio del archivo.
    
- `feof`: Esta función te permite saber si has llegado al final de un archivo. Es útil en bucles de lectura.
    
- `ferror`: Esta función te permite saber si ha ocurrido un error al leer o escribir en un archivo

#### Más información
---
Para saber más sobre ficheros haga click en [[Ficheros]]


