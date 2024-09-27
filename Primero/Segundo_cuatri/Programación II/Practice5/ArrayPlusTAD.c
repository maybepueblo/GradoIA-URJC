//
// Created by pablo on 5/9/2024.
//

#include "ArrayPlusTAD.h"
#include <stdio.h>

#include <stdlib.h>

ArrayPlusTAD *createArrayPlus(int size) {
    ArrayPlusTAD *myArrayPlus = malloc(sizeof(ArrayPlusTAD));
    myArrayPlus->array = malloc(size * sizeof(int));
    myArrayPlus->size = size;
    myArrayPlus->count = 0;
    return myArrayPlus;
}

int addElement(ArrayPlusTAD *myArrayPlus, int element) {
    if (myArrayPlus->count < myArrayPlus->size) {
        myArrayPlus->array[myArrayPlus->count++] = element;
        return 0;
    } else {
        printf("No room for more elements\n");
        return -1;
    }
}

void addArray(ArrayPlusTAD *myArrayPlus, int *arrayElements, int numNewElements) {
    for (int i = 0; i < numNewElements; ++i) {
        if (addElement(myArrayPlus, arrayElements[i]) == -1) {
            break;
        }
    }
}

void printArrayPlus(ArrayPlusTAD *myArrayPlus) {
    for (int i = 0; i < myArrayPlus->count; ++i) {
        printf("Element %i -> %i\n", i+1, myArrayPlus->array[i]);
    }
}

void emptyArrayPlus(ArrayPlusTAD *myArrayPlus) {
    myArrayPlus->count = 0;
    printf("Array successfully emptied\n");
}

void freeArrayPlus(ArrayPlusTAD *myArrayPlus) {
    free(myArrayPlus->array);
    free(myArrayPlus);
    printf("Array successfully freed\n");
}

