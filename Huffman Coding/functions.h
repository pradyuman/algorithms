#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define EXCEPTION -1
#define ASCII_COUNT 256

//structure for a tree node
typedef struct _treeNode {
   int value;
   struct _treeNode *left;
   struct _treeNode *right;
} treeNode;

//structure for a list node
typedef struct _listNode {
   treeNode *tree;
   struct _listNode *next;
} listNode;

//list function declarations
listNode *constructNode(treeNode *tree);
void destructNode(listNode *node);
void push(listNode *head, listNode *node);
listNode *pop(listNode *head);
int stackSize(listNode *head);
void stackFlush(listNode *head);

//tree function declarations
treeNode *constructTree(int key, treeNode *left, treeNode *right);
void destructTree(treeNode *node);
int isLeaf(treeNode *node);

//main function declarations
treeNode *constructHuffmanTree(FILE *input);
int decodeHuffmanTree(treeNode* huffman, FILE* input, FILE* output)
void postOrderPrint(treeNode *node, FILE *output, char *code);