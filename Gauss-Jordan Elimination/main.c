#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

//Main
int main(int argc, char** argv){
   int size;
   double** data; //Matrix that will store data from file
   double** invert; //Matrix that will store inverted matrix
   
   if (argc >= 4 && strcmp(argv[1],"-i") == 0){
      //Reading from file
      data = Read_matrix_from_file(argv[2], &size);
      //Inverting that data
      invert = Invert_matrix(data, size);
      
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
      double** aData;
      double** bData;
      double** output;
      int sizeb;
      
      aData = Read_matrix_from_file(argv[2], &size);
      bData = Read_matrix_from_file(argv[3], &sizeb);
      
      if(size != sizeb){
         return(EXIT_FAILURE);
      }
      
      output = Matrix_matrix_multiply(aData, bData, size);
      
      int sof = Write_matrix_to_file(argv[4], output, size);
      
      //If the wrte-to-file failed, print error
      if(sof == 0){
         fprintf(stderr, "Writing to the file failed\n");
         return(EXIT_FAILURE);
      }
      
      //Deallocating space
      deallocateSpace(aData, size);
      deallocateSpace(bData, sizeb);
      deallocateSpace(output, size);
   }
   else if (argc >= 3 && strcmp(argv[1], "-d") == 0) {
      data = Read_matrix_from_file(argv[2], &size);
      
      printf("%e\n", Deviation_from_identity(data, size));
   }
   else{
      fprintf(stderr, "ERROR: Enter in '-i', '-m', or '-d' as the third argument.\n");
      return(EXIT_FAILURE);
   }

return EXIT_SUCCESS;
}
