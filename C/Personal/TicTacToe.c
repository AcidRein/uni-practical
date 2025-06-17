#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// For next time me:
// Change the botDecisionTable to be array pointer, pointing at different address values. 
// This makes it easier to store in previousMoves as a pointer, for O(1) reference

#define TRUE 1
#define FALSE 0

// ==================== Board Game Config ==========================
// Create new tic tac toe board
char** createBoard(){
    char** rowBoard = malloc(3 * sizeof(char*));
    if (rowBoard == NULL) return NULL;

    for (int i = 0; i < 3; i++) {
        char* colBoard = malloc(3 * sizeof(char));
        if (colBoard == NULL) {
            for (int j = 0; j < i-1; j++) {
                free(rowBoard[j]);
            }
            free(rowBoard);
            printf("Failed allocating column %d\n", i);
            return NULL;
        }

        rowBoard[i] = colBoard;
    }

    return rowBoard;
}

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

    return '-'; // No winnners yet
}

void printBoard(char** board) {
    printf("============================\n");
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

}

// =========================== General Utility functions ======================================
unsigned short moveIsLegal(char** board, int choiceRow, int choiceCol) {
    if (board[choiceRow][choiceCol] != 'O' && board[choiceRow][choiceCol] != 'X') {
        return TRUE; 
    } else {
        return FALSE;
    }
}

// ============================ Bot Decision ====================================================
// Bot decision is inspired by the MENACE matchbox TicTacToe AI!

struct botMind {
    unsigned int boardCode; // The boardCode for holding games played. Refer to 'boardToCode' function
    // Array of 2-digit numbers, where first digit (%1) is column, and second digit(%10) is row. (1-INDEXED!)
    unsigned short* possibleMoves; // example. first column, third row would be 13
    unsigned short moveLength; // Size of possibleMoves
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
    unsigned short curIter = 1, temp;
    for (int r = 2; r >= 0; r--) {
        for (int c = 2; c >= 0; c--) {
            temp = (board[r][c] == 'X') ? 2 : (board[r][c] == 'O') ? 3 : 1;
            code = code + (temp * pow(10, curIter));
            curIter++;
        }
    }

    return code;
}

struct botMind createNewMemory(char** board, struct botMind* botDecisionTable, int* decisionTableSize, int* decisionTableMaxSize, char position, int boardCode) {
    struct botMind newMemory; // New memory
    if (*decisionTableSize + 1 == *decisionTableMaxSize) { // If max size is about to be reached, double it
        *decisionTableMaxSize = *decisionTableMaxSize * 2;
    }
    struct botMind* temp = realloc(botDecisionTable, *decisionTableMaxSize * sizeof(struct botMind*));
    if (temp == NULL) {
        printf("Error reallocating decision table new size %d.\n", *decisionTableMaxSize);
        newMemory.boardCode = 1; // BoardCode 1 as a signal
        return newMemory;
    }
    botDecisionTable = temp;

    // MENACE RULES states to use 3 starting beads for each turn, so multiply choices by 3
    unsigned short* possibleMoves = malloc(9 * 3 * sizeof(unsigned short));
    if (possibleMoves == NULL) {
        printf("Error creating possible Moves Board Code: %d.\n", boardCode);
        newMemory.boardCode = 1; // BoardCode 1 as a signal
        return newMemory;
    }

    unsigned short temp; // Holds found available move 
    unsigned int movesIndex = 0;

    // Loop through board to find available moves.
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (moveIsLegal(board, r, c) == TRUE) { // On legal move
                temp = ((r+1) * 10) + (c+1); // Row|Col, 1-indexed
                for (int i = 0; i < 3; i++) { // Add 3x the moves to the possibleMoves selection
                    possibleMoves[movesIndex] = temp;
                    movesIndex++;
                }
            }
        }
    }
    
    // Reallocate for better memory management
    unsigned short* temp = realloc(possibleMoves, movesIndex * sizeof(unsigned short));
    if (temp == NULL) {
        printf("Error creating new Memory");
        free(possibleMoves);
        newMemory.boardCode = 1;
        return newMemory;
    }
    possibleMoves = temp;
    
    *(decisionTableSize)++; // Increment decisiontable size counter

    // Store boardCode, possibleMoves, and possibleMovesLength inside struct
    newMemory.boardCode = boardCode;
    newMemory.possibleMoves = possibleMoves;
    newMemory.moveLength = movesIndex;

    // Place struct inside decistion table
    botDecisionTable[*decisionTableSize-1] = newMemory;
}

void rewardSystem(unsigned int* previousMoves, int boardCode, int position, unsigned int gameWinner, struct botMind* botDecisionTable, int* decisionTableSize) {
    
}

unsigned short botPlay(char** board, struct botMind* botDecisionTable, int* decisionTableSize, int* decisionTableMaxSize, char position, unsigned int* previousMoves, int boardCode) {
    unsigned int boardFound = FALSE;
    struct botMind memoryBoard;

    // Attempt to search for board history
    for (int i = 0; i < *decisionTableSize; i++) {
        if (botDecisionTable[i].boardCode == boardCode) { // On board code found (bot has played this sequence before.)
            memoryBoard = botDecisionTable[i];
            boardFound = TRUE;
            break;
        }
    }

    // If no board history found, create a new memory
    if (boardFound == FALSE) { // Create a new memory
        memoryBoard = createNewMemory(board, botDecisionTable, decisionTableSize, decisionTableMaxSize, position, boardCode);
        if (memoryBoard.boardCode == 1) { // On error creating memory, return
            return 1;
        }
    }

    // Use the chosen bot memory to make a random decision.
    unsigned int randomIndex = rand() % memoryBoard.moveLength;
    *previousMoves = memoryBoard.possibleMoves[randomIndex];
    previousMoves++;

    return memoryBoard.possibleMoves[randomIndex];;
}

// == Main == 
int main(void) {
    // For bot decision making
    srand(time(0));
    int dTableSize = 0;
    int dTableMaxSize = 1; // Will double every time it's reached.
    // Allows for Decision making based on boardType. Think of this as the brain, and each struct botMind as a neural link.
    struct botMind* decisionTable = malloc(dTableMaxSize * sizeof(struct botMind)); 

    unsigned short simulations = 1000;
    char botPosition, playerPosition; // Which player is X or O?
    for (int i = 0; i < simulations; i++) {
        // === Create new simulation ===
        // -- New tic tac toe board -- 
        char** ticTacToeBoard = createBoard();
        if (ticTacToeBoard == NULL) {
            printf("Error creating ticTacToeBoard.\n");
            free(decisionTable);
            return 1;
        }

        // -- Reset previousMoves bot temporary memory --
        // Store moves made by the bot, to reward them accordingly.
        unsigned int* previousMoves = malloc(5 * sizeof(unsigned int)); // Max turn you can make per game is 5

        // -- Choose who is X and O -- 

        while (FALSE) { // Loop til game finishes
            // Turn board to boardCode for bot readability
            unsigned int boardCode = boardToCode(ticTacToeBoard, botPosition); 
            // Player/Bot goes

            // Display
            printBoard(ticTacToeBoard);

            // Check winners
            char res = checkWinner(ticTacToeBoard);
            if (res == 'X' || res == 'O') {
                printf("Winner: %c\n", res);
                // Reward bot accordingly
                rewardSystem(previousMoves, boardCode, botPosition, res, decisionTable, dTableSize);
                free(ticTacToeBoard);
                free(previousMoves);
                break; // Break and continue to next simulation
            }
        }

    }

    return 0;    
}