#include <stdio.h>
#include <stdlib.h>

/*
===============================================================
part b - modifying values_under_100 function (35 marks)

Modify the values_under_100 function to take a 3rd argument which is the memory address of a pointer to an int (5 marks).  Note this is the memory address of the pointer, not the value of the pointer.  

The function should

    dynamically allocate exactly enough space to store all of the numbers that are under 100 (10 marks)
    copy the numbers under 100 to this newly allocated array (10 marks).
    Write the memory address of this newly allocated array into the pointer referred to by the 3rd argument. (10 marks).

The function must NOT print any output.
*/

int values_under_100(int numsArray[], int numSize, int** pointerToInteger) { // two asterisks to show it's a pointer to a pointer
    // Initialy dynamically allocate memory to store under 100 values
    int* numsUnder100 = malloc(numSize * sizeof(int));
    if (numsUnder100 == NULL) {
        printf("Error dynamically creating memory for numbers under 100.\n");
        return -1; // return error
    } 
    int counterUnder100 = 0; // counter for how many values are under 100

    // Count values under 100
    for (int i = 0; i < numSize; i++) {
        if (numsArray[i] < 100) {
            numsUnder100[counterUnder100] = numsArray[i]; // Store value under 100 inside dyna array
            counterUnder100++; // increment counter
        }
    }

    // Reallocate 'numsUnder100' to an array of exact size
    int* newNumsUnder100 = realloc(numsUnder100, counterUnder100 * sizeof(int)); // (ptr to realloc, size of new dyna array)
    if (newNumsUnder100 == NULL) {
        printf("Error newly dynamically creating memory for numbers under 100. \n");
        free(numsUnder100); // free and return error
        return -2;
    } 

    // Reassign numsUnder100 to the new Array
    numsUnder100 = newNumsUnder100;

    // rewrite the address of "pointerToInteger" to point to the new array
    *pointerToInteger = numsUnder100;
    
    return counterUnder100; // return nums under 100 counter
}