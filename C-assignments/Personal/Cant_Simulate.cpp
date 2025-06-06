#include <bits/stdc++.h>
#include <cstdlib>
#include <map>
#include <vector>
using namespace std;

// Generate an array of four dice rolls
vector<int> generateDice() {
    vector<int> myDices(4);
    for (int i = 0; i < 4; i++) {
        int randomNum = (rand() % 6) + 1;
        myDices[i] = randomNum;
    }
    return myDices;
}

// Given 4 dices, generate each progression type
vector<pair<int, int>>  progression(vector<int> myDices) {
    vector<pair<int,int>> returnValue(3);
    returnValue[0] = {myDices[0] + myDices[1], myDices[2] + myDices[3]};
    returnValue[1] = {myDices[0] + myDices[2], myDices[1] + myDices[3]};
    returnValue[2] = {myDices[0] + myDices[3], myDices[1] + myDices[2]};
    return returnValue;
}

// Simulate by pure
int main(void) {
    // random Numbers Initializationn
    srand(time(0)); // Seed
    
    //  ================== Simulation configs =====================
    // This simulation runs on O(n*m) time
    // where n = numberOfSimualtions, m = numThrows
    int numThrows = 6; // simulate up to x throws before choosing to stop
    int numberOfSimulations = 100000000; // how many simulations
    // ==========================================================
    // Result of a "numThrows = 4" and "numberOfSimulations = 100,000,000" simulation output:
    
    

    // Counting our busts for each throw, and number of games played for specific round
    vector<pair<int, int>> bustPlays(numThrows, {0, 0}); // {number of round 'x' played, number of Busts for round 'x'}. 

    // Initializaing game variables
    map<int, int> board = { // {Number : Advances required}
        {2, 3},
        {3, 5},
        {4, 7},
        {5, 9}, 
        {6, 11},
        {7, 13},
        {8, 11},
        {9, 9},
        {10, 7},
        {11, 5},
        {12, 3}};

    // Init new game
    map<int, int> currentBoard; // the current state of the board
    vector<pair<int, int>> progressionList(3); // Player's progression list/ what they can choose to progress (three options)
    vector<int> currentRunners; // Player's runners initialization

    for (int sims = 0; sims < numberOfSimulations; sims++) {
        currentBoard = board; // generate a new board
        currentRunners.clear(); // Clear all runners

        // Run up to 'numThrows' simulation, where each throw is dependent on the last
        for (int throwRound = 0; throwRound < numThrows; throwRound++) {
            // Increment round played
            bustPlays[throwRound].first = bustPlays[throwRound].first + 1;

            // create progression list
            progressionList = progression(generateDice());
            
            // Choose a random "available" progression
            bool successfulProgression = false; // True if progression was able to be made, otherwise busted.
            for (int i = 0; i < 3; i++) {
                // chose a random progression
                pair<int, int> randomProgression = progressionList[rand() % progressionList.size()]; 
                
                auto firstProgressionRunner = std::find(currentRunners.begin(), currentRunners.end(), randomProgression.first);
                auto secondProgressionRunner = std::find(currentRunners.begin(), currentRunners.end(), randomProgression.second);

                // If the first progression is found tied to a runner
                if (firstProgressionRunner != currentRunners.end()) {
                    if (currentBoard[randomProgression.first] > 0) { // Player hasn't reached the top of this column
                        currentBoard[randomProgression.first]--;
                        successfulProgression = true;
                    }
                }

                // If the second progression is found tied to a runner
                if (secondProgressionRunner != currentRunners.end()) {
                    if (currentBoard[randomProgression.second] > 0) { // Player hasn't reached top of this column
                        currentBoard[randomProgression.second]--;
                        successfulProgression = true;
                    }
                }

                // If neither runner was found
                if ((firstProgressionRunner == currentRunners.end()) && (secondProgressionRunner == currentRunners.end())) {
                    vector<int> choices = {randomProgression.first, randomProgression.second};
                    // if there's more than two avaiable runners to be placed
                    if (currentRunners.size() < 2) {
                        currentRunners.push_back(randomProgression.first);
                        currentRunners.push_back(randomProgression.second);
                        currentBoard[randomProgression.first]--;
                        currentBoard[randomProgression.second]--;
                        successfulProgression = true;
                    } else if (currentRunners.size() == 2) { // there's exactly 1 spot
                        // Otherwise if there's only 1 slot, choose a random progression to be made
                        int choices2 = choices[rand() % choices.size()];
                        currentRunners.push_back(choices2);
                        currentBoard[choices2]--;
                        successfulProgression = true;
                    }

                } 
                
                if (successfulProgression) { // If progression was successful, stop choosing. Otherwise, go throw all the options
                    break;
                }
            }

            if (successfulProgression == false) { // If no choices were/could be made, bust
                // On bust,
                // Increment round bust counter for round 'x'
                bustPlays[throwRound].second = bustPlays[throwRound].second + 1;
                // Stop the current simulation and go to the next
                break;
            }
        }
    }
    
    cout << "Number of Simulations: " << numberOfSimulations << endl;
    cout << "Number of throws simulated: " << numThrows << endl;
    cout << "---Result of Simulation ---" << endl;

    double cumulativeBustProbability = 0.0;

    // Print our probability at the end
    for (int i = 0; i < numThrows; i++) {
        double roundBustProbability = (double)bustPlays[i].second / numberOfSimulations;
        cumulativeBustProbability += roundBustProbability;

        cout << fixed << setprecision(2); // Format percentages
        cout << (cumulativeBustProbability * 100) << "% of games bust by round " << i+1 << endl;
    }
    return 0;
}