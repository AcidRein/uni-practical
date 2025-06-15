#include <stdio.h>
#include <math.h>

int findMax(int vecParam[], int vecSize){
  int max = -__INT_MAX__;
  for (int i = 0; i < vecSize; i++) {
    if (vecParam[i] > max) {
      max = vecParam[i];
    }
  }

  return max;
}

int findMin(int vecParam[], int vecSize){
  int min = __INT_MAX__;
  for (int i = 0; i < vecSize; i++) {
    if (vecParam[i] < min) {
      min = vecParam[i];
    }
  }

  return min;
}

int findSum(int vecParam[], int vecSize){
  int sum = 0;
  for (int i = 0; i < vecSize; i++) {
    sum += vecParam[i];
  }

  return sum;
}
int main(void) {
  // Initialize
  int userAgeInput, userAgeIndex = 0;
  int ageArray[11];

  int returnValue = 0;
  char buffer;

  for (int i = 0; i < 10; i++) {
    // Prompt for Input
    // printf("Enter your age [%d]: ", userAgeIndex);
    returnValue = scanf("%d", &userAgeInput);

    if (returnValue != 1) {  // If unsuccessfully unsigned, re-prompt
      // printf("Enter a valid number! Try again\n");
      scanf(" %c", &buffer);
      i--; // reverse index
      continue;
    }

    // If user enters -1, exit
    if (userAgeInput == -1) {
      break;

      // If user types a negative number or exceeds 150, reprompt
    } else if (userAgeInput < 0 || userAgeInput > 150) {
      // printf("[%d] is not a valid Age! Try again\n", userAgeInput);
      i--; // reverse index
      continue;
    }

      // Store in array
      ageArray[userAgeIndex] = userAgeInput; 

    // Valid entries
    userAgeIndex++; // Store how many entries were given
  }

  int ageSum = findSum(ageArray, userAgeIndex);
  int ageMax = findMax(ageArray, userAgeIndex);
  int ageMin = findMin(ageArray, userAgeIndex);

  float averageAge = ((float)ageSum) / ((float)userAgeIndex); // find average age
  float averageAgeInt = ageSum / userAgeIndex; // find average age but as integer (1.0)

  if (averageAge == averageAgeInt) { // if float is whole number, make integer
    averageAge = (int) averageAge;
  }

  // Output result
  printf("%d %d %.1f\n", ageMax, ageMin, averageAge);

  return 0;
}