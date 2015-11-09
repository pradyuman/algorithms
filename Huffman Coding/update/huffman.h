#define ERROR -1
#define DUMMY -2
//Frequency structure
typedef struct _frequency {
  int c;
  unsigned long f;
  struct _frequency *left;
  struct _frequency *right;
} frequency;

//Makes an array of frequencies based on input file
void build_freq_table(FILE* input, frequency* freq);
//Shortens the frequency table to only the characters that are actually used
frequency* make_condensed_table(frequency* freq, int* size);
//Sorts the frequency table from lowest to highest frequency
void sort_table(frequency *table, int size);
//Build Huffman Tree
int construct_huffman_tree(frequency* table, frequency* tree, int size);
//Get huffman codes
void build_code_table(frequency* root, int codes[256], int code);
//Compress file
void compress(FILE* input, FILE* output, int codes[256]);
