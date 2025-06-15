#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// The rules are simple. There are 2 players, both players decide who will start –
// let’s say player 1 starts. Player 1 “builds” a board with 10 to 15 boxes,
// Now, player 2 can cross between 1 and 2 of the boxes 
// The winner of the game is the one who crosses the last empty box.

unsigned short botTurn(unsigned short* arrayBox, unsigned short numBoxes) {
    // Objective, try combinations to have numBoxes % 3 == 0
    // Count how many boxes are left
    unsigned short boxLeft = 0;

    for (int i = 0; i < numBoxes; i++) {
        if (arrayBox[i] == 0) {
            boxLeft++;
        }
    }
    // If there's a winning method, win the game
    if (boxLeft % 3 != 0) {
        if ((boxLeft - 1) % 3 == 0) {
            return 1;
        } else if ((boxLeft - 2) % 3 == 0) {
            return 2;
        }
    } else { // No optimised way to win unless opponent mistakes. just make a waiting move
        unsigned short botRando = (rand() % 2) + 1;
        return botRando;
    }

    return 0;
}
unsigned short badInput(unsigned short callBack, unsigned short value) {
    // Check for bad inputs
    if (callBack != 1) {
        printf("Error scanning. Perhaps enter a real number?\n");
        while (getchar() != '\n');
        return 1;
    } 

    if (value != 1 && value != 2) {
        printf("Enter a number 1 or 2.\n");
        return 1;
    }

    return 0;
}

unsigned short assignCheckBox(unsigned short* arrayBox, unsigned short numBoxes, unsigned short plr, unsigned short value, unsigned short* curIter) {
    for (int i = 0; i < value; i++) {
        arrayBox[*curIter] = plr;
        *curIter = *curIter + 1;
        if (*curIter > numBoxes-1) {
            return 1;
        }
    }

    return 0;
}

void printBoxes(unsigned short* arrayBoxes, unsigned short numBoxes) {
    for (int i = 0; i < numBoxes; i++) {
        if (arrayBoxes[i] == 0) {
            printf("· ");
        } else {
            printf("%hu ", arrayBoxes[i]);
        }
    }
    printf("\n\n");
    return;
}

void PVP(unsigned short* boxArray, unsigned short numBoxes) {
    // Player variables
    unsigned short callBack, plr1, plr2;
    unsigned short currentTurn = 2; // Player 2 always start because player 1 chooses box
    unsigned short currentIteration = 0; // The current state of the array
    unsigned short completeGame = 0;

    // Main game.
    while (completeGame != 1) {
        printf("Player %hu's turn. How many boxes to tick?: ", currentTurn);
        switch (currentTurn)
        {
        case 1:
            callBack = scanf("%hu", &plr1);

            if (badInput(callBack, plr1) != 0) {
                continue;
            }
            
            if (assignCheckBox(boxArray, numBoxes, 1, plr1, &currentIteration) == 1) {
                completeGame = 1;
            }
            break;

        case 2:
            callBack = scanf("%hu", &plr2);

            if (badInput(callBack, plr2) != 0) {
                continue;
            }
            
            if (assignCheckBox(boxArray, numBoxes, 2, plr2, &currentIteration) == 1) {
                completeGame = 1;
            }
            break;
        default:
            break;
        }
        // Print
        printBoxes(boxArray, numBoxes);
        currentTurn = (currentTurn == 1)? 2 : 1; // Alternate turns if everything goes correctly.
    }
    printf("Winner: Player %hu\n", boxArray[numBoxes-1]);

    return;
}

void PVE(unsigned short* boxArray, unsigned short numBoxes, unsigned short botPlr) {
    unsigned short callBack, humanChoice, botChoice; 
    unsigned short curIter = 0, completeGame = 0;
    unsigned short currentTurn = 2; // Current turn

    while (completeGame != 1) {
        switch (currentTurn)
        {
        case 1: // On plr1 turn
            if (botPlr == 1) { // if bot is player 1.
                botChoice = botTurn(boxArray, numBoxes);
                printf("Bot (plr %hu) is thinking... Bot plays: %hu\n", botPlr, botChoice);
                if (assignCheckBox(boxArray, numBoxes, 1, botChoice, &curIter) == 1) {
                    completeGame = 1;
                }
            } else {
                callBack = scanf("%hu", &humanChoice);

                if (badInput(callBack, humanChoice) != 0) {
                    continue;
                }
                
                if (assignCheckBox(boxArray, numBoxes, 1, humanChoice, &curIter) == 1) {
                    completeGame = 1;
                }
            }
            break;
        case 2: // On plr2 turn
            if (botPlr == 2) { // If bot is player 2,
                botChoice = botTurn(boxArray, numBoxes);
                printf("Bot (plr %hu) is thinking... Bot plays: %hu\n", botPlr, botChoice);
                if (assignCheckBox(boxArray, numBoxes, 2, botChoice, &curIter) == 1) {
                    completeGame = 1;
                }
            } else {
                callBack = scanf("%hu", &humanChoice);

                if (badInput(callBack, humanChoice) != 0) {
                    continue;
                }
                
                if (assignCheckBox(boxArray, numBoxes, 2, humanChoice, &curIter) == 1) {
                    completeGame = 1;
                }
            }
            break;
        default:
            break;
        }

        // Print
        printBoxes(boxArray, numBoxes);
        currentTurn = (currentTurn == 1)? 2 : 1; // Alternate turns if everything goes correctly.
    }

    if (boxArray[numBoxes-1] == botPlr) {
        printf("Bot wins! (Plr %hu)\n", botPlr);
    } else {
        printf("Human wins! (Plr %hu)\n", (botPlr == 1)? 2 : 1);
    }
    return;
}

int main(void) {
    // Config
    unsigned short vsType = 2; // 1 = PVP, 2 = PVE

    // Init
    unsigned short callBack, numBoxes;
    unsigned botPlr; // 1 = bot player1, 2 = bot player2
    srand(time(NULL)); // for random bot algorithm.

    // Check if PVP or PVE
    if (vsType == 1) {
        // Player 1 chooses number of boxes
        printf("Player 1 choose number of boxes: ");
        callBack = scanf("%hu", &numBoxes);
        if (callBack != 1) { // Scanf fails
            printf("Error scanf-ing number of boxes\n");
            return 1;
        } else if (numBoxes < 10 || numBoxes > 15) { // Range fails
            printf("Please enter a valid box between 10-15\n");
            return 1;
        }
    } else if (vsType == 2) {
        // Random start (1 means bot is plr1, 2 means bot is plr2)
        botPlr = (rand() % 2) + 1;
        if (botPlr == 2) {
           printf("Human choose number of boxes: ");
            callBack = scanf("%hu", &numBoxes);
            if (callBack != 1) { // Scanf fails
                printf("Error scanf-ing number of boxes\n");
                return 1;
            } else if (numBoxes < 10 || numBoxes > 15) { // Range fails
                printf("Please enter a valid box between 10-15\n");
                return 1;
            } 
        } else if (botPlr == 1) { // IF BOT IS PLAYER 1
            numBoxes = (rand() % (6)) + 10; // Optimize this to only choose 12 or 15
            printf("Bot is choosing number of boxes... Bot chose: %hu\n", numBoxes);
        }
    }

    // Generate boxes
    printf("Generating %hu boxes:\n", numBoxes);
    unsigned short* boxArray = malloc(numBoxes * sizeof(unsigned short));
    if (boxArray == NULL) {
        printf("Malloc malfunction\n");
        return 1;
    }
    for (int i = 0; i < numBoxes; i++) {
        boxArray[i] = 0; // Initialize all boxes as empty (not ticked)
    }

    // Print layout
    printBoxes(boxArray, numBoxes);
    
    // Play the game against a player (PVP)
    switch (vsType)
    {
    case 1:
        PVP(boxArray, numBoxes);
        break;
    case 2:
        PVE(boxArray, numBoxes, botPlr);
        break;
    default:
        break;
    }
    


    // Free heap
    free(boxArray);

    return 0;
}