
> [!NOTE] Propósito de la práctica
> Crear un programa que gestione una agenda con datos de contacto de diferentes personas. Los datos a guardar son sus nombres, apellidos, teléfono, edad y el tipo de contacto. Este último campo solo podrá tomar los valores "FAVORITO", "CONOCIDO" y "TRABAJO". 
>
> Se deben definir estructuras adecuadas. Guardaremos los datos en memoria y por tanto, la agenda debe estar vacía al inicio.
> 
> Si lo deseas, puedes usar todas las funciones auxiliares que quieras. Se recomienda sin embargo hacer la práctica con memoria dinámica.
>
>Vamos a dividir el trabajo en dos ejercicios: el menú principal y las opciones del listado de personas, nuevas personas o el borrar personas.

#### Acercamiento a la práctica

Para poder enseñar cómo hacer esta práctica de una forma didáctica y útil (lo más importante), es mejor dividir este contenido en diferentes partes:

- `Estructuras y preparación` Vamos primero a crear todo lo que es más fácil pensar desde un principio: los valores que necesitamos.
- `Agenda` Es importante tener una buena función que nos conciba un espacio donde trabajar. 
- `Imprimir tipo de contacto` Esta es una bobería de función, pero vamos, que buscamos traducir un número a uno de los valores FAVORITO, CONOCIDO Y TRABAJO. 
- `Lista de contactos` Aquí la cosa ya se pone interesante, es hora de ver cómo podemos visualizar todos nuestros contactos.
- `Añadir contacto` Ahora buscamos la manera de concebir un contacto nuevo.
- `Eliminar contacto` ¿Quieres eliminar de una vez por todas al pesado de Orange? ¡Pues ahora puedes gracias a la implementación de esta función!
- `El menú principal` En este punto termina nuestra andadura por esta práctica, aquí recolectamos todo lo que he expuesto en esta práctica y hacemos un programa final capaz de ser usado.

#### Estructuras y preparación 

Uno tiene que estar bien preparado para lo que se avecina, así que vamos a buscar cómo. 

Primero, sabemos que tenemos tres tipos de valores exclusivamente para la variable `Tipo de contacto` por tanto, ¿qué necesitamos? pues un *enum* que nos deje nombrar los únicos tres valores que puede tener esta variable.

```
enum contactType {  
    FAVOURITE, // FAVORITO == 0
    ACQUAINTANCE, // CONOCIDO == 0
    WORK  // TRABAJO == 0
};
```

Así de fácil ya tenemos todos nuestros valores. Pero nos falta aún lo más interesante, un *struct* que nos de todos los posibles campos que tenga nuestra personita de la lista de contactos (que ya sabemos que tenemos su nombre, su apellido, su número de teléfono, dónde guarda los objetos de valor, su edad y el tipo de contacto que es). Por lo tanto, implementemos ese mismo struct:

```
#define MAX 30

typedef struct {  
    char name[MAX];  
    char surname[MAX];  
    char phoneNumber[9];  
    int age;  
    enum contactType typeContact;  
} peopleType;
```

Ahora sí que sí... Bueno no, nos falta uno más, un tipo para nuestra agenda. ¿Por qué? Pues para declarar dos cosas muy importantes:
1. Un vector que tenga a todas nuestras personas en cada instancia del vector.
2. El número de personas que tenemos en nuestro vector (tamaño máximo del mismo es decir)

```
typedef struct {  
    peopleType * people;  
    int numPeople;  
} agendaType;
```

Y ahora sí que sí, tenemos todo. Si hay algo que no se entiende, te recomiendo revisar el [[Tema 8 - Tipos enumerados y registros]] donde tengo más información sobre todo lo que acabo de usar.

#### Agenda

Para nuestra agenda vamos a crear una función que se llame `creAgenda` que nos garantice que desde que encendamos el programa tengamos una agenda (en nuestro caso vacía) ya preparada para interactuar con ella. Por supuesto, vamos a hacerla con memoria dinámica.

```
#define LIST_SIZE 50

// Crear una función a partir de un struct ya creado en el apartado anterior
agendaType createAgenda();

agendaType createAgenda() {  
    agendaType agenda;  
  
    // Ponemos el número de personas con el que empezamos a 0 
    agenda.numPeople = 0; 
    
    // Hacemos la lista inicial con la función malloc de la librería stdlib    
    agenda.people = malloc(sizeof(peopleType) * LIST_SIZE);  
    if (agenda.people == NULL) {  
        printf("ERROR"); 
        agenda.numPeople = -1;  
        return agenda;  
    }  
  
    /*  Esto es para probar un caso donde tengamos un contacto ya por defecto
    // Comandos de la librería string.h que concatenan strings
    strcpy(agenda.people[0].name, "Antoine");                                        strcpy(agenda.people[0].surname, "Benitez");                                     strcpy(agenda.people[0].phoneNumber, "654356465");    
    agenda.people[0].age = 11;    
    agenda.people[0].typeContact = FAVOURITE;    

	// Aumentamos el número de contactos que tenemos
	agenda.numPeople++;

    */  

	// Tenemos que devolver la agenda porque si no, no tenemos nada con lo cual      trabajar a posteriori
	return agenda;  
}
```

Bien, teniendo toda nuestra función que crea la agenda, ya podríamos implementarla en un main que trataremos al final de este documento (ya que estamos yendo paso por paso).
#### Imprimir tipo de contacto

Esta función es una bobada, vamos a hacerla en nada:

```
// Definimos la función que es
char * printContactType(enum contactType);

char * printContactType(enum contactType contact) {  
	// Hacemos un switch interno donde a cada valor que tengamos, pues               devolvemos exactamente lo que le corresponde
    switch (contact) {  
        case FAVOURITE: return "FAVOURITE";  
        case ACQUAINTANCE: return "ACQUAINTANCE";  
        case WORK: return "WORK";  
        default: return "UNKNOWN";  
    }  
}
```

Así de fácil es esta función, no tiene ciencia.


#### Lista de contactos

Vale esta sí que tiene un poco más de truco, pero nada fuera de este mundo. Veamos su código:

```
void contactList(agendaType agenda) {  
    printf("\n");  
    for (int i = 0; i < agenda.numPeople; ++i) {  
        printf("%i --> %s;%s;%s;%i;%s", i+1, agenda.people[i].name,                             agenda.people[i].surname,  
               agenda.people[i].phoneNumber, agenda.people[i].age,  
               printContactType(agenda.people[i].typeContact));  
        printf("\n");  
    }  
    printf("\n");  
}
```

Aquí ahora cobra sentido la función tan fácil que habíamos construido justo antes: el darle el valor verdadero al tipo de contacto, pues como sabemos del tema 8, lo que tenemos si el contacto es de tipo favorito es un 0, no la string "FAVORITO" con lo cual tenemos que valernos de esta función `imprimeTipoContacto` para dar el valor verdadero. 

Por lo demás, tenemos que simplemente ir accediendo a los diferentes campos de cada contacto e ir poniéndolos de forma ordenada en un printf, respetando los direccionamientos para que C no se queje.

#### Añadir contacto

El añadir contacto y el eliminarlo se puede hacer de mil maneras diferentes, veamos la que yo he llevado a cabo: 

```
agendaType addContact(agendaType agenda);

agendaType addContact(agendaType agenda) {  
    if (agenda.numPeople >= LIST_SIZE) {  
        printf("You can't add more contacts");  
        agenda.numPeople = -1;  
        return agenda;  
    }  
  
	// Definimos una nueva persona haciendo una nueva variable temporal para esa     persona basada en nuestro struct de tipo de persona que hicimos al principio     de la práctica
    peopleType newPerson;  
  
    // Lo siguiente es solamente preguntar por datos del contacto  
  
    printf("Give me the name:");  
    scanf(" %s", newPerson.name);  
  
    printf("\n");  
  
    printf("Give me the surname:");  
    scanf(" %s", newPerson.surname);  
  
    printf("\n");  
  
    printf("Give me their phone number (9 digits):");  
    scanf(" %s", newPerson.phoneNumber);  
  
    printf("\n");  
  
    printf("How old are them?:");  
    scanf(" %i", &newPerson.age);  
  
    printf("\n");  
  
    printf("Which type of contact is he/she? (0 = FAVOURITE, 1 = ACQUAINTANCE, 2 = WORK):");  
    scanf(" %d", &newPerson.typeContact);  
  
    // Ahora, añadimos a esa persona que acabamos de describir a la agenda para      posteriormente aumentar el número de personas que tenemos en nuestros            contactos
    agenda.people[agenda.numPeople] = newPerson;  
    agenda.numPeople++;  

	// Devolvemos la agenda para que no se nos pierda el nuevo contacto añadido
    return agenda;  
}
```

Bien, esto ya está acabado. Me gustaría explicar en profundidad cómo sirve el añadir una nueva persona de esta manera. 

Como podemos ver, tenemos que una vez definidos todos los valores de `newPerson` pues ya nos queda meterla en la agenda de verdad. Lo que hacemos es que usamos el número de contactos que tenemos hasta el momento. Esto funciona porque imagina que tenemos 2 contactos, entonces la nueva persona se añadirá en el vector en la posición 2 del mismo, dejando la posición 0 y 1 (recordamos como funcionan las listas, arrays y demás en programación) con sus respectivos contactos intactos. Luego se aumenta el número de contactos a 3, permitiendo añadir a uno nuevo en esa posición y teniendo además una referencia de todos los contactos reales que tenemos.

#### Eliminar un contacto

Bien, toca eliminar a esa persona que nos cae mal. Vamos a ver cómo lo he hecho yo (puedes tomarte la libertad de buscar más soluciones, así es más divertido): 

```
agendaType removeContact(agendaType agenda) {  
    int index, choice;  
    if (agenda.numPeople == 0) {  
        printf("Nothing to erase, the agenda is empty, you have no contacts");  
        printf("\n");  
        return agenda;  
    }  
  
    // Una advertencia pues por qué no
    printf("WARNING: What you are about to do has no turn around, there won't be     any way of recovering this contact, are you sure about this? (0 = No, 1 =        "Yes)");  
    scanf(" %i", &choice);  
    printf("\n");  

    if (choice != 0) {  
        printf("Which contact do you want to delete?");  
        scanf(" %i", &index);  
  
        printf("\n");  
  
        // Si no damos un índice válido, pues poco podemos borrar 
        if (index < 1 || index > agenda.numPeople) {  
            printf("ERROR: Value not valid\n");  
            return agenda;  
        }  
  
        for (int i = index; i < agenda.numPeople;++i) {  
            agenda.people[i-1] = agenda.people[i];  
        }  
  
        // Disminuimos el número de personas en nuestra lista de contactos 
        agenda.numPeople--;  
    }  
  
    return agenda;  
}
```

Vale, aquí solo hay una cosa que comentar -> ¿Cómo sirve el *for* que borra a las personas de la agenda? Pues muy simple, imagina que queremos borrar a un tal Rumán que está en la posición 5 (en el vector 4, recuerda como va esto) y que justo delante está el bueno de Pueblo. Pues bien, muy fácil, cogemos la posición de Rumán que ya dimos `index = 5` y hacemos que su lugar en el vector (la posición 4 pues i - 1 siendo i = 5 da 4) sea aplastada por la posición de Pueblo. 

Es decir, cogemos al bueno de Pueblo, tomamos sus datos y metemos a Pueblo en la posición de Rumán, sobrescribiendo todos sus datos, de manera que son borrados y Pueblo se mueve a la posición 5 (en el vector 4) y su antigua posición 6 (vector 5) queda eliminada posteriormente.

#### El menú principal

Bueno, veamos cómo se cohesiona todo en un *main* súper bonico: 

```
int main() {  
    int choice;  

	// Iniciamos una agenda vacía antes que nada
    agendaType agenda = createAgenda();  

	// Vamos a hacer el menú dentro de un DO-WHILE!!
    do {    
        printf("\n");  
        printf("----- MENU -----\n");  
        printf("1 - Contacts\n");  
        printf("2 - Add contact\n");  
        printf("3 - Delete contact\n");  
        printf("0 - Exit\n");  
        printf("\n");  
        printf("Choose an option (0-3):");  
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
            case 0:  
                printf("\nGoodbye!\n");  
            default:  
                printf("Noup! Not an option!");  
        }  
    } while (choice != 0);  
  
    // Liberamos la memoria -> Muy aconsejable  
    free(agenda.people);  
  
    return 0;  
}
```

Pues aquí lo tenemos, nuestro precioso *main*. Cabe destacar que en toda posición que se tome una opción igualamos la agenda a la función para que se guarden los valores y nunca perdamos información preciada. 

Y poco más hay que comentar aquí, es un programa bastante básico. Veamos cómo sería ensamblado final (lo que te facilita el copy paste básicamente).


## Programa final

Aquí poco queda que decir, vamos a verlo del tirón:

```
#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
  
#define MAX 30  
#define LIST_SIZE 50  
  
// Basic enum that defines all the values that the variable contactType can have  
enum contactType {  
    FAVOURITE,  
    ACQUAINTANCE,  
    WORK  
};  
  
// Struct for our people  
typedef struct {  
    char name[MAX];  
    char surname[MAX];  
    char phoneNumber[9];  
    int age;  
    enum contactType typeContact;  
} peopleType;  
  
// Struct for our agenda type  
typedef struct {  
    peopleType * people;  
    int numPeople;  
} agendaType;  
  
// We need a function through which we can create our agenda  
agendaType createAgenda();  
  
// Function to print the contact type  
char * printContactType(enum contactType);  
  
// Feature of seeing your current contacts  
void contactList(agendaType agenda);  
  
// Feature of adding contacts  
agendaType addContact(agendaType agenda);  
  
// Feature of removing contacts  
agendaType removeContact(agendaType agenda);  
  
int main() {  
    int choice;  
  
    agendaType agenda = createAgenda();  
    // Test to see if value we initialized with is actually there  
    // printf("%s", agenda.people[1].surname);  
    do {  
        // We initialize the actual menu  
        printf("\n");  
        printf("----- MENU -----\n");  
        printf("1 - Contacts\n");  
        printf("2 - Add contact\n");  
        printf("3 - Delete contact\n");  
        printf("0 - Exit\n");  
        printf("\n");  
        printf("Choose an option (0-3):");  
        scanf(" %i", &choice);  
        switch (choice) {  
            case 1:  
                contactList(agenda);  
                break;            case 2:  
                agenda = addContact(agenda);  
                break;            case 3:  
                agenda = removeContact(agenda);  
                break;            case 0:  
                printf("\nGoodbye!\n");  
            default:  
                printf("Noup! Not an option!");  
        }  
    } while (choice != 0);  
  
    // We free our contacts before leaving and therefore, this program is of single usage  
    free(agenda.people);  
  
    return 0;  
}  
  
agendaType createAgenda() {  
    agendaType agenda;  
  
    // We start setting the number of people we have in our agenda to zero  
    agenda.numPeople = 0; // In case you wanted to have some people from the beginning,  
    // you must increase this number  
    // Let's make an initial list of a size we defined previously using dinamic memory    agenda.people = malloc(sizeof(peopleType) * LIST_SIZE);  
    if (agenda.people == NULL) {  
        printf("ERROR");  
        agenda.numPeople = -1;  
        return agenda;  
    }  
  
    /*  
    strcpy(agenda.people[0].name, "Antoine");    strcpy(agenda.people[0].surname, "Benitez");    strcpy(agenda.people[0].phoneNumber, "619249465");    agenda.people[0].age = 11;    agenda.people[0].typeContact = FAVOURITE;    */  
    return agenda;  
}  
  
void contactList(agendaType agenda) {  
    printf("\n");  
    for (int i = 0; i < agenda.numPeople; ++i) {  
        printf("%i --> %s;%s;%s;%i;%s", i+1, agenda.people[i].name, agenda.people[i].surname,  
               agenda.people[i].phoneNumber, agenda.people[i].age,  
               printContactType(agenda.people[i].typeContact));  
        printf("\n");  
    }  
    printf("\n");  
}  
  
char * printContactType(enum contactType contact) {  
    switch (contact) {  
        case FAVOURITE: return "FAVOURITE";  
        case ACQUAINTANCE: return "ACQUAINTANCE";  
        case WORK: return "WORK";  
        default: return "UNKNOWN";  
    }  
}  
  
agendaType addContact(agendaType agenda) {  
    if (agenda.numPeople >= LIST_SIZE) {  
        printf("You can't add more contacts");  
        agenda.numPeople = -1;  
        return agenda;  
    }  
  
    // We can define a new person simply via using our peopleType, and later add it to the actual agenda  
    peopleType newPerson;  
  
    // The following code is simply asking for data about the new contact  
  
    printf("Give me the name:");  
    scanf(" %s", newPerson.name);  
  
    printf("\n");  
  
    printf("Give me the surname:");  
    scanf(" %s", newPerson.surname);  
  
    printf("\n");  
  
    printf("Give me their phone number (9 digits):");  
    scanf(" %s", newPerson.phoneNumber);  
  
    printf("\n");  
  
    printf("How old are them?:");  
    scanf(" %i", &newPerson.age);  
  
    printf("\n");  
  
    printf("Which type of contact is he/she? (0 = FAVOURITE, 1 = ACQUAINTANCE, 2 = WORK):");  
    scanf(" %d", &newPerson.typeContact);  
  
    // We now add the person we just described to the agenda, and lastly, we increase the amount of people we have  
    agenda.people[agenda.numPeople] = newPerson;  
    agenda.numPeople++;  
  
    return agenda;  
}  
  
agendaType removeContact(agendaType agenda) {  
    int index, choice;  
    if (agenda.numPeople == 0) {  
        printf("Nothing to erase, the agenda is empty, you have no contacts");  
        printf("\n");  
        return agenda;  
    }  
  
    // A warning just for fun  
    printf("WARNING: What you are about to do has no turn around, there won't be any way of recovering this "  
           "contact, are you sure about this? (0 = No, 1 = Yes)");  
    scanf(" %i", &choice);  
    printf("\n");  
  
    if (choice != 0) {  
        printf("Which contact do you want to delete?");  
        scanf(" %i", &index);  
  
        printf("\n");  
  
        // If we give the wrong range of value, we can't do anything  
        if (index < 1 || index > agenda.numPeople) {  
            printf("ERROR: Value not valid\n");  
            return agenda;  
        }  
  
        // Now, what we do is we actually take the person that is desired to be deleted by the user, and smash its data  
        // via overwriting right onto all his/her index        for (int i = index; i < agenda.numPeople;++i) {  
            agenda.people[i-1] = agenda.people[i];  
        }  
  
        // We decrease the total amount of people in our list  
        agenda.numPeople--;  
    }  
  
    return agenda;  
}

```

Y con esto poco más queda por decir. ¡Gracias por leerme!


