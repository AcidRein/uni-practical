#include <stdio.h>
#include <stdlib.h>

void printArray(float numsArray[], int numSize) {
    printf("[");
    for (int i = 0; i < numSize-1; i++) {
        printf("%.1f, ", numsArray[i]);
    }
    printf("%.1f]\n", numsArray[numSize-1]);
    return;
}   


int main(void) {
    int numSize, callBack;

    // Prompt for numSize, the size of array
    printf("How many grades to be entered: ");
    callBack = scanf("%d", &numSize);
    if (callBack != 1) {
        printf("Error, bad numSize input\n");
        return 1;
    }

    // Allocate all grades memory
    float* gradeArray = (float* ) malloc(numSize * sizeof(float));
    // Allocate memory for failed grades
    float* gradeFailArray = (float* ) malloc(numSize* sizeof(float));

    if (gradeArray == NULL || gradeFailArray == NULL) {
        printf("Error dynamically allocaitng array\n");
        return 1;
    }
    // Store user's grade
    float temp;
    int failCounter = 0; // Num of students getting below 50 marks
    for (int i = 0; i < numSize; i++) {
        printf("Enter a grade: ");
        callBack = scanf("%f", &temp);
        
        // Wait til user inputs a valid floaitng point number
        while (callBack != 1) {
            printf("Invalid float number! Try again\n");
            while (getchar() != '\n');
            printf("Enter a grade: ");
            callBack = scanf("%f", &temp);
        }

        // Check 0-100 range
        if (temp < 0 || temp > 100) {
            printf("Invalid grade: Grade not within range\n");
            i--;
            continue;
        }
        
        // Check if fail
        if (temp < 50) {
            gradeFailArray[failCounter] = temp;
            failCounter++;
        }

        // Store in dyna array
        gradeArray[i] = temp;
    }

    // Print grades vector
    printf("You entered the grades: ");
    printArray(gradeArray, numSize);

    // Reallocate the failed grade array to an exact fit size
    float* newFailArray = realloc(gradeFailArray, failCounter * sizeof(float));
    if (newFailArray == NULL) {
        printf("Error newly dynamically creating memory for failed grade\n");
        free(gradeArray);
        free(gradeFailArray); // free and return error
        return 1;
    } 
    gradeFailArray = newFailArray;

    // Print failed vectors
    printf("Failed grades: ");
    printArray(gradeFailArray, failCounter);

    // Free dynamically allocated arrays
    free(gradeArray);
    free(gradeFailArray);

    return 0;

}