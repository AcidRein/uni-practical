#include <stdio.h>

/* === Requirement ===
- Prompts the user for a string consisting only lower-case letters (less than 20 characters long).
- Reads that string into a character array. 
- Iterates through the string and places letters that are less than 'm' into an array called first and the letters that are 'm' or greater are placed into an array called last. 
- After finishing you should place a null character on the end of each array of letters so that they can be easily printed.
- Your program should then print out the contents of first and second

ASCII code: https://www.ascii-code.com/
*/

int main(void) {
    // Init vector

    // Initializes ALL vector elements to `'\0'` (ASCII 0)
    char strInp[20] = {0}; 
    char first[20] = {0}, last[20] = {0};

    // Lowercase a is the 97th element in ascii table
    // Lowercase m is 109th element in ascii table

    printf("Please enter one word of 20 char or less: ");
    scanf("%s", strInp);

    int firstInd = 0, lastInd = 0; // Initialize each vector index
    int sizeStrInp = sizeof(strInp)/sizeof(strInp[0]); // Get total size of strInp

    // Store ascii letters below m (exclusive) in 'first' vector, and otherwise in 'last' evctor
    for (int i = 0; i < sizeStrInp; i++) {
        // Print debug
        printf("Char: %c, ascii: %d\n", strInp[i], strInp[i]);

        if (97 > strInp[i] || strInp[i] > 122) { // Check if not in ascii range of lowercase a - z
            continue; // Skip 
        }

        if (strInp[i] < 109) {
            first[firstInd] = strInp[i];
            firstInd++;
        } else {
            last[lastInd] = strInp[i];
            lastInd++;
        }
    }

    // Print results
    printf("First: %s\n", first);
    printf("Last: %s\n", last);

    return 0;
}