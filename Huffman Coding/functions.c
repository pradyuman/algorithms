#include "functions.h"

//Creating a Huffman Coding Tree from an input file
treeNode *constructHuffmanTree(FILE *input, int version) {
   //Creating stack
   listNode stack;
   stack.next = NULL;
   stack.tree = (treeNode *)0;
   
   int token;
   int pos = -1;
   int readChar = 0;
   
   while (TRUE) {
     if (version == BIT) {
        if (pos < 0) {
           readChar = fgetc(input);
           if (readChar == EOF) {
              token = EXCEPTION;
              break;
           }
           pos = 7;
        }
        
        int mask = 1 << pos--;
        token = (readChar & mask) == 0 ? '0' : '1';
     } else {
        token = fgetc(input);
     }
      
      if (token == '0') {
         if (stackSize(&stack) <= 1)
            break;
         
         listNode *rightNode = pop(&stack);
         listNode *leftNode = pop(&stack);
         
         treeNode *rightTree = rightNode->tree;
         treeNode *leftTree = leftNode->tree;
         
         treeNode *tree = constructTree(ASCII_COUNT, leftTree, rightTree);
         
         if (tree == NULL) {
            fprintf(stderr, "functions.c:41 | ERROR 06: Tree could not be constructed");
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
         if (version == BIT) {
            if (pos < 0) {
               token = fgetc(input);
               if (token == EOF)
                  break;
            } else {
               int mask = 0xFF >> (7 - pos);
               token = (readChar & mask) << (7 - pos);
               readChar = fgetc(input);
               if(readChar == EOF) {
                  token = EOF;
                  break;
               }
               
               token |= readChar >> (pos + 1); 
            }   
         } else {
            token = fgetc(input);
         }
         
         if (token == EOF)
            break;
         
         treeNode *tree = constructTree(token, NULL, NULL);
         if (tree == NULL) {
            fprintf(stderr, "functions.c:80 | ERROR 06: Tree could not be constructed");
            token = EXCEPTION;
            break;
         }
         
         listNode *stackNode = constructNode(tree);
         if (stackNode == NULL) {
            fprintf(stderr, "functions.c:87 | ERROR 07: List node could not be constructed");
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

//decoding an input file
int decodeHuffmanTree(treeNode* huffman, FILE* input, FILE* output) {
   int count; //character count
   if(fread(&count, sizeof(int), 1, input) != 1)
      return 0;
   
   while (count > 0) {
      int decoded = decodeChar(huffman, input);
      
      if (decoded != EXCEPTION) {
         fputc(decoded, output);
         count--;
      } else
         break;
   }
   
   //if count is zero, return 1 (otherwise return 0)
   return count != 0 ? 0 : 1;
}

//decoding a character from the huffman tree
int decodeChar(treeNode* tree, FILE* input) {
   if (tree == NULL)
      return -1;
   //return the node value if the node is a leaf
   if (isLeaf(tree))
      return tree->value;
   
   //Static int to keep the value in this scope through the recursion calls
   static int inputChar = 0;
   static int position = EXCEPTION;
   
   if (position < 0) {
      inputChar = fgetc(input);
      //if at EOF, then return
      if (inputChar == EOF)
         return EXCEPTION;
      
      position = 7;
   }
   
   //masking the byte so that we are reading only one bit at a time
   int mask = 1 << position--;
   int token = mask & inputChar;
   
   //if token is 0, return left node of tree, otherwise return right node
   return decodeChar(token == 0 ? tree->left : tree->right, input);
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