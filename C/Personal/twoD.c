// 2D Array for C
#include <stdio.h>
#include <stdlib.h>

void print1D(int* oneD, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", oneD[i]);
    }
    printf("\n");
    return;
}
void print2D(int* twoD, int numRows, int numCols) {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            // The 'formula' to find a specific element in twoD[r][c] is given by (numCols*row) + column
            printf("%d ", twoD[(numCols*i) + j]);
        }
        printf("\n");
    }
    return;
}

void print2DArrInArr(int** twoD, int numRows, int numCols) {
    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < numCols; c++) {
            printf("%d ", twoD[r][c]); // yes we can do (2DARRAY[Row][Column])
        }
        printf("\n");
    }
    return;
}

int main(void) {
    // =================================== 2D ARRAY MALLOC METHOD =======================
    // You can create 2D array using a 1D array
    int numRows = 2, numCols = 3;
    int* my2D = malloc(numRows * numCols * sizeof(int));

    // We have a long array now. lets fill it up with stuff
    for (int i = 0; i < (numRows * numCols); i++) {
        my2D[i] = i;
    }

    printf("Printing malloc 2D Array:\n");
    // print 1d
    print1D(my2D, numRows*numCols);
    // Print using custom print
    print2D(my2D, numRows, numCols);

    // Always free malloc
    free(my2D);

    // =============================== 2D ARRAY IN ARRAY METHOD =================================
    // We allocate memory for an array of arrays. 
    // Basically, we have one array, and it's sole purpose is to store other arrays.
    
    // Declare array of arrays (rows)
    int numberOfRows = 3, numberOfColumns = 5;
    int** arrInArr = malloc(numberOfRows * sizeof(int*));

    // Declare the children of array of arrays (columns)
    for (int i = 0; i < numberOfRows; i++) {
        arrInArr[i] = malloc(numberOfColumns * sizeof(int));
    }

    // Fill elements
    int counter = 0;
    for (int r = 0; r < numberOfRows; r++) {
        for (int c = 0; c < numberOfColumns; c++) {
            arrInArr[r][c] = counter;
            counter++; 
        }
    }

    printf("Printing Array in Arrays:\n");
    // Print 2D array
    print2DArrInArr(arrInArr, numberOfRows, numberOfColumns);

    // Free each element
    for (int i = 0; i < numberOfRows; i++) {
        free(arrInArr[i]);
    }
    free(arrInArr);

    return 0;
}