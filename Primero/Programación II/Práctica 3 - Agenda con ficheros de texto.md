
> [!NOTE] Propósito de la práctica
> En este caso toca ampliar un poco en lo que habíamos realizado anteriormente para nuestra [[Práctica 2 - Agenda]]. 
> 
> En pos de ampliar un poco todo el contenido, tenemos un menú mejorado que ahora nos permite guardar la agenda de contactos de un fichero de texto y también nos permite leer el contenido de la agenda que tengamos en el fichero de texto. 
> 
> Esta opción guardar fichero pedirá al usuario el nombre del fichero donde se guardará el listado y escribirá la información en él en formato texto en base al mismo formato de la lista de personas. 
> 
> En contraposición, la opción de leer la agenda desde un fichero de texto pedirá al usuario el nombre del fichero. Deberemos controlar los posibles errores con el fichero. Cabe destacar que si existen datos en memoria se sobrescribiran los mismos, con lo cual hemos de notificar al usuario de esta posibilidad.

Para hacer un poco más amena la digestión de esta práctica, nuevamente voy a desglosar un poco los apartados que vamos a hacer, cabe denotar que no me voy a parar tanto en algunas cosas, puesto que la mayoría de las funciones que tenemos que hacer en esta práctica son idénticas a las utilizadas en la [[Práctica 2 - Agenda]]. Sin más dilación, veamos el desglose:

- `Menú principal` -> Nuevamente, muy importante para brindar al usuario la interfaz de sus sueños. 
- `Preparación previa` -> Estructuras, tipos enumerados, la función que imprime el tipo de enumerado que tenemos y la agenda con memoria dinámica.
-  `Funciones varias` -> Este apartado se refiere a las funciones que ya expliqué en su momento en los apuntes de la práctica 2, por lo cual aquí solamente se volverá a brindar el código de los mismos, pero no se explicará nada.
- `Guardar agenda` -> Aquí empieza lo importante, esta función nos permitirá crear un fichero de texto en pos de guardar nuestros contactos. 
- `Leer agenda` -> En esta, un poco más tediosa, tenemos que dar al usuario la posibilidad de leer un fichero que ya tenga ciertos contactos en él.

Una vez visto todo lo que vamos a hacer, es hora de empezar. 

#### Menú principal

```
int main() {  
    int choice;  
  
    agendaType agenda = createAgenda();  
  
    do {  
        printf("\n");  
        printf("---- MENU ----\n");  
        printf("1 - Contacts\n");  
        printf("2 - Add contact\n");  
        printf("3 - Remove contact\n");  
        printf("4 - Save contacts in a text file\n");  
        printf("5 - Read contacts from a text file\n");  
        printf("0 - Exit\n");  
  
        printf("\n");  
  
        printf("Choose an option:");  
        scanf(" %i", &choice);  
  
        switch (choice) {  
            case 1:  
                contactList(agenda);  
                break;  
            case 2:  
                agenda = addContact(agenda);  
                break;  
            case 3:  
                agenda = removeContact(agenda);  
                break;  
            case 4:  
                agenda = saveContact(agenda);  
                break;  
            case 5:  
                agenda = readContact(agenda);  
                break;  
            case 0:  
                printf("\nGoodbye!!!\n");  
                break;  
            default:  
                printf("Not a valid option");  
        }  
    } while (choice != 0);  
  
  
    free(agenda.people);  
  
    return 0;  
}
```

Poca cosa he cambiado, ahora solo hemos añadido dos opciones más que son las de guardar el fichero o la de leerlo.

#### Preparación previa

En esta fase tampoco voy a añadir nada, veamos de seguido todo lo que necesitamos tener para facilitar el programa:

```
#define MAX 30  
#define LIST_MAX 50

// Tipos de contactos
enum contactType {  
    FAVOURITE,  
    ACQUAINTANCE,  
    WORK  
};  

// Datos referentes a una persona
typedef struct {  
    char name[MAX];  
    char surname[MAX];  
    char phoneNum[9];  
    int age;  
    enum contactType type;  
} personData;  

// Struct de la agenda
typedef struct {  
    personData * people;  
    int numPeople;  
} agendaType;

// Función que incializa la agenda con memoria dinámica
agendaType createAgenda() {  
    agendaType agenda;  
  
    // Initialize the number of people to zero  
    agenda.numPeople = 0;  
  
    agenda.people = malloc(sizeof(personData) * LIST_MAX);  
    if (agenda.people == NULL) {  
        printf("ERROR: Fatal memory exception");  
        agenda.numPeople = -1;  
        return agenda;  
    }  
  
    strcpy(agenda.people[0].name, "Andrea");  
    strcpy(agenda.people[0].surname, "Espinosa");  
    strcpy(agenda.people[0].phoneNum, "619249465");  
    agenda.people[0].age = 11;  
    agenda.people[0].type = 0;  
    agenda.numPeople++;  
  
  
    return agenda;  
}

// Función que enseña el tipo de contacto por pantalla
char *showType(enum contactType type) {  
    switch (type) {  
        case FAVOURITE: return "FAVOURITE";  
        case ACQUAINTANCE: return "ACQUAINTANCE";  
        case WORK: return "WORK";  
        default: return "UNKNOWN";  
    }}
```

#### Funciones varias

Vamos a recorrer muy rápidamente y sin detenernos en ninguna las funciones que conforman nuestras funciones principales: ver la agenda de contactos, añadir uno nuevo o eliminarlo:

##### Ver la agenda de contactos

```
void contactList(agendaType agenda) {  
    if (agenda.numPeople == 0) {  
        printf("\n");  
        printf("No contacts to show!!!");  
        printf("\n");  
        exit(-1);  
    }  
    printf("\n");  
    for (int i = 0; i < agenda.numPeople; ++i) {  
        printf("%i -> %s;%s;%s;%i;%s", i+1, agenda.people[i].name, agenda.people[i].surname,  
               agenda.people[i].phoneNum, agenda.people[i].age, showType(agenda.people[i].type));  
        printf("\n");  
    }    printf("\n");  
}
```



##### Añadir contacto

```
agendaType addContact(agendaType agenda) {  
    if (agenda.numPeople >= LIST_MAX) {  
        printf("You can't add any more contacts!");  
    }  
    personData newPerson;  
  
    printf("Name:");  
    scanf(" %s", newPerson.name);  
  
    printf("Surname:");  
    scanf(" %s", newPerson.surname);  
  
    printf("Phone number (9 digits only):");  
    scanf(" %s", newPerson.phoneNum);  
  
    printf("Age:");  
    scanf(" %i", &newPerson.age);  
  
    printf("Contact type (Favourite = 0, Acquaintance = 1, Work = 2):");  
    scanf(" %i", &newPerson.type);  
  
    agenda.people[agenda.numPeople] = newPerson;  
    agenda.numPeople++;  
  
    return agenda;  
}
```

##### Eliminar contacto

```
agendaType removeContact(agendaType agenda) {  
    if (agenda.numPeople == 0) {  
        printf("You can't erase anyone because there are no contacts!");  
        agenda.numPeople = -1;  
        return agenda;  
    }  
    int choice, index;  
    printf("WARNING: Are you sure about deleting a certain contact? (NO = 0):");  
    scanf(" %i", &choice);  
  
    if (choice != 0) {  
        printf("Tell me the position you want to delete:");  
        scanf(" %i", &index);  
  
        for (int i = index; i < agenda.numPeople; ++i) {  
            agenda.people[i-1] =  agenda.people[i];  
        }  
        agenda.numPeople--;  
  
    }  
    return agenda;  
}
```


#### Guardar contactos

Ahora empezamos con lo bueno, vamos a ver primero el código para luego desglosar lo importante:

```
agendaType saveContact(agendaType agenda) {  
    int choice;  
    char route[LIST_MAX] = "test.txt";  
    printf("Give me the location in which you want to save the agenda (example.txt):");  
    scanf(" %s", route);  

	// Abrimos el archivo en modo lectura para avisar al usuario de si existe ya
    FILE * file = fopen(route, "r");  
    if (file != NULL) {  
        printf("The file already exists, if you proceed now, you will overwrite the content\n");  
        printf("Do you want to continue? (NO = 0):");  
        scanf(" %i", &choice);  
        if (choice == 0) {  
            printf("Goodbye!");  
            exit(1);  
        }        fclose(file);  
    }  
    // Ahora sí que sí creamos el archivo en el que vamos a escribir
    FILE * defFile = fopen(route, "w");  

	// Lo que hacemos aquí es ir tomando los datos de nuestra agenda e ir            imprimiendo poco a poco de la misma manera que lo hacemos en contactList(),      basándonos en el requerimiento de la práctica
    for (int i = 0; i < agenda.numPeople; ++i) {  
        fprintf(defFile, "%i -> %s;%s;%s;%i;%s", i+1, agenda.people[i].name, agenda.people[i].surname,  
                agenda.people[i].phoneNum, agenda.people[i].age, showType(agenda.people[i].type));  
        fprintf(defFile, "\n");  
    }  

	// Importante cerrar el archivo para que se guarden los cambios
    fclose(defFile);  
  
    printf("\n");  
  
    printf("Data saved in %s", route);  
  
    printf("\n");  
  
    return agenda;  
}
```

De las dos funciones nuevas, esta es la que tiene menor complicación. Como podemos ver, lo único que hacemos es recordar cómo escribe la función `contactList()` para esta vez en vez de imprimir por consola, escribir en el file.txt para que de esta manera se quede almacenado en el ordenador. 

Es importante cerrar el archivo al final, pues si no lo cierras, corres el riesgo de que se pierda todo lo que has intentado escribir, además de todos los contactos que posiblemente tuvieses en ese archivo. 

#### Leer contactos

En lo personal, esta fue la más tediosa a la hora de implementar, veamos por qué:

```
agendaType readContact(agendaType agenda) {  
    int choice;  
    printf("Note that any data you have currently stored in memory will be overwritten\n");  
    printf("Do you wish to proceed? (NO = 0):");  
    scanf(" %i", &choice);  
    printf("\n");  
    if (choice == 0) {  
        printf("Farewell, goodbye");  
        agenda.numPeople = -1;  
        return agenda;  
    }  
    char route[MAX];  
    printf("Give me the file you want to read from (example.txt):");  
    scanf(" %s", route);  
  
    FILE * file = fopen(route, "r");  
    if (file == NULL) {  
        printf("That file does not exist");  
        return agenda;  
    }  
    agenda.numPeople = 0;  
  
    char line[255];  
    int index = 0;  
    char type[MAX];  
    while (fgets(line, sizeof(line), file)) {  
        sscanf(line, "%i -> %[^;];%[^;];%[^;];%i;%s", &index, agenda.people[agenda.numPeople].name,  
               agenda.people[agenda.numPeople].surname, agenda.people[agenda.numPeople].phoneNum,  
               &agenda.people[agenda.numPeople].age, type);  
        if (strcmp(type, "FAVOURITE") == 0) {  
            agenda.people[agenda.numPeople].type = FAVOURITE;  
        } else if (strcmp(type, "ACQUAINTANCE") == 0) {  
            agenda.people[agenda.numPeople].type = ACQUAINTANCE;  
        } else if (strcmp(type, "WORK") == 0) {  
            agenda.people[agenda.numPeople].type = WORK;  
        }  
        agenda.numPeople++;  
    }  
    fclose(file);  
  
    printf("\n");  
  
    printf("Contacts read from %s", route);  
  
    printf("\n");  
  
    return agenda;  
}
```

Además de una gran cantidad de mensajes de control tal y como pedía la práctica, en este caso lo importante es el while que incorporamos, vamos a intentar explicarlo un poco. 

Lo que he hecho en esta ocasión es definir un máximo que se pueda leer en línea, es decir unos 255 caracteres (no creo que nadie tenga tanto nombre para llegar a esta abominable cifra pero por si acaso). 

Luego, nos vamos a ayudar de `fgets` una función de C que nos permite leer con cierto límite basándonos en un buffer, que en este caso es la variable *line*. De esta manera, fgets lo que va a hacer es leer hasta que llegue a 254 caracteres o hasta que llegue a un salto de línea, lo cual nos viene de perlas. 

Así, mientras fgets pueda seguir leyendo a lo largo del archivo, vamos a seguir leyendo contactos, pero primero tenemos que preocuparnos de obtener la información de cada contacto. Esto lo vamos a hacer con un `sscanf` que es una función de C que nos permite *parsear*, es decir, obtener los datos de una frase para poder usarlos luego. En este caso leemos todos los datos, incluso el index, pero ese no lo vamos a usar.

El operador `%[^;]` lee hasta que se encuentre con un ";" así que nos viene genial sabiendo el formato que tienen nuestros datos.

Finalmente, lo único a resaltar es que tenemos que hacer una cadena de if para poner el dato apropiado en el tipo de contacto de lo que hemos leído, y ya luego podemos aumentar el número de personas que tenemos.

Con esto y un bizcocho, tenemos implementada la función que más tiempo me tomó (por no darme cuenta de lo del buffer)... ¿Ni tan mal, no?

#### Programa final

Ahora sí, mucho código, vamos a poner todo el programa entero para que puedas hacerle un *copypaste* súper chulo:

```
#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
  
#define MAX 30  
#define LIST_MAX 50  
  
enum contactType {  
    FAVOURITE,  
    ACQUAINTANCE,  
    WORK  
};  
  
typedef struct {  
    char name[MAX];  
    char surname[MAX];  
    char phoneNum[9];  
    int age;  
    enum contactType type;  
} personData;  
  
typedef struct {  
    personData * people;  
    int numPeople;  
} agendaType;  
  
// Function declarations  
agendaType createAgenda();  
void contactList(agendaType agenda);  
char *showType(enum contactType type);  
agendaType addContact(agendaType agenda);  
agendaType removeContact(agendaType agenda);  
agendaType saveContact(agendaType agenda);  
agendaType readContact(agendaType agenda);  
  
int main() {  
    int choice;  
  
    agendaType agenda = createAgenda();  
  
    do {  
        printf("\n");  
        printf("---- MENU ----\n");  
        printf("1 - Contacts\n");  
        printf("2 - Add contact\n");  
        printf("3 - Remove contact\n");  
        printf("4 - Save contacts in a text file\n");  
        printf("5 - Read contacts from a text file\n");  
        printf("0 - Exit\n");  
  
        printf("\n");  
  
        printf("Choose an option:");  
        scanf(" %i", &choice);  
  
        switch (choice) {  
            case 1:  
                contactList(agenda);  
                break;  
            case 2:  
                agenda = addContact(agenda);  
                break;  
            case 3:  
                agenda = removeContact(agenda);  
                break;  
            case 4:  
                agenda = saveContact(agenda);  
                break;  
            case 5:  
                agenda = readContact(agenda);  
                break;  
            case 0:  
                printf("\nGoodbye!!!\n");  
                break;  
            default:  
                printf("Not a valid option");  
        }  
    } while (choice != 0);  
  
  
    free(agenda.people);  
  
    return 0;  
}  
  
agendaType createAgenda() {  
    agendaType agenda;  
  
    // Initialize the number of people to zero  
    agenda.numPeople = 0;  
  
    agenda.people = malloc(sizeof(personData) * LIST_MAX);  
    if (agenda.people == NULL) {  
        printf("ERROR: Fatal memory exception");  
        agenda.numPeople = -1;  
        return agenda;  
    }  
  
    strcpy(agenda.people[0].name, "Andrea");  
    strcpy(agenda.people[0].surname, "Espinosa");  
    strcpy(agenda.people[0].phoneNum, "619249465");  
    agenda.people[0].age = 11;  
    agenda.people[0].type = 0;  
    agenda.numPeople++;  
  
  
    return agenda;  
}  
  
void contactList(agendaType agenda) {  
    if (agenda.numPeople == 0) {  
        printf("\n");  
        printf("No contacts to show!!!");  
        printf("\n");  
        exit(-1);  
    }  
    printf("\n");  
    for (int i = 0; i < agenda.numPeople; ++i) {  
        printf("%i -> %s;%s;%s;%i;%s", i+1, agenda.people[i].name, agenda.people[i].surname,  
               agenda.people[i].phoneNum, agenda.people[i].age, showType(agenda.people[i].type));  
        printf("\n");  
    }    printf("\n");  
}  
  
char *showType(enum contactType type) {  
    switch (type) {  
        case FAVOURITE: return "FAVOURITE";  
        case ACQUAINTANCE: return "ACQUAINTANCE";  
        case WORK: return "WORK";  
        default: return "UNKNOWN";  
    }}  
  
agendaType addContact(agendaType agenda) {  
    if (agenda.numPeople >= LIST_MAX) {  
        printf("You can't add any more contacts!");  
    }  
    personData newPerson;  
  
    printf("Name:");  
    scanf(" %s", newPerson.name);  
  
    printf("Surname:");  
    scanf(" %s", newPerson.surname);  
  
    printf("Phone number (9 digits only):");  
    scanf(" %s", newPerson.phoneNum);  
  
    printf("Age:");  
    scanf(" %i", &newPerson.age);  
  
    printf("Contact type (Favourite = 0, Acquaintance = 1, Work = 2):");  
    scanf(" %i", &newPerson.type);  
  
    agenda.people[agenda.numPeople] = newPerson;  
    agenda.numPeople++;  
  
    return agenda;  
}  
  
agendaType removeContact(agendaType agenda) {  
    if (agenda.numPeople == 0) {  
        printf("You can't erase anyone because there are no contacts!");  
        agenda.numPeople = -1;  
        return agenda;  
    }  
    int choice, index;  
    printf("WARNING: Are you sure about deleting a certain contact? (NO = 0):");  
    scanf(" %i", &choice);  
  
    if (choice != 0) {  
        printf("Tell me the position you want to delete:");  
        scanf(" %i", &index);  
  
        for (int i = index; i < agenda.numPeople; ++i) {  
            agenda.people[i-1] =  agenda.people[i];  
        }  
        agenda.numPeople--;  
  
    }  
    return agenda;  
}  
  
agendaType saveContact(agendaType agenda) {  
    int choice;  
    char route[LIST_MAX] = "test.txt";  
    printf("Give me the location in which you want to save the agenda (example.txt):");  
    scanf(" %s", route);  
  
    FILE * file = fopen(route, "r");  
    if (file != NULL) {  
        printf("The file already exists, if you proceed now, you will overwrite the content\n");  
        printf("Do you want to continue? (NO = 0):");  
        scanf(" %i", &choice);  
        if (choice == 0) {  
            printf("Goodbye!");  
            exit(1);  
        }        fclose(file);  
    }  
    FILE * defFile = fopen(route, "w");  
  
    for (int i = 0; i < agenda.numPeople; ++i) {  
        fprintf(defFile, "%i -> %s;%s;%s;%i;%s", i+1, agenda.people[i].name, agenda.people[i].surname,  
                agenda.people[i].phoneNum, agenda.people[i].age, showType(agenda.people[i].type));  
        fprintf(defFile, "\n");  
    }  
    fclose(defFile);  
  
    printf("\n");  
  
    printf("Data saved in %s", route);  
  
    printf("\n");  
  
    return agenda;  
}  
  
agendaType readContact(agendaType agenda) {  
    int choice;  
    printf("Note that any data you have currently stored in memory will be overwritten\n");  
    printf("Do you wish to proceed? (NO = 0):");  
    scanf(" %i", &choice);  
    printf("\n");  
    if (choice == 0) {  
        printf("Farewell, goodbye");  
        agenda.numPeople = -1;  
        return agenda;  
    }  
    char route[MAX];  
    printf("Give me the file you want to read from (example.txt):");  
    scanf(" %s", route);  
  
    FILE * file = fopen(route, "r");  
    if (file == NULL) {  
        printf("That file does not exist");  
        return agenda;  
    }  
    agenda.numPeople = 0;  
  
    char line[255];  
    int index = 0;  
    char type[MAX];  
    while (fgets(line, sizeof(line), file)) {  
        sscanf(line, "%i -> %[^;];%[^;];%[^;];%i;%s", &index, agenda.people[agenda.numPeople].name,  
               agenda.people[agenda.numPeople].surname, agenda.people[agenda.numPeople].phoneNum,  
               &agenda.people[agenda.numPeople].age, type);  
        if (strcmp(type, "FAVOURITE") == 0) {  
            agenda.people[agenda.numPeople].type = FAVOURITE;  
        } else if (strcmp(type, "ACQUAINTANCE") == 0) {  
            agenda.people[agenda.numPeople].type = ACQUAINTANCE;  
        } else if (strcmp(type, "WORK") == 0) {  
            agenda.people[agenda.numPeople].type = WORK;  
        }  
        agenda.numPeople++;  
    }  
    fclose(file);  
  
    printf("\n");  
  
    printf("Contacts read from %s", route);  
  
    printf("\n");  
  
    return agenda;  
}
```

Listo, a por la siguiente práctica.

¡Gracias por leer! ;)