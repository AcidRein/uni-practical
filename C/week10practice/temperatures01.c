#include <stdio.h>
#include <stdlib.h>

void printVector(float* array, int arraySize) {
  // print ans
  for (int i = arraySize - 1; i > 0; i--) {
    printf("%.1f ", array[i]);
  }

  if (arraySize > 0) {
    printf("%.1f\n", array[0]);
  }
}
int main(void) {
  int numTemps;
  scanf("%d", &numTemps);

  float* arrayPtr = malloc(numTemps * sizeof(int));
  for (int i = 0; i < numTemps; i++) {
    scanf("%f", &arrayPtr[i]);
  }

  // Print vector neatly
  printVector(arrayPtr, numTemps);

  return 0;
}