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
    }
    fclose(file);
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
        }
        i++;
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

