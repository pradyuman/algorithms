#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

#ifndef NTEST_LOG

void logFibonacci(int n, unsigned long *fn1, unsigned long *fn2)
{

 //Terminating condition
    
  if (n==2){
    *fn2 = 1;
    *fn1 = 1;
    return;
  }
  if (n==0){
    *fn2 = 0;
    *fn1 = 0;
    return;
  } 

  //Dividing by 2
  int m = n / 2;
    
  if(m % 2 == 0){       
    logFibonacci(m, fn1, fn2);
    unsigned long int temp1 = 2*(*fn2)*(*fn1)+(*fn1)*(*fn1);
    unsigned long int temp2 = (*fn2)*(*fn2)+(*fn1)*(*fn1);
    *fn1 = temp1;
    *fn2 = temp2;
  }
   else {
     logFibonacci(m-1, fn1, fn2);
     unsigned long int temp1 = 2*(*fn2)*(*fn1)+(*fn1)*(*fn1);
     unsigned long int temp2 = (*fn2)*(*fn2)+(*fn1)*(*fn1);
     *fn2 = temp1 + temp2;
     *fn1 = *fn2 + temp1;
   }

}

#endif

#ifndef NTEST_FIB

unsigned long Fibonacci(int n)
{
  //To store results from logFibonacci

  unsigned long fn1 = 0; 
  unsigned long fn2 = 0;
  
  /* if even n, call logFibonacci with n and return fn1
   * if odd n, call with n-1 or n+1, combine fn1 and fn2 as F(n) */
  if(n % 2 == 0){
    logFibonacci(n, &fn1, &fn2);
    return fn1;
  }
  else {
    logFibonacci(n-1, &fn1, &fn2);
    return fn1 + fn2;
  }
  return 0;
}

#endif
