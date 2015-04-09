#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

//Main
int main(int argc, char** argv){
   
   if (argc >= 4 && strcmp(argv[1],"-t") == 0){
      //Opening input file
      FILE* input = fopen(argv[2],"rb");
      if (input == NULL) {
         return EXIT_FAILURE;
      }

      //Opening output file
      FILE* output = fopen(argv[3],"wb");
      
      if (output == NULL) {
         fclose(input);
         return EXIT_FAILURE;
      }

      //Reading file
      BMP_Image *image;
      
      image = Read_BMP_Image(input);
      
      BMP_Image *outputImage;
      
      outputImage = Top_Half_BMP_Image(image);
      
      //Writing to output file
      Write_BMP_Image(output, outputImage);

      fclose(input);
      fclose(output);

   }
   else if (argc >= 4 && strcmp(argv[1],"-l") == 0){
  
   }
   else {
      return(EXIT_FAILURE);
   }

   return EXIT_SUCCESS;
}
