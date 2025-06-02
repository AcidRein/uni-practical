#include <stdio.h>
#include <stdlib.h>

/*
Write a program that modifies the main function and function from question 2

=================================================================
part a - modifying main (15 marks)

Modify the main program to:

    dynamically create the values array  (you must allow the user to enter any number of values, but you may choose whether you ask for the number of values that will be entered or look for a sentinel value**).   (5 marks)
    prompt for the  individual grades storing them in the allocated array (5 marks)
    print the array. (5 marks) 

**note the autograder will only test the case where you ask the user the number of values that will be entered - but the actual prac exam is hand marked and would accept either.

*/

void printArray(int numsArray[], int numSize) {
    printf("[");
    for (int i = 0; i < numSize-1; i++) {
        printf("%d, ", numsArray[i]);
    }
    printf("%d]\n", numsArray[numSize-1]);
    return;
}   

int main(void) {
    int numSize;
    int callBack;

    // Get size of array
    printf("Enter array length: ");
    callBack = scanf("%d", &numSize);
    if (callBack != 1) {
        printf("Bad numsize input. Try again later\n");
        return 1;
    }

    // Dynamically allocate memory for array
    int* numsArray = malloc(numSize * sizeof(int));
    if (numsArray == NULL) {
        printf("Error allocating memory of size %d, please try again later.\n", numSize);
        return 1;
    }

    // Fill array
    for (int i = 0; i < numSize; i++) {
        printf("Please enter a number: ");
        callBack = scanf("%d", &numsArray[i]);
        while (callBack != 1) {
            printf("Please enter a valid number! Try again\n");
            // Clear input buffers
            while (getchar() != '\n');
            // Reprompt
            printf("Please enter a number: ");
            callBack = scanf("%d", &numsArray[i]);
        }
    }

    // Print out our array
    printArray(numsArray, numSize);

    // Call function given memory
    int anInteger;
    int* pointerToInt = &anInteger; 
    int count = values_under_100(numsArray, numSize, &pointerToInt);
    if (count < 0) { // On error
        printf("Error in values_under_100 function. Closing...\n");

        // Free memory to prevent leak
        free(numsArray);    
        
        return 1;
    }

    // Output answers
    printf("There are %d values under 100\n", count);
    printf("The values less than 100 are: ");
    printArray(pointerToInt, count);
    
    // Free memory to prevent leak
    free(numsArray);
    free(pointerToInt);

    return 0;
}