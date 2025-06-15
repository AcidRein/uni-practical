#include <stdio.h>

// Compile with gcc {FILE_NAME1}.c -o {FILE_NAME2}
// Run code with ./{FILE_NAME2}

// =======================
// Compile all solutions with | gcc -Wall -Werror=vla -std=c11 {filename} |
// =======================

int main(void) {
    // Variable types
    int var1 = 5;
    float var2 = 5.0f; // Store up to 7 decimal digits
    double var3 = 5.0; // Store up to 15 decimal digits
    char var4 = 'a'; // Single character
    // Note: C does not have a built-in boolean type, but you can use stdbool.h for this
    
    unsigned int var5 = 5; // Unsigned integer (only positive values)
    short int var6 = 5; // Short integer (less memory usage)
    long int var7 = 5; // Long integer (more memory usage)
    const int var8 = 5; // Constant integer (cannot be changed)

    // Vectors (0 index)
    int arr1[5] = {1, 2, 3, 4, 5}; // Integer array (with defined size) (Length could be 5 or less, but not more)
    float arr2[5] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f}; // Float array (f suffix to indicate float)
    char arr3[] = "Hello"; // String (array of characters)

    // Input and output
    int intInput; // Initialize an integer variable
    char strInput[10]; // Initialize a string variable to hold 9 char

    printf("Enter an integer: ");
    scanf("%d", &intInput); // Read an integer from the user
    scanf("%s", strInput); // Read a string from the user

    printf("You entered integer: %d, and string: %s\n", intInput, strInput); // Print the integer and string

    // Print specific variable types
    printf("Integer: %d, Float: %.2f, Double: %.2lf, Char: %c\n", var1, var2, var3, var4); 
    printf("Unsigned int: %u, Short int: %hd, Long int: %ld, Const int: %d\n", var5, var6, var7, var8);

    // If statements
    if (var1 > 0 || var1 == 0) { // Check if var1 is positive or zero
        printf("var1 is positive or zero\n");
    } else if (var1 < 0 && var1 == -5) { // Check if var1 is negative and equal to -5
        printf("var1 is negative and not -5\n");
    } else {
        printf("var1 is negative or undefined\n");
    }

    // Switch statement
    switch (var1) {
        case 1:
            printf("var1 is 1\n");
            break;
        case 2:
            printf("var1 is 2\n");
            break;
        case 3:
            printf("var1 is 3\n");
            break;
        default:
            printf("var1 is not 1, 2, or 3\n");
    }


    // Loops
    for (int i = 0; i < 5; i++) { // For loop
        printf("For loop iteration: %d\n", i);
    }

    int counter = 5; // Initialize counter variable
    while (counter > 0) { // While loop
        printf("While loop iteration: %d\n", counter);
        counter--; // Decrement counter

        if (counter >= 5) {
            break; // Break out of the loop
        } else if (counter == 3) {
            continue; // Skip the rest of the loop iteration
        }
    }

    int counter2 = 10; // Initialize counter2
    do { // Do-while loop (executes at least once)
        printf("Do-while loop iteration: %d\n", counter2);
        counter2--;
    } while (counter2 < 0);

    // Signs and operators
    // % Modulus (remainder)
    // ++ Increment
    // -- Decrement
    // == Equal to
    // >= Greater than or equal to
    // <= Less than or equal to
    // && Logical AND
    // || Logical OR
    // ! Logical NOT
    // (THERE IS NO POWER SIGN LIKE ** IN PYTHON)
    
    // Note, when dividing, use decimals to get decimal numbers. 
    // (1 / 2 = 0) WHERE (1.0 / 2.0 = 0.5)
    
    // Functions
    double x = testFunction(); // Call testFunction (no parameters) and store the result in x

    return 0; // Return 0 to indicate successful
}

double testFunction(void) { // void means no parameters needed
    return 3.14; // Function to return the value 3.14
}