#include <stdlib.h>
#include <stdio.h>

// A function to check  if a value is within an array.
int valueInArray(int value, int array[]) {
   for (int i = 0; i < 3; i++) {
      if (value == array[i]) {
         return 1;
      }
   }

   return 0;
}


int main(void) {
   int runnerColumns[3] = {2, 4, 11}; // An array representing the columns the runners are in [Use (3, 8,4) and (2, 4, 11) to fulfill this assignment]

   // Initialize Counters, Counting the numbers of advances (success) or busts (failure) that occurs during our simulation
   double success = 0;
   double failure = 0;
   int gameTime = 1296; // 6^4 = 1296, Number of Dice simulated

   // Simulate all four dice rolls O(6^4) time complexity
   for (int fir = 1; fir <= 6; fir++) {
      for (int sec = 1; sec <= 6; sec++) {
         for (int thi = 1; thi <= 6; thi++) {
            for (int fou = 1; fou <= 6; fou++) {

               // Check if any given combination of rolls can advance one of the 3 runners in "runnerColumns"
               if ((valueInArray(fir+sec, runnerColumns) == 1) || (valueInArray(fir+thi, runnerColumns) == 1) || (valueInArray(fir+fou, runnerColumns) == 1)
                  || (valueInArray(sec+thi, runnerColumns) == 1) || (valueInArray(sec + fou, runnerColumns) == 1) || (valueInArray(thi+fou, runnerColumns) == 1)){
                  
                  // If a runner can be advanced given any of the dice rolls,
                  success++; // Increment Advance counter
               } else {
                  // Otherwise if no runners can be advanced
                  failure++; // Increment Bust counter
               }
            }
         }
      }
   }  

   // Calculate probability and Print output
   double probabilityOfAdvancing = success/gameTime;
   double probabilityOfBusting = failure/gameTime;
   printf("Numbers of Simulations ran: %d\n", gameTime);
   printf("Numbers of Advances available: %.0lf\nNumbers of Failures available: %.0lf\n", success, failure);
   printf("Probability of Advancing: %lf\nProbability of Busting: %lf\n", probabilityOfAdvancing, probabilityOfBusting);

   return 0;
   
}