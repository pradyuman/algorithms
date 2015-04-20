#include <stdio.h>
#include "functions.h"

int main(int argc, char **argv) {
   //Checking to make sure that the correct number of arguments is given (at least 3)
   
   if (argc < 3) {
      fprintf(stderr, "main.c:8 | ERROR 01: Incorrect number of input arguments");
      return EXIT_FAILURE;
   }
   
   //Opening input file
   FILE *input = fopen(argv[1], "r");
   if (input == NULL) {
      fprintf(stderr, "main.c:15 | ERROR 02: Input file could not be opened");
      return EXIT_FAILURE;
   }
   
   //Creating a huffman tree
   treeNode * huffman = constructHuffmanTree(input);
   //Input file is not needed after tree is contructed
   fclose(input);
   
   if (huffman == NULL) {
      fprintf(stderr, "main.c:25 | ERROR 04: Huffman tree could not be created");
      return EXIT_FAILURE;
   }
   
   //Opening output file
   FILE *output = fopen(argv[2], "w");
   if (output == NULL) {
      fprintf(stderr, "main.c:31 | ERROR 05: Output file could not be opened or created");
      return EXIT_FAILURE;
   }
   
   //Save the huffman tree into a file
   postOrderPrint(huffman, output);
   
   //Output file is not needed after printing
   fclose(output);
   
   return EXIT_SUCCESS;
}