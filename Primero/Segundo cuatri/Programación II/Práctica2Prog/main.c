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

    // We free our contacts before leaving and therefore, this program is of single usage
    free(agenda.people);

    return 0;
}

agendaType createAgenda() {
    agendaType agenda;

    // We start setting the number of people we have in our agenda to zero
    agenda.numPeople = 0; // In case you wanted to have some people from the beginning,
    // you must increase this number

    // Let's make an initial list of a size we defined previously using dinamic memory
    agenda.people = malloc(sizeof(peopleType) * LIST_SIZE);
    if (agenda.people == NULL) {
        printf("ERROR");
        agenda.numPeople = -1;
        return agenda;
    }

    /*
    strcpy(agenda.people[0].name, "Antoine");
    strcpy(agenda.people[0].surname, "Benitez");
    strcpy(agenda.people[0].phoneNumber, "619249465");
    agenda.people[0].age = 11;
    agenda.people[0].typeContact = FAVOURITE;
    */

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
        // via overwriting right onto all his/her index
        for (int i = index; i < agenda.numPeople;++i) {
            agenda.people[i-1] = agenda.people[i];
        }

        // We decrease the total amount of people in our list
        agenda.numPeople--;
    }

    return agenda;
}
