#include "functions.h"

//Creating a Huffman Coding Tree from an input file
treeNode *buildHuffmanTree(FILE *input) {
   //Creating stack
   listNode stack;
   stack.next = NULL;
   stack.tree = (treeNode *)0;
   
   int token;
   
   while ((token = fgetc(input)) != EOF) {
      if (token == '0') {
         if (stackSize(&stack) <= 1)
            break;
         
         listNode *rightNode = pop(&stack);
         listNode *leftNode = pop(&stack);
         
         treeNode *rightTree = rightNode->tree;
         treeNode *leftTree = leftNode->tree;
         
         treeNode *tree = constructTree(ASCII_COUNT, leftNode, rightNode);
         
         if (tree == NULL) {
            destructNode(leftNode);
            destructNode(rightNode);
            token = EXCEPTION;
            break;
         }
         
         rightNode->tree = tree;
         rightNode->next = NULL;
         push(&stack, rightNode);
         free(leftNode);
      }
      else if (token == '1') {
         token = fgetc(input);
         if (token == EOF)
            break;
         
         treeNode *tree = constructTree(token, NULL, NULL);
         if (tree == NULL) {
            token = EXCEPTION;
            break;
         }
         
         listNode *stackNode = nodeConstruct(tree);
         if (stackNode == NULL) {
            token = EXCEPTION;
            break;
         }
      }
   }
   
   if (token == '0' && stackSize(&stack) == 1) {
      treeNode *node = pop(&stack);
      treeNode *huffman = node->tree;
      free(node);
      return huffman;
   }
   
   stackFlush(&stack);
   return NULL;
}

//Post order print of the Huffman Coding tree
void postOrderPrint(treeNode *node, FILE *output) {
   if (node == NULL)
      return;
   
   if (isLeaf(node)) {
      fprintf(output, "1%c", node->value);
      return;
   }
   postOrderPrint(node->left, output);
   postOrderPrint(node->right, output);
   fprintf(output, "0");
}