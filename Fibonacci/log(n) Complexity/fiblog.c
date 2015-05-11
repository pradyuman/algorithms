#include <stdio.h>
#include <stdlib.h>
#include "functions.h" //Function declarations

int main(int argc, char *argv[])
{
   //Error checking
   if (argc != 2) {
      return EXIT_FAILURE;
   }
   
   int n = atoi(argv[1]);
   if (n < 0) {
      return EXIT_FAILURE;
   }
   
   //Call Fibonacci function
   unsigned long ans = Fibonacci(n);
   
   printf("The Fibonacci number is: %lu\n", ans);
   
   return EXIT_SUCCESS;
}
