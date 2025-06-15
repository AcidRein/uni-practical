#include <stdio.h>

void printVec(int vec[], int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", vec[i]);
    }
    printf("\n");
}
void array_copy(int *src, int* dest, int len) {
    for (int i = 0; i < len; i++) {
        dest[i] = src[i];
    }
}
int main(void) {
    int arr1[6] = {1, 2, 3, 4, 5, 6};
    int arr2[6] = {7, 8, 9, 10, 11, 12};

    array_copy(arr1, arr2, 6);

    printVec(arr1, 6);
    printVec(arr2, 6);

    return 0;
}
