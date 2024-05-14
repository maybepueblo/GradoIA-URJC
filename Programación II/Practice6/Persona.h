//
// Created by pablo on 4/19/2024.
//

#ifndef PRACTICA6_PERSONA_H
#define PRACTICA6_PERSONA_H
#define MAX_CHAR 30

typedef enum {
    FAVOURITE,
    ACQUAINTANCE,
    WORK
} contactType;

// You can also write the enum this way
/*
 * enum ContactType {
 *      FAVOURITE,
 *      ACQUAINTANCE,
 *      WORK
 * };
 */

class Persona {
    private:
        char name[MAX_CHAR];
        char surname[MAX_CHAR];
        /*int age{};
        char phone_number[9]{};
        contactType type;
        */
    public:
        // Constructor
        Persona(char *nom, char *sur_nom);
        char * toString();
        // Getters

};


#endif //PRACTICA6_PERSONA_H
