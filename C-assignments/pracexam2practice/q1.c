#include <stdio.h>
#include <stdlib.h>

/*
Write a program that:

reads in 10 doubles  from the user (10 marks) storing the numbers in an array (can be static or dynamic) (10 marks).  Then prints the maximum value of all of the numbers in the array (10 marks)
*/

int main(void) {
    double* myArr = malloc(10 * sizeof(double));
    if (myArr == NULL) {
        printf("Issue dynamically allocating array.\n");
        return 1;
    }

    int callBack;
    double temp;

    for (int i = 0; i < 10; i++) {
        printf("Enter a number: ");
        callBack = scanf("%lf", &temp);
        while (callBack != 1) {
            printf("Failed Getting number. try again!\n");
            // Clear input buffer
            while (getchar() != '\n');
            printf("Enter a number: ");
            callBack = scanf("%lf", &temp);
        }
        myArr[i] = temp;
    }

    double max = myArr[0];
    for (int i = 1; i < 10; i++) {
        if (myArr[i] > max) {
            max = myArr[i];
        }
    }

    printf("The largest of your numbers is: %lf\n", max);
    free(myArr);

    return 0;
}