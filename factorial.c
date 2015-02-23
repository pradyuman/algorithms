//This program calculates the factorial of a number.
#include <stdio.h>
#include <stdlib.h>

//Function declaration
unsigned factorial(unsigned num);

//Main
int main(int argc, char * argv[]){
    int ans, sum;

    ans = factorial(atoi(argv[1]));

    printf("The factorial of %d is %d.\n", atoi(argv[1]), ans);
}

//Function definition
unsigned factorial(unsigned num){
    //Base case
	if (num == 1){
        return 1;
    }
	//Calculating factorial
    return num * factorial(num - 1);
}
