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
    }
    printf("\n");
}

char *showType(enum contactType type) {
    switch (type) {
        case FAVOURITE: return "FAVOURITE";
        case ACQUAINTANCE: return "ACQUAINTANCE";
        case WORK: return "WORK";
        default: return "UNKNOWN";
    }
}

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
    agenda.people = realloc(agenda.people, sizeof(personData) * (agenda.numPeople - 1));

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
        }
        fclose(file);
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




