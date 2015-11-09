#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <memory.h>
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

  //Sort table
  sort_table(table, size);

  //Create Huffman Tree
  frequency huffman[1028] = {{0}};
  int iroot = construct_huffman_tree(table, huffman, size);
  frequency* root = &huffman[iroot];
  //printf("%d", root);
  //Create output file
  char * ofilename = malloc(strlen(argv[1]) + 6); //sizeof(char) = 1 - +6 for .huff and \0
  strcpy(ofilename, argv[1]); strcat(ofilename, ".huff");
  FILE *output = fopen(ofilename, "wb");
  free(ofilename);

  //Build table of codes
  int codes[256]; //second half of codes stores depth
  build_code_table(root, codes, 0);
 /* int i = 0;
  for(i = 0; i<size; i++){
    printf("%c: %d", table[i].c, codes[table[i].c]);
  }*/
  printf("\n");
  compress(input, output, codes);
  /*int i = 0;
  for(i=0; i<size; i++)
    printf("%d: %lu\n", table[i].c, table[i].f);
  for(i=0; i <= root; i++){
    printf("%d: %lu | left: %lu right: %lu ", i, huffman[i].f, huffman[i].left->f, huffman[i].right->f);
    if(huffman[i].left->c != INT_MAX) printf("left_char: %c ", huffman[i].left->c);
    if(huffman[i].right->c != INT_MAX) printf("right_schar: %c ", huffman[i].right->c);
    printf("\n");
  }*/
  free(table);
  fclose(input);
  fclose(output);
  return 0;
}

void build_freq_table(FILE* input, frequency* freq) {
  int curr;
  while(fread(&curr, sizeof(char), sizeof(char), input)) {
    freq[curr].c = curr;
    freq[curr].f++;
  }
}

frequency* make_condensed_table(frequency* freq, int* size) {
  int i;
  for(i=0; i<256; i++) {
    if(freq[i].f) *size = *size + 1;
  }

  frequency *table = calloc(*size, sizeof(frequency));
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

void sort_table(frequency *table, int size) {
  int i, j;
  frequency temp;
  for(i=1; i<size; i++) {
    temp.c = table[i].c;
    temp.f = table[i].f;
    j = i;
    while(j > 0 && table[j-1].f > temp.f) {
      table[j].c = table[j-1].c;
      table[j].f = table[j-1].f;
      j--;
    }
    table[j].c = temp.c;
    table[j].f = temp.f;
  }
}

int construct_huffman_tree(frequency* table, frequency* tree, int size) {
  //frequency *queue = calloc(size, sizeof(frequency));
  frequency *temp;
  int i=0;
  int j=0;
  int p=0; //point at start of stack

  //Initial setup
  temp = &tree[i++];
  temp->left = &table[j++];
  temp->right = &table[j++];
  temp->f = temp->left->f + temp->right->f;
  temp->c = INT_MAX;

  while(j < size) {
    temp = &tree[i++];
    if(tree[p].f <= table[j+1].f){
      temp->left = &tree[p++];
      temp->right = &table[j++];
    } else {
      temp->left = &table[j++];
      temp->right = &table[j++];
    }
    temp->f = temp->left->f + temp->right->f;
    temp->c = INT_MAX;
  }

  while(p < i-1) {
    temp = &tree[i++];
    temp->left = &tree[p++];
    temp->right = &tree[p++];
    temp->f = temp->left->f + temp->right->f;
    temp->c = INT_MAX;
  }

  return p;
}

void build_code_table(frequency* node, int codes[256], int code) {
  //At leaf, store the code and depth
  if(node->left == NULL || node->right == NULL) {
    codes[node->c] = code;
  } else {
    build_code_table(node->left, codes, code*10 + 1);
    build_code_table(node->right, codes, code*10 + 2);
  }
}

void compress(FILE* input, FILE* output, int codes[256]) {
  char bit, c;
  char temp = 0; //temp character to be put into file
  int code, length;
  int left = 8; //# of bits left
  int orig = 0, compressed = 0;
  int i;
  fseek(input, 0, SEEK_SET);
  while((c=fgetc(input)) != EOF) {
    orig++;
    i = codes[(int)c];
    length = 0;
    while(i!=0){
      i /= 10;
      length++;
    }
    code = codes[(int)c];
    while(length--) {
      compressed++;
      bit = code % 10 - 1; code /= 10; //do the arithmetic to get proper bit
      temp |= bit;
      left--;
      if(!left){
        fputc(temp, output);
        temp = 0; //reset temp
        left = 8; //reset bits left
      }
      temp <<= 1;
    }
  }

  if(left != 8) { //fill in last bit with padding
    temp <<= left - 1;
    fputc(temp, output);
  }
  printf("orig = %d, compressed = %d, saved %f", orig*8, compressed, ((float)compressed/(orig*8)));
}
