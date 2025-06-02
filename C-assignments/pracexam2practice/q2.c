#include <stdio.h>
#include <stdlib.h>

/*
Write a function that takes two arguments: an array of integers and the size of this array. The function should then return how many values in the array are less than 100.
*/

int values_under_100(int values[], int size) {
    int counter = 0;
    for (int i = 0; i < size; i++) {
        if (values[i] < 100) {
            counter++;
        }
    }

    return counter;
}

/*
int main(void) {
    // Taken from the example except for the function
    int values[6]={-1,200,400,5,-3,600};
    int size=6;

    // call the function 
    int count = values_under_100(values, size);
    
    printf("There are %d values under 100\n", count);

    return 0;
}
*/