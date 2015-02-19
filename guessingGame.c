//This program will take an input of two numbers (lower and upper bound) and
//will try to guess the number that you are thinking.
#include <stdio.h>
#include <stdlib.h>
//Function declaration
unsigned guess(unsigned lower_bound, unsigned upper_bound, unsigned size);

//Main
int main(int argc, char * argv[]){
    int ans;

    ans = guess(atoi(argv[1]) - 1,atoi(argv[2]), atoi(argv[2]) + 1 - atoi(argv[1]));

    printf("Your number is %d! Thanks for playing!\n", ans);

    return 0;
}

//Function definition
unsigned guess(unsigned lower_bound, unsigned upper_bound, unsigned size){
    char response;

    if (size == 1) {
        return lower_bound + 1;
    }

    //Getting input
    printf("Is the number below %d inclusive? (y/n): ", lower_bound + size / 2);
    scanf("%c", &response);
    getchar();

    if (response == 'y' || response == 'Y'){
        return guess(lower_bound, lower_bound + size / 2, size / 2);
    }
    else {
        return guess(lower_bound + size / 2, upper_bound, size / 2);
    }
}
