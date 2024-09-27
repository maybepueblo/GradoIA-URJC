Veamos las soluciones a los ejercicios que se pusieron en la convocatoria extraordinaria del año 2022-2023 de programación II. 

OJO! Cabe destacar que ese año no dieron POO con lo cual se dieron librerías de Python, cosa que este año no hemos dado.

#### Ejercicio 1 - Teoría
El examen constó de 10 preguntas de tipo test sobre abstracción, TADs y librerías. Veamos las soluciones a las mismas:

1. ¿Podemos cambiar el valor numérico de los valores de un tipo enumerado?
2. No es posible crear arrays cuyo tipo sea un struct.
3. Es posible dar nombres sinónimos a un tipo de datos definido en C (por ejemplo llamar entero a int).
4. stderr es un stream que permite leer del teclado.
5. La abstracción oculta los detalles de implementación de ciertos elementos.
6. Un TAD simplifica el desarrollo y mantenimiento, dado que por ejemplo correcciones de errores menores no afectan a quienes usan el TAD.
7. Los TADs deben ser ambiguos, dando lugar a diversas interpretaciones.
8. C es un lenguaje orientado a POO.
9. Es posible usar librerías en C de las que no disponemos el código fuente.
10. SQLite es una librería que facilita la gestión de imagen y vídeo, especialmente en aplicaciones relacionadas con la IA, como el reconocimiento de imágenes.

Veamos las soluciones a estas respuestas uno por uno:

1. Verdadero, podemos hacer lo siguiente:

```
typedef enum {
	int valor, // Sin cambiar valor tenemos que es 0
	int valor2, // Sería 1
	int valor3 // Sería 2
} enumBasico;

typedef enum {
	int valor = 3,
	int valor2 = 1,
	int valor3 = 0
} enumCambiado;
```

2. Falso, claro que podemos hacerlo, tal y como vimos en la [[Práctica 2 - Agenda]].
3. Sí es posible ya que no guardan relación.
4. Falso, stderr es el que maneja las excepciones o errores, es stdin el que permite leer de teclado.
5. Verdadero, tal y como vimos en [[Tema 10 - Abstracción]].
6. Verdadero, tal y como vimos en [[Tema 11 - TADs]].
7. Falso, deben ser simples y claro, dando lugar a una única implementación.
8. Falso, es un lenguaje imperativo tal y como vimos en [[Paradigmas de programación]].
9. Verdadero, simplemente tenemos que saber el nombre de la librería.
10. Falso, SQLite es una database de SQL

#### Ejercicio 2 - Registros

***Enunciado***
Define una estructura en C que permita almacenar el nombre del estudiante, su DNI, y la nota que va a sacar en el examen de la convocatoria extraordinaria. El nombre de la estructura debe ser TipoExamen

```
typedef struct {  
    char nombre[30];  
    char DNI[10];  
    double nota;  
} TipoExamen;
```

Aquí tenemos el struct definido, bastante simple y poco más que comentar. Si no se acuerdan de los structs, es mejor revisar [[Tema 8 - Tipos enumerados y registros]].

#### Ejercicio 3 - Ficheros de texto

***Enunciado***
Escribe una función en C que reciba el nombre de un fichero de texto, y devuelva como valor de retorno el número de líneas en blanco. Se considera que una línea está en blanco cuando o bien no tiene ningún carácter, o solo contiene espacios. En caso de error en el acceso o lectura de alguno de los ficheros, la función deberá devolver el valor -1. Se garantiza que todas las líneas del fichero tienen menos de 1024 caracteres.

Veamos primero el código en pos de desglosarlo bien:

```
int lineasBlancas() {  
    char filename[50] = "ejemplo.txt";  
    printf("Dame el nombre de un fichero de texto:");  
    scanf(" %s", filename);  
    FILE * archivo = fopen(filename, "r");  
    if (archivo == NULL) {  
        perror("ERROR");  
        return -1;  
    }  
  
    char line[1024];  
    int blank = 0;  
    while (fgets(line, 1024, archivo)) {  
        int isBlank = 1;  
        for (int i = 0; line[i] != '\0'; ++i) {  
            if (line[i] != ' ' && line[i] != '\n' && line[i] != '\r') {  
                isBlank = 0;  
                break;  
            }        }        if (isBlank) {  
            blank++;  
        }    }  
    fclose(archivo);  
  
    printf("Tu archivo tiene un total de %i lineas en blanco", blank);  
  
    return 0;  
}
```

Bien, lo único que puede traer confusión en este código es la parte de nuestro bucle, vamos a desglosarlo:

```
char line[1024];  
    int blank = 0;  
    while (fgets(line, 1024, archivo)) {  
        int isBlank = 1;  
        for (int i = 0; line[i] != '\0'; ++i) {  
            if (line[i] != ' ' && line[i] != '\n' && line[i] != '\r') {  
                isBlank = 0;  
                break;  
            }        }        if (isBlank) {  
            blank++;  
        }    }  
```

Lo que estamos haciendo primero que todo es definir un char de tamaño máximo que puede tener una línea, unos 1024 caracteres. Asimismo, tenemos que definir la variable entera que cuenta el número de líneas en blanco.

Ahora, creamos un bucle que lea mientras el fgets no sea NULL, cosa que pasará si no hay más líneas o saltos de línea delante para seguir bajando.

Definimos un entero booleano `isBlank` que está puesto en *true* por defecto. Con él haremos un bucle que recorra todo nuestro array línea que tiene unos 1024 caracteres, es decir, recorremos la línea hasta llegar al carácter nulo que se deja automáticamente al final de un char en C.

Analizando estos valores, si el valor no es ni un espacio, ni un salto de línea ni ningún retorno de carro (lo mismo que un salto), pues entonces no está vacío y por ende la línea no está vacía.

En caso de que este for vea todo en orden, pues tenemos que sí podemos sumar uno al contador de nuestros espacios en blanco.

#### Ejercicio 4 - Ficheros binarios

***Enunciado***
Escribe una función en C que reciba 3 argumentos, siendo estos el nombre del alumno, su DNI y su nota. Utiliza el tipo de datos declarado en el ejercicio 2, y añádelo a un fichero binario llamado examenes.bin. Es importante que no se eliminen los datos existentes al añadir nuevos exámenes al fichero. El tipo de retorno de la función debe ser un entero. En caso de que la operación se haya podido completar con éxito devolverá el valor 0, si ocurre cualquier error en la apertura o cierre del fichero debe devolver el valor -1. 

Veamos nuevamente el código necesario para programar esto:

```
int escribirBinario(char *nombre, char *DNI, double nota) {  
    FILE * archivoB = fopen("examenes.bin", "ab");  
    if (archivoB == NULL) {  
        perror("ERROR");  
        return -1;  
    }  
    TipoExamen alumno;  
    strcpy(alumno.nombre, nombre);  
    strcpy(alumno.DNI, DNI);  
    alumno.nota = nota;  
  
    fwrite(&alumno, sizeof(TipoExamen), 1, archivoB);  
  
    if (fclose(archivoB) != 0) {  
        perror("ERROR");  
    }  
    return 0;  
}
```

En este caso, lo único que tenemos que hacer es primero definirnos nuestra propia variable TipoExamen dentro de nuestra función para darle todos los parámetros que hemos recibido. Una vez tengamos eso, como estamos en el modo ab (append binario) que directamente escribe al final del archivo, no hay nada más que hacer que un fwrite que nos copie el contenido de la variable que hemos definido en el fichero binario.

Como un pequeño bonus y siendo una función tan fácil, cree la siguiente función `leerBinario` que me permite comprobar que se está escribiendo todo bien en el archivo .bin. Vamos a ver cómo la llevé a cabo:

```
int leerBinario() {  
    char *filename = "examenes.bin";  
    FILE * archivo = fopen(filename, "rb");  
  
    TipoExamen alumno;  
  
    printf("\n");  
  
    char line[255];  
    while (!feof(archivo)) {  
        fread(&alumno, sizeof(TipoExamen), 1, archivo);  
        if (!feof(archivo))  
        printf("%s %s %lf\n", alumno.nombre, alumno.DNI, alumno.nota);  
    }  
    if (fclose(archivo) != 0) {  
        perror("ERROR");  
        return -1;  
    }  
    return 0;  
}
```

Es simple pero lo único que buscamos es que mientras el puntero del archivo no esté al final, leeremos los alumnos que hemos metido y los imprimiremos por pantalla, así de fácil pero muy útil para revisar los fallos que estamos teniendo.

Y hasta aquí el examen del año pasado, gracias por leerme!

