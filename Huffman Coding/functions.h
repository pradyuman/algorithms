#define TRUE 1
#define FALSE 0
#define EXCEPTION -1

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
void push(listNode *head, listNode *node);
listNode *pop(listNode *head);
int stackSize(listNode *head);
listNode *constructNode(treeNode *tree);
void nodeDeconstruct(listNode *node);

//tree function declarations
treeNode *constructTree(int key, treeNode *left, treeNode *right);
void destructTree(treeNode *node);
int isLeaf(treeNode *node);
