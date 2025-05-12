#include <stdio.h>

void printVector(int vectorParam[], int vectorSize) {
  for (int i = 0; i < (vectorSize - 1); i++) {
    printf("%d ", vectorParam[i]);
  }
  printf("%d\n", vectorParam[vectorSize - 1]);
}

int main(void) {
  int nums[] = {11, 3, 9, 7, 6, 10, 13, 17, 2, 8, 3};
  int numSize = sizeof(nums) / sizeof(nums[0]);
  printf("Vector sIZE: %d\n", numSize);

  int evenNums[11], oddNums[11];

  int evenIndex = 0, oddIndex = 0;
  for (int i = 0; i < numSize; i++) {
    if (nums[i] % 2 == 0) {
      evenNums[evenIndex] = nums[i];
      evenIndex++;
    } else {
      oddNums[oddIndex] = nums[i];
      oddIndex++;
    }
  }

  printVector(oddNums, oddIndex);
  printVector(evenNums, evenIndex);
}