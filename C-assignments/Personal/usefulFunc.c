#include <stdio.h> // Input/output library
#include <math.h> // Math library reference: (https://www.w3schools.com/c/c_ref_math.php)

void printArray(int numsArray[], int numSize) {
    printf("[");
    for (int i = 0; i < numSize-1; i++) {
        printf("%d, ", numsArray[i]);
    }
    printf("%d]\n", numsArray[numSize-1]);
    return;
}   


int main(void) {
    // Instead of scanf which can cause buffer overflow, fgets() is safer
    // fgets(var, maxByte + '\0', inputType)

    char strInp[4];

    printf("Enter anything: ");
    fgets(strInp, 4, stdin); // Only take 3 input + stores a null terminator
    // abcd will store {'a', 'b', 'c', '\0'} inside strInp

    printf("\nYou entered: %s\n", strInp);

    // Math functions from math.h library
    int x = 2;
    
}

