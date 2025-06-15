#include <stdio.h>

/* Requirement
- Initialises an array called vals of 10 integers
- Calculates and stores, in another array called peaks, the numbers from vals which are peaks
- A number is a peak if the two numbers on either side of it are less than it
*/

int main(void) {

    // Init vectors
    int vals[10] = {0}, peaks[10] = {0};
    for (int i = 0; i < 10; i++) {
        // Take user input
        char userChar = '\0';
        printf("Enter a +integer number for the %d element: ", i);
        scanf("%c", &userChar);

        // Ascii code for '1' is 49
        // Ascii code for '9' is 57
        // Verify input
        printf("\n%d\n", userChar);
        if (userChar < 49 || userChar > 57) {
            printf("Invalid number: %c, Try again\n", userChar);
            i--;
            continue; // Invalid input
        } 
        printf("Success\n");
    }

}