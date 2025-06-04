#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    // Generate random seed given a time (we need time to randomize the seed)
    srand(time(NULL));
    // Get a random 'garbage' value
    // Formula for random range: int randomVar = [rand() % (max - min + 1) + min]
    int randomNum = rand();
    printf("Random: %d\n", randomNum);



    return 0;
    
}