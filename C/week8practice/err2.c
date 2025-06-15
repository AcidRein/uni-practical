#include <stdio.h>

int main(void) {
    int x; // Original code did not initialize x

    printf("enter a number: ");
    scanf("%d", &x);

    printf("you entered: %d\n", x);
    
    return 0;
} 