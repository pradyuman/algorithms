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

      //Reading file
      BMP_Image *image = Read_BMP_Image(input);
      if (image == NULL) {
         fclose(input);
         return EXIT_FAILURE;
      }
      
      BMP_Image *outputImage = Top_Half_BMP_Image(image);
      if (outputImage == NULL) {
         fclose(input);
         Free_BMP_Image(image);
         return EXIT_FAILURE;
      }
      
      //Opening output file
      FILE* output = fopen(argv[3],"wb");
      if (output == NULL) {
         fclose(input);
         return EXIT_FAILURE;
      }
      
      //Writing to output file
      int valid = Write_BMP_Image(output, outputImage);
      if (valid == FALSE) {
         fclose(input);
         fclose(output);
         Free_BMP_Image(image);
         Free_BMP_Image(outputImage);
      }
      
      
      fclose(input);
      fclose(output);
      Free_BMP_Image(image);
      Free_BMP_Image(outputImage);
   }
   else if (argc >= 4 && strcmp(argv[1],"-l") == 0){
      //Opening input file
      FILE* input = fopen(argv[2],"rb");
      if (input == NULL) {
         return EXIT_FAILURE;
      }
      
      //Reading file
      BMP_Image *image = Read_BMP_Image(input);
      if (image == NULL) {
         fclose(input);
         return EXIT_FAILURE;
      }
      
      BMP_Image *outputImage = Left_Half_BMP_Image(image);
      if (outputImage == NULL) {
         fclose(input);
         Free_BMP_Image(image);
         return EXIT_FAILURE;
      }
      
      //Opening output file
      FILE* output = fopen(argv[3],"wb");
      if (output == NULL) {
         fclose(input);
         return EXIT_FAILURE;
      }
      
      //Writing to output file
      int valid = Write_BMP_Image(output, outputImage);
      if (valid == FALSE) {
         fclose(input);
         fclose(output);
         Free_BMP_Image(image);
         Free_BMP_Image(outputImage);
      }
      
      
      fclose(input);
      fclose(output);
      Free_BMP_Image(image);
      Free_BMP_Image(outputImage);
   }
   else if (argc >= 4 && strcmp(argv[1],"-c") == 0){
      //Opening input file
      FILE* input = fopen(argv[2],"rb");
      if (input == NULL)
         return EXIT_FAILURE;
      
      //Reading file
      BMP_Image *image = Read_BMP_Image(input);
      if (image == NULL) {
         fclose(input);
         return EXIT_FAILURE;
      }
      
      //Converting image
      BMP_Image *outputImage = (BMP_Image *)malloc(sizeof(BMP_Image));
      if (outputImage == NULL) {
         fclose(input);
         Free_BMP_Image(image);
         return EXIT_FAILURE;
      }
      
      if (image->header.bits == 24) {
         outputImage = Convert_24_to_16_BMP_Image(image);
      }
      else if (image->header.bits == 16){
         outputImage = Convert_16_to_24_BMP_Image(image);
      }
      //invalid input (wrong number of bits)
      else {
         fclose(input);
         Free_BMP_Image(outputImage);
         Free_BMP_Image(image);
         return EXIT_FAILURE;
      }
      
      //Opening output file
      FILE* output = fopen(argv[3],"wb");
      if (output == NULL) {
         fclose(input);
         return EXIT_FAILURE;
      }
      
      //Writing to output file
      int valid = Write_BMP_Image(output, outputImage);
      
      if (valid == FALSE) {
         fclose(input);
         fclose(output);
         Free_BMP_Image(image);
         Free_BMP_Image(outputImage);
      }
      
      fclose(input);
      fclose(output);
      Free_BMP_Image(image);
      Free_BMP_Image(outputImage);
   }
   else {
      return(EXIT_FAILURE);
   }

   return EXIT_SUCCESS;
}
