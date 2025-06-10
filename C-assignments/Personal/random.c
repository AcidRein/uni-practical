#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    // Generate random seed given a time (we need time to randomize the seed)
    srand(time(NULL));
    // Get a random 'garbage' value
    // Formula for random range: int randomVar = [rand() % (max - min + 1) + min]
    for (int i = 0; i < 10; i++) {
        int randomNum = rand() % 6;
        printf("Random: %d\n", randomNum);
    }
    

    return 0;
    
}