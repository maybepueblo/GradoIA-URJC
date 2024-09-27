#include <iostream>
#include "Persona.h"
//#include "Agenda.h"

int main() {
    /*Persona *p = new Persona("Pablo", "Garcia Perez");
    std::cout << p -> toString();
    */

    int choice = 0;

    do {
        printf("\n --- MENU --- \n");
        printf(" 1 - Contacts\n");
        printf(" 2 - New contact\n");
        printf(" 3 - Delete contact\n");
        printf(" 0 - Exit\n\n");

        printf("Choose an option:");
        scanf(" %i", &choice);

        switch (choice) {
            default:
                printf("Wrong choice");
        }

    } while (choice != 0);

    return 0;
}