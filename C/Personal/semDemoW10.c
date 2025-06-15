#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char myString1[256];
    char myString2[256];

    printf("Enter first string: ");
    scanf("%255s", myString1);

    printf("Enter second string: ");
    scanf("%255s", myString2);

    // Find length of both string
    unsigned int lengthBoth = strlen(myString1) + strlen(myString2);

    // Allocate memory using Malloc
    char* newArrPtr = malloc(lengthBoth * sizeof(char) + 1); // Add 1 for the null terminator

    if (newArrPtr == NULL) { // unsuccessful for getting ptr of new memory
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Initialize `newArrPtr` before using `strcat`
    newArrPtr[0] = '\0'; 

    // Concat both string to the new array
    strcat(newArrPtr, myString1);
    strcat(newArrPtr, myString2);

    // Print concatenated new array
    printf("String of both: %s\n", newArrPtr);
}