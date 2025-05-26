#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

int main(void) {
    double* arr = (double *)malloc(10 * sizeof(double)); // Init dynamic array of 10 dbl
    double max = -DBL_MAX; // declare maximum variable
    double temp;
    int succ;

    // Store array dynamically and get the highest
    for (int i = 0; i < 10; i++) {
        succ = scanf("%lf", &temp);
        if (succ != 1) {
            printf("Unsuccessful in storing input\n");
            return 1; 
        }
        arr[i] = temp;
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    // print answer
    printf("The largest of your numbers is: %lf\n", max);

    // Clean memory
   free(arr);

    return 0;
}