//Frequency structure
typedef struct _frequency {
  char c;
  long f;
} frequency;

//Makes an array of frequencies based on input file
void build_freq_table(FILE* input, unsigned long* freq);
//Shortens the frequency table to only the characters that are actually used
//unsigned long* make_condensed_table(unsigned long* freq);
