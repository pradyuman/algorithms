#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

//recursive implementation of the mind guessing game
int guess_rec(int lb, int ub)
{

  //Terminating condition
  if (lb == ub) {
      return lb;
  }

  char answer;
  int mid;        

  mid = (ub + lb) / 2;  //Split mid into two parts

  printf("Is the number greater than %d? (Y/N)\n", mid);
  
  //Get the answer from user
  answer = getchar();
  while (getchar() != '\n');

  if (answer == 'N') {
    return guess_rec(lb, mid);

  } else { 
     return guess_rec(mid + 1, ub);
  }

  return 0;
}

//Iterative implementation of the mind guessing game
int guess_itr(int lb, int ub)
{

  char answer;
  int mid;
  
   while (ub != lb) {  

     mid = (ub + lb) / 2;

     printf("Is the number greater than %d? (Y/N)\n", mid);

     answer = getchar();
     while (getchar() != '\n');

     if (answer == 'N') { 
        ub = mid;
     } else { 
        lb = mid + 1;
     }

   }
  return lb;
}
