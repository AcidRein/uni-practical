#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// for 'CASE INSENSTIVE' statement
char toLower(char character) {
    if (character >= 'A' && character <= 'Z') { // if character is BIG alphabet
        return (character + 32);
    }

    return character;
}

// Note: I know it's not efficient. I couldnt look up any useful functions so i had to do it in O(n^2) time
// It still meets the requirement so do i get a pass? :)
char * removeChars(char * mainString, char * charsToRemove) { 
    int lenMain = strlen(mainString), lenRmv = strlen(charsToRemove);
    char* newString = malloc(lenMain * sizeof(char));
    int charCounter = 0, isFound = 0;

    for (int i = 0; i < lenMain-1; i++) {
        isFound = 0;
        for (int j = 0; j < lenRmv-1; j++) {
            if (toLower(mainString[i]) == toLower(charsToRemove[j])) {
                isFound = 1;
                break;
            }
        }
        
        if (isFound == 0) { // char not found in remove
            newString[charCounter] = mainString[i];
            charCounter++;
        }
    }

    // Rallocate to new array
    char* newNewString = realloc(newString, (charCounter * sizeof(char)) + 1); // +1 for null terminator
    newString = newNewString;

    // return the new string
    return newString;
}

int main(void) {
    // First prompts for string
    printf("Enter your string: ");
    char userStr[100]; // max of 100 characters
    fgets(userStr, 101, stdin); // get user's 100 char + null terminator

    // Prompt char removal
    printf("Enter letters to remove: ");
    char userRmv[100]; // max of 100 characters
    fgets(userRmv, 101, stdin); // get user's 100 char + null terminator


    // Store string and char removal in a dynamic array?
    char* myString = malloc(strlen(userStr) * sizeof(char));
    char* myRemoval = malloc(strlen(userRmv) * sizeof(char));
    if (myString == NULL || myRemoval == NULL) {
        printf("Error dynamically allocating array\n");
        return 1;
    }

    // Put str and strrmv into their arrays
    for (int i = 0; i < strlen(userStr); i++) {
        myString[i] = userStr[i];
    }
    for (int i = 0; i < strlen(userRmv); i++) {
        myRemoval[i] = userRmv[i];
    }

    // call function
    char* newString = removeChars(myString, myRemoval);

    // Print result
    printf("Your new string: ");
    for (int i = 0; i < strlen(newString); i++) {
        printf("%c", newString[i]);
    }
    printf("\n");

    // Free memory
    free(myString);
    free(myRemoval);
    free(newString);

    return 0;
}