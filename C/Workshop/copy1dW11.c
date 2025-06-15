#include <stdio.h>
#include <stdlib.h>

/*
In this question you should write a C program called  copy_1d  which defines an uses an array_copy function that copies data from a source array of integers to a destination array of integers.  The signature of array_copy is:

void array_copy(int *src, int *dest, int len)

You can assume that the dest array is allocated before the call to the function and len defines the length of the source array. Your program should perform a basic test on this code.
*/
void printArray(int numsArray[], int numSize) {
    printf("[");
    for (int i = 0; i < numSize-1; i++) {
        printf("%d, ", numsArray[i]);
    }
    printf("%d]\n", numsArray[numSize-1]);
    return;
}   

void array_copy(int *src, int *dest, int len) {
    for (int i = 0; i < len; i++) {
        *(dest+i) = *(src+i);
    }
    return;
}

int main(void) {
    int len = 10;
    int* dynaSrc = malloc(len * sizeof(int));
    int* dynaDes = malloc(len * sizeof(int));

    // Handling malloc error
    if (dynaSrc == NULL || dynaDes == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    
    // FIll only dynaSrc array
    for (int i = 0; i < len; i++) {
        dynaSrc[i] = i * 2;
    }

    array_copy(dynaSrc, dynaDes, len);

    printArray(dynaSrc, len);
    printArray(dynaDes, len);

    free(dynaSrc);
    free(dynaDes);
}