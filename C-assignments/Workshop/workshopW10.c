#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_cat(void) {
    char s[256]; 
    char s2[256];

    printf("Enter string1: ");
    scanf("%255s", s); // -1 for null terminator
    printf("Enter string2: ");
    scanf("%255s", s2); 

    int lengthBoth = strlen(s) + strlen(s2);
    
    // Dynamically make memory
    char* newStr = malloc(lengthBoth * sizeof(char) + 1); // + 1 for null terminator
    newStr[0] = '\0';  // Ensure it's an empty string before concatenation

    // Concatenate both string
    strcat(newStr, s);
    strcat(newStr, s2);

    printf("Result: %s\n", newStr);

    // Free the memory after use
    free(newStr);

    return 0;
}

int main(void){
    char userStr[257]; // + 1 or null terminator
    char* finalSubmission, finalSubmissionTemp;

    int inpBuffer, strSize = 0;
    do {
        inpBuffer = scanf("%256s", userStr);

        if (inpBuffer != 1) {
            printf("ERROR: Couldn't store user input\n");
            continue;
        }

        // If # at start, else
        
        strSize += strlen(userStr);
        finalSubmissionTemp = malloc(strSize * sizeof(char) + 1); // create new memory with new size + 1 for null terminator
        strcat(finalSubmissionTemp, finalSubmission); // Add old elements to new element,
        free(finalSubmission); // Free old memory
        free()
        if 
    } while ()
}