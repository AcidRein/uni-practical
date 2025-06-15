#include <stdio.h>
#include <string.h>

int main(void) {
    char str1[11], str2[11];

    // Take input
    printf("Enter word 1: ");
    scanf("%10s", str1);
    printf("Enter word 2: ");
    scanf("%10s", str2);

    if (strlen(str1) > strlen(str2)) {
        printf("The longer word is %s\n", str1);
    } else {
        printf("The longer word is %s\n", str2);
    }

    return 0;
}