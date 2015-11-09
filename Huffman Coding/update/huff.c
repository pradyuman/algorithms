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
  construct_huffman_tree(table, huffman, size);

  int i = 0;
  for(i=0; i<size; i++)
    printf("%d: %lu\n", table[i].c, table[i].f);
  for(i=0; huffman[i].f != 0; i++)
    printf("%d: %lu | left: %lu right: %lu\n", i, huffman[i].f, huffman[i].left->f, huffman[i].right->f);

  free(table);
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

void construct_huffman_tree(frequency* table, frequency* tree, int size) {
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
}
