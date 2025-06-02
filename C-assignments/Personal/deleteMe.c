#include <stdlib.h>

int main(void) {

   // Q1
   int counter = 0;

   int count = 1;
    counter += sizeof(count);
    printf("+%d\n", sizeof(count));
   int number;
   counter += sizeof(number);
   printf("+%d\n", sizeof(number));
   int * ptr = &count;
   counter += sizeof(ptr);
   printf("+%d\n", sizeof(ptr));
   int * ptr2 = &number;
   counter += sizeof(ptr2);
   printf("+%d\n", sizeof(ptr2));


   // Q2
   ptr = ptr2;
   *ptr2 = 3;
   


   // Q3
   ptr = malloc (number * sizeof(char));
    counter += number * sizeof(char);
   printf("+%d", number * sizeof(char));

   printf("Final would be: %d\nOtherwise\n", counter);
   // Q4
   ptr2 = malloc (count * sizeof(char));
   ptr = ptr2;
   counter += count * sizeof(char);
   printf("+%d\n", count * sizeof(char));

   return 0;
   
}