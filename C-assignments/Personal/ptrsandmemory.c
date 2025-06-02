#include <stdio.h>
#include <stdlib.h> // Must include to use malloc(), free(), realloc();

int main(void) {
    // A variable 
    int x = 20;
    int* ptr = &x; // Pointer to memory of x

    // Size of an integer:
    printf("Int Size: %zu, Int ptr Size: %zu\n", sizeof(int), sizeof(int*));



    // Dynamically

    return 0;
}