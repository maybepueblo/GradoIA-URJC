//
// Created by pablo on 5/9/2024.
//

#ifndef PRACTICE5_ARRAYPLUSTAD_H
#define PRACTICE5_ARRAYPLUSTAD_H

typedef struct {
    int *array;
    int size;
    int count;
} ArrayPlusTAD;

ArrayPlusTAD *createArrayPlus(int size);

// Adds a new element to our array
int addElement(ArrayPlusTAD *myArrayPlus, int element);

// Checks element that aren't already in our array and adds them
void addArray(ArrayPlusTAD *myArrayPlus, int *arrayElements, int numNewElements);

// Shows our array
void printArrayPlus(ArrayPlusTAD *myArrayPlus);

// Empties our array
void emptyArrayPlus(ArrayPlusTAD *myArrayPlus);

// Frees the memory occupied by our array
void freeArrayPlus(ArrayPlusTAD *myArrayPlus);

#endif //PRACTICE5_ARRAYPLUSTAD_H
