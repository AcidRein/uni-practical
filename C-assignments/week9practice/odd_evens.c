#include <stdio.h>

void printVector(int vectorParam[], int vectorSize) {
  for (int i = 0; i < (vectorSize - 1); i++) {  // Loop through vector param
    printf("%d ", vectorParam[i]);  // print element except last eleent
  }
  printf("%d\n", vectorParam[vectorSize - 1]);  // print last element
}

int main(void) {
  int nums[] = {11, 3, 9, 7, 6, 10, 13, 17, 2, 8, 3};  // Initialize nums
  int numSize = sizeof(nums) / sizeof(nums[0]);  // get vector size of Nums

  int evenNums[11], oddNums[11];  // initialize even and odd vectors

  int evenIndex = 0, oddIndex = 0;  // even and nums vector index

  for (int i = 0; i < numSize; i++) {  // loop thorugh nums vector
    if (nums[i] % 2 == 0) {            // if even, push back number to evenNums
      evenNums[evenIndex] = nums[i];
      evenIndex++;

    } else {  // if odd, push back number to oddNums
      oddNums[oddIndex] = nums[i];
      oddIndex++;
    }
  }

  printVector(oddNums, oddIndex);
  printVector(evenNums, evenIndex);
}