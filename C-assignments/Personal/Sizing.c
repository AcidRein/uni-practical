#include <stdio.h>

int main(void) {
    // Declare Variables
    int var1 = 1; // 4 bytes typically
    float var2 = 2.3; // 4 bytes
    double var3 = 3.4567; // 8 bytes
    char var4 = 'a'; // 1 byte (0-255 characters in ascii table)

    // Declare vectors 
    int vec1[] = {10, 8, 6, 2, 3}; // Size of vector is the sum of all vectors (5)

    // ASCII table stuff
    char x = 'a';
    printf("Character (%c) is %d element in the ascii table\n", x, x);
    // Calculation to find length of any type of array: sizeof(vec1) / sizeof(vec1[0])
    return 0;
}