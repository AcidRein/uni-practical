#include <stdio.h>
#include <stdlib.h>

void printVector(int* array, int arraySize) {
    // print ans
    for (int i = 0; i < arraySize-1; i++) {
        printf("%d ", array[i]);
    }

    if (arraySize > 0) {
        printf("%d\n", array[arraySize-1]);
    }
}

int main(void) {

    int numInts;
    scanf("%d", &numInts); // get array size

    // Dynamically store user's input
    int* allInputs = malloc(numInts * sizeof(int));

    int oddCounter = 0, evenCounter = 0;
    int scanSucc; // success of user input
    int tempVar; // variable to temporary store user's input

    for (int i = 0; i < numInts; i++) {
        scanSucc = scanf("%d", &tempVar);
        if (scanSucc != 1) {
            // printf("Error allocating number to temp, try again.\n");
            i--;
            continue;
        }

        // Store
        allInputs[i] = tempVar;  

        // Count user's odd and even numbers
        if (tempVar % 2 == 0) {
            evenCounter++;
        } else {
            oddCounter++;
        }

    }

    // Dynamically allocate odd and even numbers to array
    int *oddNums = malloc(oddCounter * sizeof(int));
    int* evenNums = malloc(evenCounter * sizeof(int));

    // Store to odd and even nums accordingly
    int oddIndex = 0, evenIndex = 0;
    for (int i = 0; i < numInts; i++) {
        if (allInputs[i] % 2 == 0) {
            evenNums[evenIndex] = allInputs[i];
            evenIndex++;
        } else {
            oddNums[oddIndex] = allInputs[i];
            oddIndex++;
        }
    }

    // Print
    printVector(oddNums, oddIndex);
    printVector(evenNums, evenIndex);

    return 0;
}