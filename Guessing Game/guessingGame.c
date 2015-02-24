//This program will take an input of two numbers (lower and upper bound) and will try to guess the number that you are thinking.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
include "functions.h" //Function declarations

//Main
int main(int argc, char * argv[]){
    int ans;
	
	if(argc != 4 || (strcmp((argv[1]), "-r") != 0 && strcmp((argv[1]), "-i") != 0) || atoi(argv[2]) > atoi(argv[3]))
     return EXIT_FAILURE;
    else if(strcmp((argv[1]), "-r") == 0)
      ans = guess_rec(atoi(argv[2]),atoi(argv[3]));
    else
      ans = guess_itr(atoi(argv[2]), atoi(argv[3]));

    printf("Your number is %d! Thanks for playing!\n", ans);

    return 0;
}
