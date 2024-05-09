#include "ArrayPlusTAD.h"
#include <stdio.h>

#define SIZE 5

int main() {
    /* Basic testing code
    ArrayPlusTAD *array = createArrayPlus(6);
    int arrayTest[5] = {1, 2, 3, 4, 5};
    addArray(array, arrayTest, 5);
    printArrayPlus(array);
    */

    // Major test of our program functions

    // Creates an empty array
    ArrayPlusTAD *myArrayPlus = createArrayPlus(SIZE * 2);

    // Fills our array with individual elements
    for (int i = 0; i < SIZE; i++) {
        addElement(myArrayPlus, i);
    }

    // Shows the content of our array
    printArrayPlus(myArrayPlus);

    // Empties the array
    emptyArrayPlus(myArrayPlus);

    // Adds various elements to our array
    int arrayAux[] = {15, 64, 27, 99};
    addArray(myArrayPlus, arrayAux, 4);

    // Adds a single element to our array
    addElement(myArrayPlus, 8);

    // Shows the contents
    printArrayPlus(myArrayPlus);

    // Frees the memory of our array
    freeArrayPlus(myArrayPlus);

    return 0;
}
