#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

// There's no built-in C maps/hash so no O(1) lookups.
// I guess we'll have to loop through all decision table *EVERY SEARCH* >:(

#define TRUE 1
#define FALSE 0

// =========================== General Utility functions ======================================
unsigned int moveIsLegal(char** board, unsigned short choiceRow, unsigned short choiceCol) {
    if (board[choiceRow][choiceCol] != 'O' && board[choiceRow][choiceCol] != 'X') {
        return TRUE; 
    } else {
        return FALSE;
    }
}

unsigned int* removeElementFromHeap(unsigned int* mainArray, unsigned int arraySize, unsigned int elementToRemove, unsigned int amountToRemove) {
    // printf("Removing %hu of the number %hu from an array of size %u...\n", amountToRemove, elementToRemove, arraySize);
    // Dont removev anything if array size is 1.
    if (arraySize <= 1) {
        return NULL;
    }
    unsigned int alreadyRemoved = 0;
    // Create a new array that will hold the modified values
    unsigned int* newReturnArray = malloc(arraySize * sizeof(unsigned int));
    if (newReturnArray == NULL) {
        printf("Error in newReturnArray\n");
        return NULL;
    }

    unsigned int newArrayIndex = 0;
    for (int i = 0; i < arraySize; i++) { // Go through main
        if (mainArray[i] == elementToRemove) { // check if is the element to remove
            if (alreadyRemoved < amountToRemove) {
                alreadyRemoved++; // dont add it in the new array
                continue;
            }
        }
        newReturnArray[newArrayIndex] = mainArray[i];
        newArrayIndex++;
    }

    // Reallocate new return array
    unsigned int* newReturnArray2 = realloc(newReturnArray, newArrayIndex * sizeof(unsigned int));
    if (newReturnArray2 == NULL) {
        printf("Error2 in newRturnArray\n");
        free(newReturnArray);
        return NULL;
    }

    return newReturnArray2;
}

// ======================== Save and load function here ==================================

// ==================== Board Game Config ==========================
// Create new tic tac toe board
char** createBoard(){
    char** rowBoard = malloc(3 * sizeof(char*));
    if (rowBoard == NULL) return NULL;

    for (int i = 0; i < 3; i++) {
        char* colBoard = malloc(3 * sizeof(char));
        if (colBoard == NULL) {
            printf("Failed allocating column %d\n", i);
            for (int j = 0; j < i; j++) {
                free(rowBoard[j]);
            }
            free(rowBoard);
            return NULL;
        }

        for (int j = 0; j < 3; j++) {
            colBoard[j] = '.';
        }

        rowBoard[i] = colBoard;
    }


    return rowBoard;
}

// 'X' or 'O' for a winner, '-' for draw, '.' for nothing
char checkWinner(char** board) {
    char temp = '-';

    // Check Row wins
    for (int r = 0; r < 3; r++){
        for (int c = 0; c < 3; c++) {
            if (c == 0) { // On first iteration
                temp = board[r][c];
            } else if (temp != board[r][c]){
                temp = '-';
                break; // Stop checking this row
            } 
            if (c == 2) { // On last check
                if (temp != '-') { // If three in a row
                    return temp; // // return winner
                }
            }
        }
    }

    // Check Col wins
    for (int c = 0; c < 3; c++){
        for (int r = 0; r < 3; r++) {
            if (r == 0) { // On first iteration
                temp = board[r][c];
            } else if (temp != board[r][c]){
                temp = '-';
                break;
            } 
            if (r == 2) { // On last check
                if (temp != '-') { // If three in a row
                    return temp; // // return winner
                }
            }
        }
    }

    // Main diagonal
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && (board[0][0] == 'O' || board[0][0] == 'X'))
        return board[0][0];

    // Anti-diagonal
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && (board[0][2] == 'O' || board[0][2] == 'X')) {
        return board[0][2];
    }

    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (moveIsLegal(board, r, c) == TRUE) { // On legal move
                return '.'; // If still legal move, return continue
            }
        }
    }
    return temp; // return Draw
}

void printBoard(char** board) {
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (board[r][c] == 'X' || board[r][c] == 'O') {
                printf("%c ", board[r][c]);
            } else {
                printf("· ");
            }
        }
        printf("\n");
    }
    printf("==============\n");
}

// ============================ Bot Decision ====================================================
// Bot decision is inspired by the MENACE matchbox TicTacToe AI!

struct botMind {
    unsigned int boardCode; // The boardCode for holding games played. Refer to 'boardToCode' function
    // Array of 2-digit numbers, where first digit (%1) is column, and second digit(%10) is row. (1-INDEXED!)
    unsigned int* possibleMoves; // example. first column, third row would be 13
    unsigned int moveLength; // Size of possibleMoves
};

unsigned int boardToCode(char** board, char position) {
    // Board to code.
    // 1 means empty, 2 means X, 3 means O, trailing end number means position played as
    // Example. Given the board with bot playing as X:
    /*
    X - x 
    O X O
    - - O
    */

    // The board code is 2123231132, with the last two being 'X' as our position
    unsigned int code = (position == 'X') ? 2 : (position == 'O') ? 3 : 1; // end code as position
    unsigned int curIter = 1, temp;
    for (int r = 2; r >= 0; r--) {
        for (int c = 2; c >= 0; c--) {
            temp = (board[r][c] == 'X') ? 2 : (board[r][c] == 'O') ? 3 : 1;
            code = code + (temp * pow(10, curIter));
            curIter++;
        }
    }

    return code;
}

struct botMind createNewMemory(char** board, struct botMind** botDecisionTable, unsigned int* decisionTableSize, unsigned int* decisionTableMaxSize, char position, int boardCode) {
    //printf("Creating new memory...\n");

    struct botMind newMemory; // New memory
    if (*decisionTableSize >= *decisionTableMaxSize) { // If max size is reached, double max size it
        *decisionTableMaxSize = *decisionTableMaxSize * 2;
        struct botMind* temp = realloc(*botDecisionTable, *decisionTableMaxSize * sizeof(struct botMind));
        if (temp == NULL) {
            printf("Error reallocating decision table new size %d.\n", *decisionTableMaxSize);
            newMemory.boardCode = 99; // BoardCode 99 as a signal it failed
            return newMemory;
        }
        *botDecisionTable = temp;
    }
    

    // MENACE RULES states to use 3 starting beads for each turn, so multiply choices by 3
    unsigned int* possibleMoves = malloc(9 * 3 * sizeof(unsigned int));
    if (possibleMoves == NULL) {
        printf("Error creating possible Moves Board Code: %d.\n", boardCode);
        newMemory.boardCode = 99; // BoardCode 99 as a signal
        return newMemory;
    }

    unsigned int tempValue; // Holds found available move 
    unsigned int movesIndex = 0;

    // Loop through board to find available moves.
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (moveIsLegal(board, r, c) == TRUE) { // On legal move
                tempValue = ((r+1) * 10) + (c+1); // Row|Col, 1-indexed
                for (int i = 0; i < 3; i++) { // Add 3x the moves to the possibleMoves selection
                    possibleMoves[movesIndex] = tempValue;
                    movesIndex++;
                }
            }
        }
    }

    if (movesIndex == 0) { // No legal moves
        printf("No legal moves available BC: %u.\n", boardCode);
        free(possibleMoves);
        newMemory.boardCode = 99; // BoardCode 99 as a signal
        return newMemory;
    }
    
    // Reallocate for better memory management
    unsigned int* tempNewMoves = realloc(possibleMoves, movesIndex * sizeof(unsigned int));
    if (tempNewMoves == NULL) {
        printf("Error creating new Memory");
        free(possibleMoves);
        newMemory.boardCode = 99;
        return newMemory;
    }

    possibleMoves = tempNewMoves;

    // Store boardCode, possibleMoves, and possibleMovesLength inside struct
    newMemory.boardCode = boardCode;
    newMemory.possibleMoves = possibleMoves;
    newMemory.moveLength = movesIndex;

    // Place struct inside decistion table
    (*botDecisionTable)[*decisionTableSize] = newMemory;
    *decisionTableSize = *decisionTableSize + 1; // Increment decisiontable size counter after insertion

    return newMemory;
}


void rewardSystem(unsigned int** previousMoves, unsigned int turnsMade, char position, char gameWinner, struct botMind** botDecisionTable, unsigned int* decisionTableSize) {
    // Reward 3 per win, Reward 1 per draw, Remove 1 per loss
    int change = (gameWinner == position) ? 3 : (gameWinner == '-') ? 1 : -1;
    
    // Calculate how many moves the bot made
    unsigned int movesMade = (position == 'X') ? ((turnsMade+1)/2) : (turnsMade/2); // ceil on X, floor on O

    // Init
    struct botMind* memoryBoard;
    unsigned int boardCode;

    // For each previous move, find the boardCode and what move the bot played
    for (int i = 0; i < movesMade; i++) {
        boardCode = (*previousMoves)[2 * i]; // 1st element is the boardCode
        //printf("BoardCode: %u, Move: %hu\n", boardCode, (*previousMoves)[(2 * i) + 1]);

        // Search for board history. It must exist already
        memoryBoard = NULL;
        for (int j = 0; j < *decisionTableSize; j++) {
            if ((*botDecisionTable)[j].boardCode == boardCode) {
                memoryBoard = &(*botDecisionTable)[j];
                break;
            }
        }
        if (memoryBoard == NULL) {
            printf("No memory found for boardCode: %u\n", boardCode);
            continue;
        }


        // Make changes to the possiblemoves for that memory boardCode.
        if (memoryBoard->moveLength + change < 0) { // If no more moves on this table, just clear it entirely.
            printf("FOUND ERROR!: %hu\n", memoryBoard->moveLength);
            return;
        }
        
        // On reward, increase possibleMoves and add.
        if (change > 0) {
            unsigned int* tempNewPossibility = realloc(memoryBoard->possibleMoves, (memoryBoard->moveLength + change) * sizeof(unsigned int));
            if (tempNewPossibility == NULL) {
                printf("Error updating memory for boardCode: %d\n", boardCode);
                continue;
            }
            // Reward 
            unsigned int moveToAdd = (*previousMoves)[(2 * i) + 1];
            for (int a = 0; a < change; a++) {
                tempNewPossibility[memoryBoard->moveLength + a] = moveToAdd;
            }

            memoryBoard->possibleMoves = tempNewPossibility;
        // On punishment, decrease and remove.
        } else if (change < 0) {
            unsigned int* updatedArray = removeElementFromHeap(memoryBoard->possibleMoves, memoryBoard->moveLength, (*previousMoves)[(2 * i) + 1], abs(change));

            if (updatedArray == NULL) {
                continue;
            }

        free(memoryBoard->possibleMoves);  // Free old data
        memoryBoard->possibleMoves = updatedArray;

        }
        // Update new possibleMOves size based on the reward system
        (*memoryBoard).moveLength = (*memoryBoard).moveLength + change;
    }
    return;
}

char botPlay(char** board, struct botMind** botDecisionTable, unsigned int* decisionTableSize, unsigned int* decisionTableMaxSize, char position, unsigned int** previousMoves, unsigned int turnsMade, unsigned int boardCode) {
    //printf("Making a move for %c... This is turn: %hu\n", position, turnsMade);
    //printBoard(board);

    unsigned int boardFound = FALSE;
    struct botMind* memoryBoard = NULL;  // Change to pointer
    
    // Attempt to search for board history
    for (int i = 0; i < *decisionTableSize; i++) {
        if ((*botDecisionTable)[i].boardCode == boardCode) {
            memoryBoard = &((*botDecisionTable)[i]);  // Get pointer to original
            boardFound = TRUE;
            break;
        }
    }

    // If no board history found, create a new memory
    if (boardFound == FALSE) {
        struct botMind newMemory = createNewMemory(board, botDecisionTable, decisionTableSize, decisionTableMaxSize, position, boardCode);
        if (newMemory.boardCode == 99) {
            printf("Error creating a new memory for boardcode: %u\n", boardCode);
            return 1;  // Return 1 on error
        }
        memoryBoard = &((*botDecisionTable)[*decisionTableSize - 1]);  // Point to the newly added memory
    }
    
    // Use the chosen bot memory to make a random decision.
    unsigned int randomIndex = rand() % memoryBoard->moveLength;
    unsigned int movesMade = (position == 'X') ? (turnsMade + 1) / 2 : turnsMade / 2; // moves 'about' to be made.
    
    // Store move about to be made into temp storage
    int index = 2 * (movesMade - 1);
    (*previousMoves)[index] = boardCode;
    (*previousMoves)[index + 1] = memoryBoard->possibleMoves[randomIndex];
    
    // Make the move
    return memoryBoard->possibleMoves[randomIndex];
}

struct botMind* trainBot(unsigned int simulations, unsigned int* bot1Wins, unsigned int* bot2Wins, unsigned int* bot1TableSize, unsigned int* bot2TableSize, unsigned int* bot1MaxSize, unsigned int* bot2MaxSize) {
    // ======== Create 2 minds to go against each other
    // Allows for Decision making based on boardType. Think of this as the brain, and each struct botMind as a neural link.
    struct botMind* bot1DecisionTable = malloc(*bot1MaxSize * sizeof(struct botMind)); // create new memory

    struct botMind* bot2DecisionTable = malloc(*bot2MaxSize * sizeof(struct botMind));     

    char bot1Position, bot2Position, whoPlays; // Which player is X or O?
    unsigned int bot1Value, bot2Value; // The play the bot wants to make. 2 digit number, 1-indexed
    unsigned int currentTurn; // Up to 9, to determine a draw

    // Bot VS Bot simuluations time.
    for (unsigned int i = 0; i < simulations; i++) {
        printf("Bot sim: %u\n", i);
        // === Create new simulation ===
        // -- New tic tac toe board -- 
        char** ticTacToeBoard = createBoard();
        //printf("New board created: \n");
        //printBoard(ticTacToeBoard);

        if (ticTacToeBoard == NULL) {
            printf("Error creating Tic Tac Toe board. Simulation: %d\n", i);
            continue;
        }

        // Store moves made by the bot, to reward them accordingly. Think of it as temporary memory, like ram.
        // Max turn you can make per game is numRow = 5, stores boardCode and moveMade, numCol = 2
        unsigned int* bot1PreviousMoves = malloc(5 * 2 * sizeof(unsigned int)); // 1 dimensional 2D array. 
        unsigned int* bot2PreviousMoves = malloc(5 * 2 * sizeof(unsigned int)); // 1 dimensional 2D array. 

        // -- Choose who is X and O -- 
        if (rand() % 2 == 1) {
            bot1Position = 'X';
            bot2Position = 'O';
        } else {
            bot1Position = 'O';
            bot2Position = 'X';
        }
        whoPlays = 'X'; // X always go first

        // Initialise turn
        currentTurn = 1;
        while (TRUE) { // Loop til game finishes
            // Turn board to boardCode for bot readability
            unsigned int boardCode = boardToCode(ticTacToeBoard, whoPlays); 

            // bot1/bot2 goes
            if (whoPlays == bot1Position) {
                bot1Value = botPlay(ticTacToeBoard, &bot1DecisionTable, bot1TableSize, bot1MaxSize, bot1Position, &bot1PreviousMoves, currentTurn, boardCode);
                if (bot1Value == 1) {
                    printf("Error in bot1 play. Board Code: %u\n", boardCode);
                    continue;
                }
                // Update board. given xy, x is row, y is column.
                ticTacToeBoard[(bot1Value / 10)-1][(bot1Value % 10)-1] = bot1Position;
            } else if (whoPlays == bot2Position) {
                bot2Value = botPlay(ticTacToeBoard, &bot2DecisionTable, bot2TableSize, bot2MaxSize, bot2Position, &bot2PreviousMoves, currentTurn, boardCode);
                if (bot2Value == 1) {
                    printf("Error in bot2 play. Board Code: %u\n", boardCode);
                    continue;
                }
                // Update board. given xy, x is row, y is column.
                ticTacToeBoard[(bot2Value / 10)-1][(bot2Value % 10)-1] = bot2Position;
            }

            // Check winners
            char res = checkWinner(ticTacToeBoard);
            if (res != '.') { // On a winner or draw, finish the game.
                //printf("GAME COMPLETE! Final board:\n");
                //printBoard(ticTacToeBoard);
                // Reward each bot accordingly (win/lose/draw)
                rewardSystem(&bot1PreviousMoves, currentTurn, bot1Position, res, &bot1DecisionTable, bot1TableSize);
                rewardSystem(&bot2PreviousMoves, currentTurn, bot2Position, res, &bot2DecisionTable, bot2TableSize);
                
                // Counter
                if (res == bot1Position) {
                    (*bot1Wins)++;
                } else if (res == bot2Position) {
                    (*bot2Wins)++;
                }

                // Clear simulation's memory
                for (int i = 0; i < 3; i++) {
                    free(ticTacToeBoard[i]);
                }
                free(ticTacToeBoard);
                free(bot1PreviousMoves);
                free(bot2PreviousMoves);
                break; // Break and continue to next simulation
            }
            currentTurn++;
            whoPlays = (whoPlays == bot1Position) ? bot2Position : bot1Position;
            
        }

    }

    // Return the mind of the winner and free the mind of the loser - i felt so cool writing that
    if (*bot1Wins > *bot2Wins) {
        for (int i = 0; i < *bot2TableSize; i++) {
            free(bot2DecisionTable[i].possibleMoves);
        }
        free(bot2DecisionTable);
        
        return bot1DecisionTable;
    } else {
        for (int i = 0; i < *bot1TableSize; i++) {
            free(bot1DecisionTable[i].possibleMoves);
        }
        free(bot1DecisionTable);
        return bot2DecisionTable;
    }
}

// == Main == 
int main(void) {
    // ==== Sim configs ====
    unsigned int simulations = 1000000; 
    // Easy mode - Simulations 100k (100000) or under
    // Medium - Simulations 1M (1000000)
    // Hard (or impossible, idk) - Simulations 10M+ (10000000)
    unsigned int gamesToPlay = 3; // How many games you want to play with the bot after it has learnt?
    // ====================

    // For bot decision making
    srand(time(0));
    unsigned int bot1TableSize = 0; // how big their brain is
    unsigned int bot2TableSize = 0;
    unsigned int bot1MaxSize = 1; // the maximum size of the brain (doubles every time it's reached)
    unsigned int bot2MaxSize = 1;
    unsigned int bot1Wins = 0, bot2Wins = 0; // Wins counter

    // Make it go head-to-head with another bot, and vs the winner
    struct botMind* winningBot = trainBot(simulations, &bot1Wins, &bot2Wins, &bot1TableSize, &bot2TableSize, &bot1MaxSize, &bot2MaxSize);
    unsigned int* winnerBotTableSize = (bot1Wins > bot2Wins) ? &bot1TableSize : &bot2TableSize;
    unsigned int* winnerBotMaxSize = (bot1Wins > bot2Wins) ? &bot1MaxSize : &bot2MaxSize;
    // Optionally, make it go head-to-head with an optimal bot, it it turns out stupid no matter what lmao
    // TBA

    char botPosition, playerPosition, whoPlays; // Which player is X or O?
    unsigned short botValue;// The play the bot wants to make. 2 digit number, 1-indexed
    unsigned short playerRow, playerColumn; // The play player wants to make, 1-indexed
    unsigned int currentTurn; // Up to 9, to determine a draw
    int callBack; // scanf error handling

    printf("Bot is ready to play after %u simulations\nBot 1 wins: %u, Bot 2 wins: %u\n", simulations, bot1Wins, bot2Wins);

    // Player VS Bot simuluations time.
    for (unsigned int i = 0; i < gamesToPlay; i++) {
        // === Create new simulation ===
        // -- New tic tac toe board -- 
        char** ticTacToeBoard = createBoard();
        if (ticTacToeBoard == NULL) {
            printf("Error creating Tic Tac Toe board: %d\n", i);
            continue;
        }

        unsigned int* botPreviousMoves = malloc(5 * 2 * sizeof(unsigned int)); // 1 dimensional 2D array. 

        // -- Choose who is X and O -- 
        if (rand() % 2 == 1) {
            botPosition = 'X';
            playerPosition = 'O';
        } else {
            botPosition = 'O';
            playerPosition = 'X';
        }
        whoPlays = 'X'; // X always go first

        // Initialise turn
        currentTurn = 1;
        while (TRUE) { // Loop til game finishes
            // Turn board to boardCode for bot readability
            unsigned int boardCode = boardToCode(ticTacToeBoard, whoPlays); 

            // Display on player
            if (whoPlays == playerPosition) {
                printBoard(ticTacToeBoard);
            }

            // bot/player goes
            if (whoPlays == botPosition) {
                botValue = botPlay(ticTacToeBoard, &winningBot, winnerBotTableSize, winnerBotMaxSize, botPosition, &botPreviousMoves, currentTurn, boardCode);
                if (botValue == 1) {
                    printf("Error in bot1 play. Board Code: %u\n", boardCode);
                    continue;
                }
                // Update board. given xy, x is row, y is column.
                ticTacToeBoard[(botValue / 10)-1][(botValue % 10)-1] = botPosition;

            } else if (whoPlays == playerPosition) {
                playerRow = 0, playerColumn = 0;

                // Repeat until a legal move is entered
                while (TRUE) {
                    printf("You are (%c), enter row and column (1-3): ", playerPosition);

                    // Get row
                    callBack = scanf("%hu", &playerRow);
                    if (callBack != 1 || playerRow < 1 || playerRow > 3) {
                        printf("Invalid row input! Please enter a number between 1 and 3.\n");
                        while (getchar() != '\n'); // Clear input buffer
                        continue;
                    }

                    // Get column
                    callBack = scanf("%hu", &playerColumn);
                    if (callBack != 1 || playerColumn < 1 || playerColumn > 3) {
                        printf("Invalid column input! Please enter a number between 1 and 3.\n");
                        while (getchar() != '\n');
                        continue;
                    }

                    // Check legality of move
                    if (moveIsLegal(ticTacToeBoard, playerRow-1, playerColumn-1) == FALSE) {
                        printf("Cell already occupied.\n");
                        continue;
                    }

                    // All checks passed—break the loop
                    break;
                }


                
                // Update board
                ticTacToeBoard[playerRow-1][playerColumn-1] = playerPosition;
            }

            // Check winners
            char res = checkWinner(ticTacToeBoard);
            if (res != '.') { // On a winner or draw, finish the game.
                printf("GAME COMPLETE WINNER: %c! Final board:\n", res);
                printBoard(ticTacToeBoard);
                // Reward bot accordingly (win/lose/draw)
                rewardSystem(&botPreviousMoves, currentTurn, botPosition, res, &winningBot, winnerBotTableSize);

                //  free heaps
                for (int i = 0; i < 3; i++) {
                    free(ticTacToeBoard[i]);
                }
                free(ticTacToeBoard);
                free(botPreviousMoves);
                break; // Break and continue to next simulation
            }
            currentTurn++;
            whoPlays = (whoPlays == botPosition) ? playerPosition : botPosition;
            
        }

    }


    // Free bot memory
    for (int i = 0; i < *winnerBotTableSize; i++) {
        free(winningBot[i].possibleMoves);
    }
    free(winningBot);

    return 0;    
}