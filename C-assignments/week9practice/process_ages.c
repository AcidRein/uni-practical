#include <stdio.h>

int main(void) {
  // Initialize
  int userAgeInput, userAgeIndex = 0;
  int minAge = __INT_MAX__, maxAge = -__INT_MAX__, ageSum = 0;
  int returnValue = 0;
  char buffer;

  while (1) {
    // Prompt for Input
    printf("Enter your age [%d]: ", userAgeIndex);
    returnValue = scanf("%d", &userAgeInput);

    if (returnValue != 1) {  // If unsuccessfully unsigned, re-prompt
      printf("Enter a valid number! Try again\n");
      scanf(" %c", &buffer);
      continue;
    }

    // If user enters -1 or entered 10 people, exit
    if (userAgeInput == -1 || userAgeIndex >= 9) {
      break;

      // If user types a negative number or exceeds 150, reprompt
    } else if (userAgeInput < 0 || userAgeInput > 150) {
      printf("[%d] is not a valid Age! Try again\n", userAgeInput);
      continue;
    }

    // Valid entries
    userAgeIndex++;

    // Find min/max age
    if (userAgeInput > maxAge) {
      maxAge = userAgeInput;
    }
    if (userAgeInput < minAge) {
      minAge = userAgeInput;
    }

    // Sum age
    ageSum = ageSum + userAgeInput;
  }

  float averageAge = ((float)ageSum) / ((float)userAgeIndex);
  printf("\nMaximum: %d\nMinimum: %d\nAverage: %.1f\n", maxAge, minAge,
         averageAge);

  return 0;
}