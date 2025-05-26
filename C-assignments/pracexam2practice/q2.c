#include <stdio.h>
#include <stdlib.h>

int values_under_100(int arr[], int arrSize) {
    int count = 0;
    for (int i = 0; i < arrSize; i++) {
        if (arr[i] < 100) {
            count++;
        }
    }

    return count;
}
int main(void) {
    int values[6]={-1,200,400,5,-3,600};
    int size=6;

    // call the function 
    int count = values_under_100(values, size);
    
    printf("There are %d values under 100\n", count);

    return 0;
}