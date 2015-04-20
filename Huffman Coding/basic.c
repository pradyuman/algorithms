#include "functions.h"

void push(listNode *head, listNode *node) {
   node->next = head->next;
   head->next = node;
   int size = (unsigned long)(head->tree) + 1;
   head->tree = (treeNode *)((unsigned long)size);
}

listNode *pop(listNode *head) {
   listNode *node = head->next;
   if (node != NULL) { //stack has at least 1 member
      head->next = node->next;
      node->next = NULL;
      int size = (unsigned long)(head->tree) - 1;
      head->tree = (treeNode *)((unsigned long)size);
   }
}