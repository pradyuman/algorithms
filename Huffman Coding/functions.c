#include "functions.h"

//Creating a Huffman Coding Tree from an input file
treeNode *constructHuffmanTree(FILE *input) {
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
         
         treeNode *tree = constructTree(ASCII_COUNT, leftTree, rightTree);
         
         if (tree == NULL) {
            fprintf(stderr, "functions.c:26 | ERROR 06: Tree could not be constructed");
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
            fprintf(stderr, "functions.c:45 | ERROR 06: Tree could not be constructed");
            token = EXCEPTION;
            break;
         }
         
         listNode *stackNode = constructNode(tree);
         if (stackNode == NULL) {
            fprintf(stderr, "functions.c:26 | ERROR 07: List node could not be constructed");
            destructTree(tree);
            token = EXCEPTION;
            break;
         }
         push(&stack, stackNode);
      }
      else
         break;
   }
   
   if (token == '0' && stackSize(&stack) == 1) {
      listNode *node = pop(&stack);
      treeNode *huffman = node->tree;
      free(node);
      return huffman;
   }
   
   stackFlush(&stack);
   return NULL;
}

int decodeHuffmanTree(treeNode* huffman, FILE* input, FILE* output) {
   int count; //character count
   if(fread(&count, sizeof(int), 1, input) != 1)
      return 0;
   
   while (count > 0) {
      int decoded = decodeChar(huffman, input);
      
      if (decoded != -1) {
         fputc(decoded, output);
         count--;
      } else
         break;
   }
   
   //if count is zero, return 1 (otherwise return 0)
   return count != 0 ? 0 : 1;
}

//Post order print of the Huffman Coding tree
void postOrderPrint(treeNode *node, FILE *output, char *code) {
   if (node == NULL)
      return;
   
   if (isLeaf(node)) {
      fprintf(output, "%c:%s\n", node->value, code);
      return;
   }
   //fprintf(output, "%c:%s\n", node->value, code);
   postOrderPrint(node->left, output, strcat(code,"0"));
   code[strlen(code) - 1] = '\0';
   postOrderPrint(node->right, output, strcat(code,"1"));
   code[strlen(code) - 1] = '\0';
}