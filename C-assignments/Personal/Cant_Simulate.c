
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Given an array of size 4, return the array filled with random numbers between 1-4
void randomDice(int* diceArray) {
    for (int i = 0; i < 4; i++) {
        int randomNum = rand() % (6) + 1; // random number 1-6
        diceArray[i] = randomNum;
    }
    return;
}
int main(void) {
    // Generate random seed given a time (we need time to randomize the seed)
    srand(time(NULL));

    // Initializing our variables
    int* diceInventory = malloc(4 * sizeof(int));// Init the dices we have

    // Counter

    for (int rollRound = 1; rollRound <= 4; rollRound++) { // Simulating 1-4 rolls
        randomDice(diceInventory); // Fill dice inventory with random numbers
        
    }



    // Free memory to prevent leak
    free(diceInventory);


    return 0;
    
}