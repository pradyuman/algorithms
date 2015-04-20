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

//function declarations
void push(listNode *head, listNode *node);
listNode *pop(listNode *head);