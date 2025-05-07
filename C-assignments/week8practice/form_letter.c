#include <stdio.h>

int main(void) {
    char firstName[10], lastName[10];
    int age;
    double fraction;

    printf("Enter your Full name, age, and employement fraction: ");
    scanf("%c", &firstName);
    scanf("%c", &lastName);
    scanf("%d", &age);
    scanf("%lf", &fraction);

    printf("Your name is %c %c, you are %d years old and your employment fraction is %.1f",
    firstName, lastName, age, fraction);

}