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

void reallocateArray(
    float* moveFrom, float* moveTo,
    int moveFromSize) {  // Moves all elements in param1 to param2 array
  for (int i = 0; i < moveFromSize; i++) {
    *(moveTo + i) = *(moveFrom + i);
  }
}

float* doubleSizeArray(float* fullArray, int newArraySize) {
  int oldarraySize =
      newArraySize / 2;  // store the size fo the old 'full' array
  float* newArray =
      malloc(newArraySize *
             sizeof(float));  // create new array with double original size
  reallocateArray(fullArray, newArray,
                  oldarraySize);  // move old array element to new array
  // Free up old array
  free(fullArray);

  return newArray;  // return the new array to act as array to append on
}
int main(void) {
  int arrSize = 5;  // initally allocate 5 mem

  float* arrayPtr = malloc(arrSize * sizeof(float));
  int currLocation = 0;  // location of pointer in an array

  float tempValue = 0;  // temporray hold user value
  int succScan;
  while (1) {
    succScan = scanf("%f", &tempValue);

    // Check if -100.0 value or allocation not successful
    if ((tempValue == -100.0) || (succScan != 1)) {
      break;
    }

    // change value of array
    *(arrayPtr + currLocation) = tempValue;
    currLocation++;  // move to next item in array

    // Check if current array is full
    if (currLocation == arrSize) {  // if the current Pointer location is at the
                                    // end of the array,
      arrSize *= 2;                 // double array size
      // create a new array and move all elements to new array
      arrayPtr = doubleSizeArray(
          arrayPtr, arrSize);  // use the new array to set as previous
    }
  }

  // Print vector neatly
  printVector(arrayPtr, currLocation);
  return 0;
}