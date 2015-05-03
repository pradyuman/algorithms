#include "functions.h"

int main(int argc, char **argv) {
   //Checking to make sure that the correct number of arguments is given (at least 3)
   if (argc < 4) {
      fprintf(stderr, "main.c:5 | ERROR 01: Incorrect number of input arguments");
      return EXIT_FAILURE;
   }
   
   if (strcmp(argv[1],"-pc") != 0 && strcmp(argv[1],"-dc") != 0 && strcmp(argv[1],"-pb") != 0 && strcmp(argv[1],"-db") != 0) {
      fprintf(stderr, "main.c:10 | ERROR 08: Input flag is not valid");
      return EXIT_FAILURE;
   }
   
   //Opening input file
   FILE *input = fopen(argv[2], "r");
   if (input == NULL) {
      fprintf(stderr, "main.c:17 | ERROR 02: Input file could not be opened");
      return EXIT_FAILURE;
   }
   
   //Creating a huffman tree
   int version;
   if(strcmp(argv[1],"-pc") == 0 || strcmp(argv[1], "-dc") == 0)
      version = CHAR;
   else
      version = BIT;
      
   treeNode *huffman = constructHuffmanTree(input, version);
   if (huffman == NULL) {
      fprintf(stderr, "main.c:29 | ERROR 04: Huffman tree could not be created");
      fclose(input);
      return EXIT_FAILURE;
   }
   
   //Opening output file
   FILE *output = fopen(argv[3], "w");
   if (output == NULL) {
      fprintf(stderr, "main.c:37 | ERROR 05: Output file could not be opened or created");
      fclose(input);      
      return EXIT_FAILURE;
   }
   
   if (strcmp(argv[1],"-pc") == 0 || strcmp(argv[1], "-pb") == 0) {
      //Input file is not needed after tree is contructed
      fclose(input);
      //Save the huffman tree into a file
      char *code = (char *)calloc(ASCII_COUNT, sizeof(char));
      if (code == NULL) {
         //Deallocate all memory used
         destructTree(huffman);
         //Output file is not needed
         fclose(output);
         fprintf(stderr, "main.c:48 | ERROR 03: Memory allocation unsuccessful");
         return EXIT_FAILURE;
      }
      postOrderPrint(huffman, output, code);
      
      //Deallocate all memory used
      destructTree(huffman);
      free(code);
      //Output file is not needed after printing
      fclose(output);
   } else {
      //Decoding input file
      int flag = decodeHuffmanTree(huffman, input, output);
      //Input file is not needed after decoding
      fclose(input);
      //Output file is not needed after decoding
      fclose(output);
      //Deallocate all memory used
      destructTree(huffman);
      
      if (flag == 0) {
         fprintf(stderr, "main.c:66 | ERROR 09: Input file could not be decoded");
         return EXIT_FAILURE;
      }
   }
   
   return EXIT_SUCCESS;
}
