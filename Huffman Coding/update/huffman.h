//Frequency structure
typedef struct _frequency {
  char c;
  unsigned long f;
} frequency;

//Makes an array of frequencies based on input file
void build_freq_table(FILE* input, frequency* freq);
//Shortens the frequency table to only the characters that are actually used
frequency* make_condensed_table(frequency* freq, int* size);
