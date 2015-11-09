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
  frequency freq[256] = {{0}};
  build_freq_table(input, freq);

  //Condense into a list
  int size = 0;
  frequency *table = make_condensed_table(freq, &size);

  int i = 0;
  for(i=0; i<size; i++)
    printf("%d: %lu\n", table[i].c, table[i].f);

  return 0;
}

void build_freq_table(FILE* input, frequency* freq) {
  int curr;
  while(fread(&curr, sizeof(char), sizeof(char), input)) {
    freq[curr].c = (char)curr;
    freq[curr].f++;
  }
}

frequency* make_condensed_table(frequency* freq, int* size) {
  int i;
  for(i=0; i<256; i++) {
    if(freq[i].f) *size = *size + 1;
  }

  frequency *table = malloc(*size * sizeof(frequency));
  int j = 0;
  for(i=0; i<256; i++){
    if(freq[i].f) {
      table[j].c = freq[i].c;
      table[j].f = freq[i].f;
      j++;
    }
  }

  return table;
}
