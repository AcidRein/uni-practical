#include <stdio.h>

int main(void) {
    int x = 0;

    printf("enter a number and I'll double it: ");
    scanf("%d", &x); // Original code forgot the & before the variable x

    printf("twice %d is %d\n", x, 2*x);
    return 0;
}