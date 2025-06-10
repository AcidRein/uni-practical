#include <stdio.h>
#include <stdlib.h>

// Task: create a function to copy a 2d array to a destination
// Signature
void array_2dcopy(int** src, int **dest, int rows, int cols) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            dest[row][col] = src[row][col];
        }
    }
}

int main(void) {

}
