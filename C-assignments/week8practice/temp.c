#include <stdio.h>

// Using "gcc -Wall temp.c" to compile
int main(void) {
    double userCelcius;
    printf("Please ener a celcius: ");
    scanf("%lf", &userCelcius);

    double fahrenheit = ((userCelcius * 9) / 5.0) + 32;
    
    // Display the celcius and fahrenheit as a whole number
    printf("%d degree celcius is %d in fahrenheit", (int) userCelcius, (int) fahrenheit);

    return 0;

}
