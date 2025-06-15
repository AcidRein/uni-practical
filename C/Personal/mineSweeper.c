#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printDivider(int len) {
    // Print divider
    for (int i = 0; i < (len * 2)+1; i++) {
        printf("=");
    }
    printf("\n");
    return;
}
// Printing mines
void printMap(unsigned short** playerBoard, short ** mineMap, int rowSize, int colSize, unsigned short hidden) {
    printDivider(colSize);
    unsigned short columnLabel = 0, rowLabel = 0;

    // print • (bullet, 149) if hidden, print · if blank, print @ if bomb, else print num
    for (int r = -1; r < rowSize; r++) {
        for (int c = -1; c < colSize; c++) {

            // Printing helpful labels (thanks for the idea)
            if (r == -1 && c == -1) {
                printf("X ");
                continue;
            }
            if (r == -1) {
                printf("%hu ", columnLabel);
                columnLabel++;
                if (columnLabel > 9) {
                    columnLabel = 0;
                }
                continue;
            }
            if (c == -1) {
                printf("%hu ", rowLabel);
                rowLabel++;
                if (rowLabel > 9) {
                    rowLabel = 0;
                }
                continue;
            }

            // Printing main game
            if (playerBoard[r][c] == 0 && hidden == 1) { // If hidden from player, continue.
                printf("• ");
                continue;
            }
            if (mineMap[r][c] == -1) {
                printf("@ ");
            } else if (mineMap[r][c] == 0) {
                printf("· ");
            } else {
                printf("%hd ", mineMap[r][c]);
            }
        }
        printf("\n");
    }

    printDivider(colSize);
    return;
}
// Set random Mines ( Very unintelligent way of generating mines. will fix when i get better lol )
void generateMines(short** mineMap, int numMines, int rowSize, int colSize) {
    // Place mines in random row and column.
    // If mine exists, repeat placinng mine somewhere random.
    // After 3 repeats, it'll display a warning and skip.

    int generatedRow, generatedCol;
    int failureRate = 0;
    for (int i = 0; i < numMines; i++) {
        while (failureRate < 3) {
            generatedRow = rand() % (rowSize);
            generatedCol = rand() % (colSize);
            if (mineMap[generatedRow][generatedCol] == -1) {
                failureRate++;
            } else {
                failureRate = 0;
                mineMap[generatedRow][generatedCol] = -1;
                break;
            }
        }
        if (failureRate >= 3) {
            printf("Failed to place mine after 3 attempts. Skipping...\n");
        }
    }

    return;
}

// Counting Mines ( not mine )
void countMines(short int** mineMap, int rowSize, int colSize) {
    short unsigned int minesFound;
    int offsets[8][2] = { {-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1} };

    for (int r = 0; r < rowSize; r++) {
        for (int c = 0; c < colSize; c++) {
            // If current is a mine, skip
            if (mineMap[r][c] == -1) {
                continue;
            }
            minesFound = 0;

            // Iterate through offsets
            for (int i = 0; i < 8; i++) {
                int newR = r + offsets[i][0];
                int newC = c + offsets[i][1];

                // Bounds check 
                if (newR >= 0 && newR < rowSize && newC >= 0 && newC < colSize) {
                    if (mineMap[newR][newC] == -1) {
                        minesFound++;
                    }
                }
            }

            mineMap[r][c] = (short) minesFound;
        }
    }
}

// Recursively open up the map if no mines found around it.
void recursiveFlood(unsigned short** playerBoard, short ** mineMap, int rowSize, int colSize, int chosenRow, int chosenCol) {
    /* Rule
    - If you click a square and it has no mines in its surrounding eight tiles, it is considered a "blank" square.
    - The game then automatically reveals all adjacent (all eight neighboring) blank squares.
    - If any of those newly revealed squares are also blank, the process repeats recursively, clearing large sections of the board.
    - The chain reaction stops when a square with a number (indicating nearby mines) is reached.
    */
    int offsets[8][2] = { {-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1} };
    playerBoard[chosenRow][chosenCol] = 1; // Make chosen seen

    // Iterate through offsets
    for (int i = 0; i < 8; i++) {
        int newR = chosenRow + offsets[i][0];
        int newC = chosenCol + offsets[i][1];

        // Bounds check 
        if (newR >= 0 && newR < rowSize && newC >= 0 && newC < colSize) {
            // If within bounds
            if (playerBoard[newR][newC] == 1) {
                // If player has already seen this square
                continue;
            } else { // If player has not seen this square
                if (mineMap[newR][newC] != -1) { // If square is blank
                    if (mineMap[chosenRow][chosenCol] == 0) { // don't show adjacent if not chosen a blank
                        playerBoard[newR][newC] = 1; // Make seen
                    }

                    if (mineMap[newR][newC] == 0) {// On blank square, 
                        // call recursive around it.
                        recursiveFlood(playerBoard, mineMap, rowSize, colSize, newR, newC);
                    }
                } 
            }
        }
    }
}

unsigned short playerWon(unsigned short** playerBoard, short ** mineMap, int rowSize, int colSize) {
    for (int r = 0; r < rowSize; r++) {
        for (int c = 0; c < colSize; c++) {
            if ((playerBoard[r][c] == 0) && (mineMap[r][c] != -1)) { // On undiscovered free square, return false
                return 1;
            }
        }
    }
    return 0;
}

int main(void) {
    // Init Random
    srand(time(0));

    // Game Config =============
    int numMines = 10;
    int rowSize = 10, columnSize = 10;
    // =========================

    // Board generation
    // 0 for no bombs, -1 for a bomb, n for n bombs nearby
    short** mineMap = malloc(rowSize * sizeof(short*));
    if (mineMap == NULL) {
        printf("Error malloc for mineMap\n");
        return 1;
    }
    for (int i = 0; i < rowSize; i++) {
        mineMap[i] = malloc(columnSize * sizeof(short));
        for (int c = 0; c < columnSize; c++) {
            mineMap[i][c] = 0; // No bombs nearby
        }
    }
    
    // Player Board Generation (What the player can see)
    // 0 for hidden, 1 for can see
    unsigned short** playerBoard = malloc(rowSize * sizeof(unsigned short*));
    if (playerBoard == NULL) {
        printf("Error malloc for mineMap\n");
        return 1;
    }
    for (int i = 0; i < rowSize; i++) {
        playerBoard[i] = malloc(columnSize * sizeof(unsigned short));
        for (int c = 0; c < columnSize; c++) {
            playerBoard[i][c] = 0; // Hidden
        }
    }

    // Fill board with mines
    generateMines(mineMap, numMines, rowSize, columnSize);

    // Count mine and update board
    countMines(mineMap, rowSize, columnSize);

    // Display what the player sees.
    printMap(playerBoard, mineMap, rowSize, columnSize, 1);
    
    // ===== Main Game ========
    unsigned short userInputRow, userInputCol, callBackRow, callBackCol;
    while (1) {
        // Prompt user to select a square
        printf("Enter Row: ");
        callBackRow = scanf("%hd", &userInputRow);
        printf("Enter Col: ");
        callBackCol = scanf("%hu", &userInputCol);

        // Wait til user inputs a valid number
        while (callBackRow != 1 && callBackCol != 1) {
            printf("Invalid number! Try again\n");
            while (getchar() != '\n');
            printf("Enter Row: ");
            callBackRow = scanf("%hd", &userInputRow);
            printf("Enter Col: ");
            callBackCol = scanf("%hu", &userInputCol);
        }

        // Force quit.
        if (userInputRow == -1 || userInputCol == -1) {
            break;
        }

        // Check if row and column in range
        if (!((userInputRow >= 0) && (userInputRow < rowSize) && (userInputCol >= 0) && (userInputCol < columnSize))) {
            printf("Enter a number within range! (0-index)\n");
            continue;
        }

        // Check if user clicks on a mine
        if (mineMap[userInputRow][userInputCol] == -1) {
            printf("YOU LOSE! Row Chosen: (%hu), Col Chosen: (%hu)\n", userInputRow, userInputCol);
            break;
        }

        // Check if user is trying to re-click an already discovered path
        if (playerBoard[userInputRow][userInputCol] == 1) {
            printf("You already discovered this...\n");
            continue;
        }
    
        // Call the recursive fill function
        recursiveFlood(playerBoard, mineMap, rowSize, columnSize, userInputRow, userInputCol);

        // Check if player has won
        if (playerWon(playerBoard, mineMap, rowSize, columnSize) == 0) {
            printf("YOU WIN!\n");
            break;
        }
        // Display what the player sees.
        printMap(playerBoard, mineMap, rowSize, columnSize, 1);

        
    }

    // On game end
    printMap(playerBoard, mineMap, rowSize, columnSize, 0); // Display full map

    // Free memory
    for (int i = 0; i < rowSize; i++) {
        free(mineMap[i]);
        free(playerBoard[i]);
    }
    free(mineMap);
    free(playerBoard);
    
}