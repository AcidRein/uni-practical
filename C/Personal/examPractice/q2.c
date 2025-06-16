#include <stdlib.h>
#include <stdio.h>

/*
==========================================================================================================================
Write a program called odds_evens that reads a (non-empty) sequence of integers. As for question 1 above, your program should first ask for the num-
ber of integers to read and dynamically allocate an array just big enough to
hold the number of values you read.
You should then read in the elements of the array using a loop. Then your
program must dynamically allocate two arrays one to hold all the even num-
bers from the array you have just read and one to hold the odd numbers
from the array. Your code must allocate just enough space to each of the
arrays to hold the odd and the even numbers.
*/



int main(void) {
    int numRead;
    unsigned short callBack;

    printf("Enter array size: ");
    callBack = scanf("%d", &numRead);
    if (callBack != 1) {
        printf("Bad number\n");
        return 1;
    }

    //Dyna array
    int* allArr = malloc(numRead * sizeof(int));
    if (allArr == NULL) {
        return 1;
    }
    
    // Dynamically allocate memory
    int oddCounter = 0, evenCounter = 0, temp;
    for (int i = 0; i < numRead; i++) {
        printf("Enter your %dth element: ", i);
        callBack = scanf("%d", &temp);
        if (callBack != 1) {
            i--;
            continue;
        }

        if (temp % 2 == 0) {
            evenCounter++;
        } else {
            oddCounter++;
        }
        allArr[i] = temp;
    }

    // Make odd even
    int* oddA = malloc(oddCounter * sizeof(int));
    int* evenA = malloc(evenCounter * sizeof(int));
    if (oddA == NULL || evenA == NULL) {
        free(allArr);
        return 1;
    }

    int evenTrack = 0, oddTrack = 0;
    for (int i = 0; i < numRead; i++) {
        if (allArr[i]%2 == 0) {
            evenA[evenTrack] = allArr[i];
            evenTrack++;
        } else {
            oddA[oddTrack] = allArr[i];
            oddTrack++;
        }
    }

    free(allArr);
    free(evenA);
    free(oddA);

    return 0;
}
