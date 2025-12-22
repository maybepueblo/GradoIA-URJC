En esta entrada de Obsidian, vamos a ver los ejercicios del examen del año pasado al mío, vamos a resolverlos y a explicarlos además.

Tenemos los siguientes ejercicios:

- `Teoría` -> Hay una pequeña sección de teoría.
- `Ejercicio 2` -> Se nos pide crear una estructura de datos que almacene las tres coordenadas de un punto en 3 dimensiones usando números reales.
- `Ejercicio 3` -> Hacer una función que reciba el nombre de un fichero de texto y devuelva como valor de retorno el número de líneas que contiene el fichero. En caso de error en el acceso o lectura del fichero se ha de devolver -1.
- `Ejercicio 4` -> Reusando código del ejercicio anterior, hemos de escribir una función en C que reciba un fichero con tres números reales en cada línea. La función leerá el contenido y usando la estructura ya definida, creará un fichero binario con el contenido leído del fichero de texto.

#### Teoría

Indicar si las siguientes afirmaciones son verdaderas o falsas:

 - **Los ficheros .h se suelen usar para implementar los métodos declarados en los ficheros .c.**
		Falso, de hecho es al revés, en los ficheros .h declaramos nuestros métodos y en el fichero .c buscamos implementarlos.
- **No es posible llamar a funciones implementadas en C o en C++ usando Python.**
		Falso, sí que es posible, existen librerías que permiten esto. 
-  **La abstracción expone la funcionalidad. El usuario del componente solamente sabe qué hace el componente, pero no cómo lo hace.**
		Verdadero, véase en [[Tema 10 - Abstracción]].
-  **Los structs no pueden contener otros structs.**
		Falso, cualquier struct puede contener otro struct dentro de sí.
- **OpenCV es una librería que permite manipular bases de datos fácilmente desde C.**
		Verdadero.
-  **Para poder usar un TAD, necesitamos conocer su implementación.** 
		Falso, justamente lo bueno de los TAD es que podemos usarlos sin saber cómo hacen lo que hacen.
- **Podemos usar la directiva include para extender la funcionalidad de nuestro fichero usando librerías.**
		Verdadero, tal y como hemos visto desde el principio de la materia.
-  **La abstracción funcional consiste en la creación de nuevos tipos de datos.**
		Falso, la abstracción funcional no tiene nada que ver, véase [[Tema 10 - Abstracción]].
- **Un TAD es una colección de valores, junto con unas operaciones sobre ellos, definidos mediante una especificación que es independiente de cualquier implementación.**
		Verdadero, es exactamente la definición que vimos en [[Tema 11 - TADs]].
- **C es un lenguaje de programación orientado a objetos.**
		Falso, justamente es un lenguaje de programación imperativa y estructurada, tal y como lo clasificamos en [[Paradigmas de programación]].

#### Ejercicio 2

*Enunciado* --> Escribe el código en C que cree una estructura de datos de nombre *tipoPunto* que almacene las tres coordenadas de un punto en 3 dimensiones usando números reales.

```
typedef struct {  
    float x;  
    float y;  
    float z;  
} tipoPunto;
```

Y ya estaría, es bastante fácil pero es después de todo lo único que nos pide. Cabe resaltar que también podemos poner que son valores de tipo `double` en vez de `float`, que serviría de igual forma.

#### Ejercicio 3

*Enunciado* -> Escribir una función en C que reciba el nombre de un fichero de texto y devuelva como valor de retorno el número de líneas que contiene ese fichero. En caso de error en el acceso o lectura de fichero, deberá devolver el valor -1.

```
int numLineas() {  
    char filename[255] = "example.txt";  
    printf("Dame el nombre del fichero de texto (ejemplo.txt):");  
    scanf(" %s", filename);  
    FILE * archivo = fopen(filename, "r");  
    if (archivo == NULL) {  
        perror("ERROR WHEN READING FILE");  
        return -1;  
    }  
    int count = 0;  
    char linea[255];  
    while (fgets(linea, 255, archivo)) {  
        count++;  
    }  
    if (fclose(archivo) != NULL) {  
        return -1;  
    }  
    printf("Fichero leido de forma exitosa\n");  
  
    return count;  
}
```

En este caso, hemos de hacer un bucle simple que consiste en un fgets, que lee hasta que llegue hasta 254 caracteres o hasta un salto de línea, lo cual es idóneo para poder contar todas las líneas que hay en el archivo.
#### Ejercicio 4

*Enunciado* -> Escribe una función en C que reciba el nombre de un fichero de texto que contendrá tres números reales en cada línea representando las coordenadas de puntos en 3D. La función deberá leer el contenido del fichero de texto y utilizando la estructura de datos del ejercicio 2, creará un fichero binario con el contenido leído del fichero de texto. El nombre del fichero binario será siempre binario.bin. Se supone que el fichero de texto está bien construido. En caso de errores la función deberá devolver -1. Si no los hay, devolveremos 0.

```
int coordenadasBinario() {  
    char filename[255];  
    printf("Dame el nombre del archivo a leer");  
    scanf(" %s", filename);  
  
    FILE * archivo = fopen(filename, "r");  
    if (archivo == NULL) {  
        perror("Fallo en el archivo");  
        return -1;  
    }  
    FILE * archivoB = fopen("binario.bin", "wb");  
    if (archivoB == NULL) {  
        perror("Fallo en el archivo");  
        return -1;  
    }  
    char line[255];  
    tipoPunto coordenada;  
    while (fgets(line, 255, archivo)) {
	    // Parseo de datos  
        sscanf(line, " %f %f %f", &coordenada.x, &coordenada.y,  
               &coordenada.z);
		printf("%.2f %.2f %.2f\n", coordenada.x, coordenada.y, coordenada.z);
		// Escribir en el archivo binario		 
        fwrite(&coordenada, sizeof(tipoPunto), 1, archivoB);  
    }  
    if (fclose(archivo) != NULL) {  
        perror("Error de cierre");  
        return -1;  
    }  
    if (fclose(archivoB) != NULL) {  
        perror("Error de cierre");  
        return -1;  
    }  
    return 0;  
}
```

Aquí hemos de definir un dato perteneciente a la estructura de datos `tipoPunto` con tal de ir guardando los datos de un fichero de texto. Parseamos con sscanf y luego imprimimos los datos en el archivo binario directamente. El printf del medio es para revisar que efectivamente estamos leyendo los datos correctamente.  