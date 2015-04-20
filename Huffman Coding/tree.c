#include "functions.h"

//Constructing the root node of a tree
treeNode *constructTree(int key, treeNode *left, treeNode *right) {
   treeNode *node = (treeNode *)malloc(sizeof(treeNode));
   if (node = NULL) {
      fprintf(stderr, "ERROR 01: Memory allocation unsuccessful");
      return NULL;
   }
   
   //Constructing root node
   node->value = key;
   node->left = left;
   node->right = right;
   
   return node;
}

//Deconstructing a tree
void destructTree(treeNode *node) {
   if (node == NULL)
      return;
   
   //postorder free
   destructTree(node->left);
   destructTree(node->right);
   free(node);
}

//Checking if node is a leaf
int isLeaf(treeNode *node) {
   if (node != NULL) { //node exists
      //If the left and right nodes don't exists, return TRUE
      if (node->left == NULL && node->right == NULL)
         return TRUE;
      //Otherwise return FALSE
      else
         return FALSE;
   }
   
   //Input is NULL
   return EXCEPTION;
}


