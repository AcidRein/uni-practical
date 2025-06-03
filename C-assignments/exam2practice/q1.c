#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // Dyna array
    int* myNums = malloc(5 * sizeof(int));

    int callBack, temp;
    for (int i = 0; i < 5; i++) {
        printf("Enter a number: ");
        callBack = scanf("%d", &temp);

        while (callBack != 1) {
            printf("Enter valid int!\n");
            while (getchar() != '\n');
            printf("Enter a number: ");
            callBack = scanf("%d", &temp);
        }
        myNums[i] = temp;
    }

    // Print the product of pos integers
    int product = 1;
    for (int i = 0; i < 5; i++) {
        if (myNums[i] > 0) {
            product *= myNums[i];
        }
    }

    printf("Your product: %d\n", product);
    return 0;
}