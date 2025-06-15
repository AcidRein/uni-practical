#include <stdio.h> // Required for file handling
#include <stdlib.h>

int main(void) {
    // Open file with fopen(filename, mode), and fclose(fp)  
    // modes: r = read, w = write, a = append, r+ reading and righting from beginning, w+ reading and overwriting, a+ reading and appending

    FILE *ptr; // create a pointer to a file.
    ptr = fopen("testFile.txt", "a"); // Point towards a file in a mode.

    if (ptr == NULL) { // On error
        printf("Error opening file...\n");  
        return 1;
    }

    // Write to file
    fprintf(ptr, "Hello World!!\nVariable Number: %d\n", 10);

    // Close the file
    fclose(ptr);


    // Reading out a file
    FILE *newPtr = fopen("testFile.txt", "r");
    if (newPtr == NULL) {
        printf("Error openingn file...\n");
        return 1;
    }

    // Print everything
    char c; // Temporary character holder, to check if it's EOF (end of file)
    while ((c = fgetc(newPtr)) != EOF)
    {
        printf("%c", c);
    }

    fclose(newPtr);
    return 0;
}  