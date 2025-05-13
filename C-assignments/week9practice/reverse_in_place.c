#include <stdio.h>

int main(void) {
  char myStr[21] = {-1};  // init string vector to have invalid ascii range

  printf("Enter 20 char or less: ");
  fgets(myStr, 21, stdin);  // Get user input

  for (int i = 20; i >= 0; i--) {  // Looping from end to start of array

    if (myStr[i] > 0 && myStr[i] < 255) {  // If is within ascii range
      printf("%c", myStr[i]);              // print character
    }
  }
  printf("\n");  // end print
}