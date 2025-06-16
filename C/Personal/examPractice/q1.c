#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
==================================================================================================================================
Write a function common_char that takes two strings as arguments and re-
turns a new string that contains a single copy of all of the characters that
appear in either of the two strings. For example, if the strings ”hello” and
”world” were passed as arguments the function would return the string ”hellowrd” 
(o and l were already in array from ”hello”)
You may use string functions in your solution.
*/

unsigned short valueInArray(char str[], char checkFor, int size) {
    for (int i = 0; i < size; i++) {
        if (str[i] == checkFor) {
            return 1;
        }
    }
    return 0;
}
// Going by the example, assuminng that whatever char is shownn inn the first word does not appear in the second word.
char* common_char(char str1[], char str2[]) {
    int str1Size = strlen(str1);
    int str2Size = strlen(str2);
    int newArrIndex = 0;
    char* newArray = malloc(str1Size + str2Size + 1);

    for (int i = 0; i < str1Size; i++) {
        newArray[newArrIndex] = str1[i];
        newArrIndex++;
    }

    for (int i = 0; i < str2Size; i++) {
        if (valueInArray(str1, str2[i], str1Size) == 0) { // If not in array
            newArray[newArrIndex] = str2[i];
            newArrIndex++;
        } 
    }
    newArray[newArrIndex] = '\0';
    newArray = realloc(newArray, newArrIndex+1);
    return newArray;
}

int main(void){
    /*
    =============================================================================
    Write a C program that Prompts the user for a string (less than 20 characters
    long) representing a name, reads that string into a character array, prints
    the number of characters in the string.
    */
    
    /*
    char str[20]; // Can hold 19 + null term
    printf("Enter a string: ");
    scanf("%19s", str);

    printf("Length of string: %ld\n", strlen(str));
    */
    
    // ============================================================================
    // List and give an example of three different defensive programming practices
    /*
    - Freeing heap memories (like using free() on arrays made by malloc)
    - Allocating memories as needed to prevent memory overflow (like having sufficient memory for scanf())
    - Having fail-safe in code to exit. (like checking if a pointer is null when assigning malloc)
    */

    /*
    Explain the difference between: 1) an int and a long int 2) a float and a
    double. Include in your explanation when you would use each.
    */
    
    /* Ints are 4 byte data that can store (2^32-1) whole numbers, where long int stores (2^64)-1 whole numbers.
    You would use int to store numbers, or use long int for storing very large numbers for things like calculations, 
    at the cost of more memory usage.

    Floats are data type that can store up to 7 decimal digits, and double can store up to 16, which allows more precise values
    for things that needs to be precisely calculated/
    */
    return 0;
}