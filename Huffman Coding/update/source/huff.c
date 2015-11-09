#define ERROR -1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

int main(int argc, char** argv) {
  //Make sure filename was given
  if(argc < 2) {
    printf("Make sure to enter a filename.");
    return ERROR;
  }

  FILE *input = fopen(argv[1], "rb");
  if(input == NULL){
    printf("Error opening input file.");
    return ERROR;
  }

  //Build frequency table
  frequency freq[256] = {0};
  build_freq_table(input, freq);

  int i = 0;
  for(i=0; i<256; i++)
    printf("%d: %lu\n", i, freq[i]);

  return 0;
}

void build_freq_table(FILE* input, unsigned long* freq) {
  int curr;
  while(fread(&curr, sizeof(char), sizeof(char), input))
    freq[curr]++;
}
