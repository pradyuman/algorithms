#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

//Main
int main(int argc, char** argv){
   int size, i, j;
   double** data;
   double** invert;
   
   if (argc >= 4 && strcmp(argv[1],"-i") == 0){
      printf("i ");
      data = Read_matrix_from_file(argv[2], &size);
      printf("%d\n", size);
      for(i = 0; i < size; i++){
         for(j = 0; j < size; j++){
            printf("%f ", data[i][j]);
         }
         printf("\n");
      }
      int sof = Write_matrix_to_file(argv[3], data, size);
      printf("sof: %d\n", sof);
      
      invert = Invert_matrix(data, size);
      for(i = 0; i < size; i++){
         for(j = 0; j < size; j++){
            printf("%f ", invert[i][j]);
         }
         printf("\n");
      }
      deallocateSpace(invert, size);
   }
   else if (argc >= 5 && strcmp(argv[1],"-m") == 0){
      printf("m\n");
   }
   else if (argc >= 3 && strcmp(argv[1], "-d") == 0) {
      printf("d\n");
   }
   else
      return(EXIT_FAILURE);

return 0;
}
