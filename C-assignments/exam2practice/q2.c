#include <stdio.h>
#include <stdlib.h>

int countGreaterThanLast(int values[], int arrSize) {
    int counter = 0;
    int lastElem = values[arrSize-1];
    for (int i = 0; i < arrSize-1; i++) {
        if (values[i] > lastElem) {
            counter++;
        }
    }
    return counter;
}
int main(void) {

    int values[6] = {6, 1, 4, 5, 2, 3};
    int size = 6;

    printf("There are %d values greater than the last element\n", countGreaterThanLast(values, size));
}