>[!NOTE] Propósito de la práctica
>Nuevamente volvemos con programación II, esta vez para hacer una práctica basada alrededor de los ficheros binarios. Cabe destacar que esta práctica tiene mucho que ver con su predecesora la [[Práctica 3 - Agenda con ficheros de texto]], por lo cual si no la has visto, recomiendo echarle un vistazo a ella primero.
>
>Sin más dilación, esta práctica busca más o menos lo mismo, pero ahora nos tenemos que mover por nuestra agenda no en programa, sino siempre en disco con un fichero *agenda.dat* que tendremos que crear en el mismo programa en pos de almacenar todos nuestros datos. 
>
>Por lo demás, tenemos que implementar una serie de funciones como son el añadir contactos, eliminarlos, exportar la agenda a un archivo o importarla de uno, y finalmente pero más importante, enseñar los contactos de la agenda.

En este caso, como tenemos impuesta la restricción de no poder usar memoria del programa sino que siempre hemos de utilizar el archivo binario, se complica un poco la cosa. Veamos cómo desglosar esta práctica:

- `Menú principal` -> Como siempre, una parte vital del programa que nos enseña las posibles opciones. Tiene el mismo número de funciones que la práctica anterior, pero cambian un par de elementos. 
- `Preparación previa` -> Dentro de esta práctica la preparación previa es mucho más sencilla, veremos el por qué.
- `Lista de contactos` -> Ahora, como hemos de acceder desde un fichero binario todo el rato, hemos de tener esto en cuenta. 
- `Añadir y eliminar contacto` -> Son dos funciones que trataremos en un mismo capítulo pero no sin explicar las diferencias a las usadas anteriormente.
- `Importar y exportas contactos` -> En este caso hemos de importar y exportar a ficheros de texto, veremos cómo se hace y lo desglosaremos de debida manera.

#### Menú principal

```
int main() {  
    int choice;  
  
  
    do {  
        printf("\n");  
        printf("---- MENU ----\n");  
        printf("1 - Contacts\n");  
        printf("2 - New contact\n");  
        printf("3 - Remove contact\n");  
        printf("4 - Export agenda to text file\n");  
        printf("5 - Import agenda from text file\n");  
        printf("0 - Exit program\n\n");  
  
        printf("Choose an option:");  
        scanf(" %i", &choice);  
  
        switch (choice) {  
            case 1:  
                contactList();  
                break;  
            case 2:  
                addContact();  
                break;  
            case 3:  
                removeContact();  
                break;  
            case 4:  
                exportAgenda();  
                break;  
            case 5:  
                importAgenda();  
                break;  
            case 0:  
                printf("\nGoodbye!!!\n");  
                break;  
            default:  
                printf("Option not registered");  
        }  
    } while (choice != 0);  
  
  
    return 0;  
}
```

Cabe destacar que en este caso ya no tenemos la función que precedía al código del menú principal en la [[Práctica 3 - Agenda con ficheros de texto]] y en la [[Práctica 2 - Agenda]]. Esto es debido a que como ahora siempre hemos de interactuar con la agenda a través del archivo *agenda.dat*, no hay necesidad para comenzar inicializando espacio ni nada.

#### Preparación previa

Vamos a ver un poco la reducida preparación que tenemos que llevar a cabo en esta práctica:

```
#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
  
#define MAX 30  
  
// We define the struct  
typedef struct {  
    char name[MAX];  
    char surname[MAX];  
    char phone[9];  
    int age;  
    char type[MAX];  
} typePerson;  
  
// Declarations  
void contactList();  
void addContact();  
void removeContact();  
void exportAgenda();  
void importAgenda();
```

Esta vez, tal y como se ve en el código nos hemos quitado dos elementos, el `agendaType` y el tipo enumerado `contactType`. Esto se debe a que como hemos de leer todo del archivo, el enumerado no nos sirve y es mejor leer directamente el dato, y en caso de que queramos añadir a alguien nuevo, especificarle como ha de escribirlo. 

Por otro lado, el ``agendaType`` desaparece por la falta de necesidad de él, ya que como dije antes, no necesitamos iniciar ninguna agenda previamente.

#### Lista de contactos

Vamos a empezar con las funciones de nuestro menú:

```
void contactList() {  
    FILE * file = fopen("agenda.dat", "rb");  
    typePerson person;  
    int i = 1;  
    //char type[MAX];  
    while (fread(&person, sizeof(typePerson), 1, file)) {  
        printf("%i;%s;%s;%s;%i;%s\n", i, person.name, person.surname, person.phone, person.age,  
               person.type);  
        i++;  
    }    fclose(file);  
}
```

Lo que cambia en este programa es la necesidad imperativa de abrir el archivo binario en modo lectura para poder ir enseñando por pantalla todos los contactos que tenemos en la agenda binaria. 

Antes que nada, es propio hacer un inciso con como funciona el *fread()*. En este caso, vamos leyendo en person (un nuevo tipo de dato basado en el *struct* con el cual luego se nos vuelve fácil enseñar cada persona). Por lo demás, leemos un dato de tamaño struct typePerson, leyendo una línea por vez y todo esto siendo leído desde file.

#### Añadir y eliminar contactos

##### Añadir contactos

```
void addContact() {  
    FILE * file = fopen("agenda.dat", "ab");  
    typePerson p;  
    printf("Name:");  
    scanf(" %s", p.name);  
  
    printf("\nSurname:");  
    scanf(" %s", p.surname);  
  
    printf("\nPhone number (9 digits):");  
    scanf(" %s", p.phone);  
  
    printf("\nAge:");  
    scanf(" %i", &p.age);  
  
    printf("\nType of contact (FAVOURITE, WORK or ACQUAINTANCE):");  
    scanf(" %s", p.type);  
  
    fwrite(&p, sizeof(typePerson), 1, file);  
  
    printf("\nContact added successfully\n");  
  
    fclose(file);  
}
```

En este caso no hay mucho cambio, lo único que buscamos es tener el archivo abierto en modo "ab", que abre un archivo binario para escribir en el mismo justo al final del todo, lo cual nos viene de perlas en pos de no tener algún problema con el puntero de posicionamiento en el archivo. 

##### Eliminar contactos

```
void removeContact() {  
    FILE *file = fopen("agenda.dat", "rb");  
    FILE *temp = fopen("temp.dat", "wb");  
  
    typePerson person;  
  
    int num, i;  
    i = 1;  
    printf("Index of the person to remove:");  
    scanf(" %i", &num);  
        while (fread(&person, sizeof(typePerson), 1, file)) {  
        if (i != num) {  
            fwrite(&person, sizeof(typePerson),1, temp);  
        }        i++;  
    }  
    printf("\nContact deleted succesfully\n");  
  
    fclose(file);  
    fclose(temp);  
    remove("agenda.dat");  
    rename("temp.dat", "agenda.dat");  
}
```

Esta función si bien no es complicada, tiene ciertas diferencias con nuestra aproximación al problema respecto a casos previos.

En este caso vamos a apoyarnos de un archivo auxiliar, el cual crearemos para escribir todos los contactos que no coincidan con el número de contacto que le pedimos al usuario que nos de. De esta manera, nos ahorramos problemas y simplificamos el código, teniendo que simplemente eliminar el archivo original y renombrar el auxiliar a *agenda.dat* al final de la función para que se pueda seguir usando el programa.

#### Importar y exportar contactos

##### Exportar contactos

```
void exportAgenda() {  
    FILE *file = fopen("agenda.dat", "rb");  
    FILE *export;  
    char filename[50];  
    printf("Name of the text file:");  
    scanf(" %s", filename);  
    export = fopen(filename, "w");  
    typePerson person;  
    int i = 1;  
    while (fread(&person, sizeof(typePerson), 1, file)) {  
        fprintf(export, "%i;%s;%s;%s;%i;%s\n", i, person.name, person.surname, person.phone,  
                person.age, person.type);  
        i++;  
    }  
    printf("\nAgenda exported successfully to %s\n", filename);  
  
    fclose(file);  
    fclose(export);  
}
```

En este caso, lo que hacemos es simple:
1. Abrimos "agenda.dat" en modo lectura a la par que creamos el archivo `export` donde meteremos todo el contenido.
2. Le pedimos al usuario que nos de el nombre de este nuevo archivo.
3. Mientras que se pueda leer líneas del archivo binario, las anotaremos en el nuevo archivo de texto creado.
4. Finalmente, cerramos el archivo y damos un mensaje de confirmación.

##### Importar contactos

```
void importAgenda() {  
    FILE * file = fopen("agenda.dat", "w+");  
    FILE * import;  
    char filename[MAX];  
    printf("File you want to import the agenda from:");  
    scanf(" %s", filename);  
    import = fopen(filename, "r");  
    typePerson person;  
    char line[255];  
    int index = 0;  
    while (fgets(line, sizeof(line), import)) {  
        sscanf(line, "%i;%[^;];%[^;];%[^;];%i;%s", &index, person.name, person.surname, person.phone,  
               &person.age, person.type);  
        fwrite(&person, sizeof(typePerson), 1, file);  
    }  
    printf("\nAgenda imported successfully from %s\n", filename);  
  
    fclose(file);  
    fclose(import);  
}
```

Esta sí me tomó un poco más de tiempo pero el procedimiento es simple:

1. Nuevamente, abrimos agenda.dat, pero esta vez en pos de escribir en ella.
2. Ahora, una vez tengamos el nombre del archivo a importar, hemos de ir escribiendo en la agenda mientras que halla líneas que leer del archivo importado. Cabe recordar que fgets lee hasta el número de caracteres que le especifiquemos o hasta un salto de línea. En este caso, cuando ya no haya más texto después de un salto de línea, el bucle parará.
3. Y una vez asignado todo el contenido nuevamente a la agenda, ya tenemos todo. Así, cerramos el archivo y mandamos confirmación de la operación.











#### Programa final

Ahora, en esta sección no queda mucho más por decir, aquí tienen el programa completo:

```
#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
  
#define MAX 30  
  
// We define the struct  
typedef struct {  
    char name[MAX];  
    char surname[MAX];  
    char phone[9];  
    int age;  
    char type[MAX];  
} typePerson;  
  
// Declarations  
void contactList();  
void addContact();  
void removeContact();  
void exportAgenda();  
void importAgenda();  
  
int main() {  
    int choice;  
  
  
    do {  
        printf("\n");  
        printf("---- MENU ----\n");  
        printf("1 - Contacts\n");  
        printf("2 - New contact\n");  
        printf("3 - Remove contact\n");  
        printf("4 - Export agenda to text file\n");  
        printf("5 - Import agenda from text file\n");  
        printf("0 - Exit program\n\n");  
  
        printf("Choose an option:");  
        scanf(" %i", &choice);  
  
        switch (choice) {  
            case 1:  
                contactList();  
                break;  
            case 2:  
                addContact();  
                break;  
            case 3:  
                removeContact();  
                break;  
            case 4:  
                exportAgenda();  
                break;  
            case 5:  
                importAgenda();  
                break;  
            case 0:  
                printf("\nGoodbye!!!\n");  
                break;  
            default:  
                printf("Option not registered");  
        }  
    } while (choice != 0);  
  
  
    return 0;  
}  
  
void contactList() {  
    FILE * file = fopen("agenda.dat", "rb");  
    typePerson person;  
    int i = 1;  
    //char type[MAX];  
    while (fread(&person, sizeof(typePerson), 1, file)) {  
        printf("%i;%s;%s;%s;%i;%s\n", i, person.name, person.surname, person.phone, person.age,  
               person.type);  
        i++;  
    }    fclose(file);  
}  
  
void addContact() {  
    FILE * file = fopen("agenda.dat", "ab");  
    typePerson p;  
    printf("Name:");  
    scanf(" %s", p.name);  
  
    printf("\nSurname:");  
    scanf(" %s", p.surname);  
  
    printf("\nPhone number (9 digits):");  
    scanf(" %s", p.phone);  
  
    printf("\nAge:");  
    scanf(" %i", &p.age);  
  
    printf("\nType of contact (FAVOURITE, WORK or ACQUAINTANCE):");  
    scanf(" %s", p.type);  
  
    fwrite(&p, sizeof(typePerson), 1, file);  
  
    printf("\nContact added successfully\n");  
  
    fclose(file);  
}  
  
void removeContact() {  
    FILE *file = fopen("agenda.dat", "rb");  
    FILE *temp = fopen("temp.dat", "wb");  
  
    typePerson person;  
  
    int num, i;  
    i = 1;  
    printf("Index of the person to remove:");  
    scanf(" %i", &num);  
        while (fread(&person, sizeof(typePerson), 1, file)) {  
        if (i != num) {  
            fwrite(&person, sizeof(typePerson),1, temp);  
        }        i++;  
    }  
    printf("\nContact deleted succesfully\n");  
  
    fclose(file);  
    fclose(temp);  
    remove("agenda.dat");  
    rename("temp.dat", "agenda.dat");  
}  
  
void exportAgenda() {  
    FILE *file = fopen("agenda.dat", "rb");  
    FILE *export;  
    char filename[50];  
    printf("Name of the text file:");  
    scanf(" %s", filename);  
    export = fopen(filename, "w");  
    typePerson person;  
    int i = 1;  
    while (fread(&person, sizeof(typePerson), 1, file)) {  
        fprintf(export, "%i;%s;%s;%s;%i;%s\n", i, person.name, person.surname, person.phone,  
                person.age, person.type);  
        i++;  
    }  
    printf("\nAgenda exported successfully to %s\n", filename);  
  
    fclose(file);  
    fclose(export);  
}  
  
void importAgenda() {  
    FILE * file = fopen("agenda.dat", "w+");  
    FILE * import;  
    char filename[MAX];  
    printf("File you want to import the agenda from:");  
    scanf(" %s", filename);  
    import = fopen(filename, "r");  
    typePerson person;  
    char line[255];  
    int index = 0;  
    while (fgets(line, sizeof(line), import)) {  
        sscanf(line, "%i;%[^;];%[^;];%[^;];%i;%s", &index, person.name, person.surname, person.phone,  
               &person.age, person.type);  
        fwrite(&person, sizeof(typePerson), 1, file);  
    }  
    printf("\nAgenda imported successfully from %s\n", filename);  
  
    fclose(file);  
    fclose(import);  
}
```

¡Gracias por leerme! :) 
