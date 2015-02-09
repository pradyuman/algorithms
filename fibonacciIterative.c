//This program calculates the nth fibonacci number recursively.
#include <stdio.h>
#include <stdlib.h>

//Function declarations
unsigned long fib(unsigned long num);

int main(int argc, char * argv[]){
    long ans;

    ans = fib(atol(argv[1]));

    if (atol(argv[1]) == 1){
        printf("The %ldst Fibonacci number is %ld.\n", atol(argv[1]), ans);
    }
    else if (atol(argv[1]) == 2){
        printf("The %ldnd Fibonacci number is %ld.\n", atol(argv[1]), ans);
    }
    else if (atol(argv[1]) == 3){
        printf("The %ldrd Fibonacci number is %ld.\n", atol(argv[1]), ans);
    }
    else {
        printf("The %ldth Fibonacci number is %ld.\n", atol(argv[1]), ans);
    }

    return 0;
}

unsigned long fib(unsigned long num){
    if (num == 1){
        return 1;
    }
    if (num == 0){
        return 0;
    }

    unsigned int prev, fib, temp;
    int i;
    prev = 0;
    fib = 1;

    for(i = 2; i <= num; i++){
        temp = prev + fib;
        prev = fib;
        fib = temp;
    }
    return fib;
}
