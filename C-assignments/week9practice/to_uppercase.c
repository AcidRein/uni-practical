#include <stdio.h>

int main(void) {
  // A (65) - Z (90)
  // a (97) - z (122)

  char personName[21] = {0};

  printf("Enter your Name (all lowecase): ");
  fgets(personName, 21, stdin);  // User input

  for (int i = 0; i < 20; i++) {
    if (personName[i] < 'a' ||
        personName[i] > 'z') {      // If not alphabet from a-z
      printf("%c", personName[i]);  // Print ascii character

    } else {                             // if alphabet from a to z
      printf("%c", personName[i] - 32);  // Print uppercase version
    }
  }
  printf("\n");
}