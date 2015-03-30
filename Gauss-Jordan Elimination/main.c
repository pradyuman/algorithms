#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

//Main
int main(int argc, char** argv){
   int size, i, j; //Variable that will store the size
   double** data; //Matrix that will store data from file
   double** invert; //Matrix that will store inverted matrix
   
   if (argc >= 4 && strcmp(argv[1],"-i") == 0){
      //Reading from file
      data = Read_matrix_from_file(argv[2], &size);
      //Inverting that data
      invert = Invert_matrix(data, size);
      
      for (i = 0; i <size; i++) {
         for (j = 0; j < size; j++) {
            printf("%3.6f ", invert[i][j]);
         }
         printf("\n");
      }
      
      //If the inversion was not successful, print error
      if (invert == NULL) {
         fprintf(stderr, "ERROR: The inversion failed.\n");
         return(EXIT_FAILURE);
      }
      
      //Testing
      int sof = Write_matrix_to_file(argv[3], invert, size);
      
      //If the wrte-to-file failed, print error
      if(sof == 0){
         fprintf(stderr, "Writing to the file failed\n");
         return(EXIT_FAILURE);
      }
   
      //deallocate the inverted matrix
      deallocateSpace(invert, size);
   }
   else if (argc >= 5 && strcmp(argv[1],"-m") == 0){
      printf("m\n");
   }
   else if (argc >= 3 && strcmp(argv[1], "-d") == 0) {
      printf("d\n");
   }
   else{
      fprintf(stderr, "ERROR: Enter in '-i', '-m', or '-d' as the third argument.\n");
      return(EXIT_FAILURE);
   }

return 0;
}
