#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    int seed = time(0);
    srand(seed);

    for (int i = 0; i < 100; i++) {
        int randomNum = rand();

        printf("Random: %d\n", randomNum);
    }
    
}