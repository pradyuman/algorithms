#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

/* check whether a value is sufficiently small */
/* to be considered 0 */

int Is_zero(double value)
{
   if (value < 0) {
      value = -value;
   }
   if (value < TOL) {
      return 1;
   } else {
      return 0;
   }
}

/* read a matrix from a file, return the matrix */
/* store the size of the matrix in *size        */

double **Read_matrix_from_file(char *filename, int *size)
{
   //Opening file
   FILE *input = fopen(filename, "r");
   //If file did not open, return and do nothing else
   if(input == NULL)
      return NULL;
   
   //Read in size
   rewind(input);
   fread(size, sizeof(int), 1, input);
   
   //allocate memory for data in the file
   double** data = allocateSpace(*size);
   if (data == NULL){
      return NULL;
   }
   
   int i; //x-coordinate
   int j; //y-coordinate
   
   //Read data from file
   for(i = 0; i < *size; i++){
      for(j = 0; j < *size; j++){
         fread(&data[i][j], sizeof(double), 1, input);
      }
   }
   
   fclose(input);
   
   return data;
}

/* write a matrix of a given size to a file, return 1 if the write is */
/* successful, otherwise, 0 */

int Write_matrix_to_file(char *filename, double **matrix, int size)
{
   //Opening file
   FILE *output = fopen(filename, "w");
   //If file did not open, return and do nothing else
   if(output == NULL)
      return 0;
   
   int i; //x-coordinate
   int j; //y-coordinate
   
   //Read data from matrix and write to the file
   for(i = 0; i < size; i++){
      for(j = 0; j < size; j++){
         fwrite(&matrix[i][j], sizeof(double), 1, output);
      }
   }
   
   fclose(output);
   
   return 1;
}

/* invert a matrix of a given size */
/* if inversion is successful, return the inverse */
/* otherwise, return NULL */

double **Invert_matrix(double **data, int size)
{
   //Initializing augmented part of matrix to identity
   double** inverse = createIdentity(size);
   //If unsuccessful, return NULL
   if(inverse == NULL)
      return NULL;
   
   int i, j; //counter
   int leftState, rightState; //positions in left/right part of augmented matrix
   for(i = 0; i < size; i++){
      //get pivot row
      int pivot = findPivot(data, i, size);
      
      //Swapping rows based on pivot
      for(j = 0; j < size; j++) {
         //swap rows on left side
         leftState = data[i][j];
         data[i][j] = data[pivot][j];
         data[pivot][j] = leftState;
         
         //swap rows on right side
         rightState = inverse[i][j];
         inverse[i][j] = inverse[pivot][j];
         inverse[pivot][j] = rightState;
      }
      
      //Divide rows by the current value which should be the highest based on the row operations
      int currState = data[i][i];
      for(j = 0; j < size ; j++) {
         data[i][j] /= currState;
         inverse[i][j] /= currState;
      }
      
      int k;
      j = 0;
      while(j < size){
         if (j == i) {
            j++;
         }
         else {
            float state = data[j][i];
            for(k = 0; k < size; k++){
               data[j][k] -= state * data[i][k];
               inverse[j][k] -= state * inverse[i][k];
            }
            j++;
         }
      }
      
   }
   deallocateSpace(data, size);
   return inverse;
}

//Create identity matrix
double **createIdentity(int size){
	int i, j; //Counters
	double **identity = allocateSpace(size);
   if (identity == NULL)
      return NULL;
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			identity[i][j] = i == j ? 1 : 0;
		}
	}
   
   return identity;
}

//Find pivot
int findPivot(double** data, int curr, int size){
   //current value of matrix
   float state = data[curr][curr];
   //Will check the value right underneath current value
   float lower = 0;
   //return value
   int pivot;
   int i; //counter
   //current + 1 to make sure we don't go beyond the bounds (also want to compare value underneath to current)
   for(i = curr + 1; i < size; i++){
      //absolute value
      lower = data[i][curr] > 0 ? data[i][curr] : -1 * data[i][curr];
      state = state > 0 ?: -1 * data[curr][curr];
      
      if(lower > state){
         pivot = i;
         state = data[i][curr];
      }
   }
   printf("%d\n", pivot);
   return pivot;
}

/* multiply two matrices of the same size */
/* if the multiplication is successful, return the results */

double **Matrix_matrix_multiply(double **matrixa, double **matrixb, int size)
{
   return NULL;
}

/* return the sum of the absolute differences between the */
/* entries of a matrix of a given size and the corresponding */
/* entries of an identity matrix of the same size */

double Deviation_from_identity(double **matrix, int size)
{
   return 0.0;
}

//Allocate space for data
double ** allocateSpace(int size)
{
   //Initializing maze dynamically
   double** data = (double **)malloc(size * sizeof(double *));
   
   //Checking to see if memory allocation was successful
   if (data == 0) {
      printf("ERROR: Memory allocation unsuccessful.\n");
      deallocateSpace(data,0);
      return NULL;
   }
   
   int row; //Incrememnting through the rows
   
   for (row = 0; row < size; row++) {
      data[row] = (double *)malloc(size * sizeof(double));
      if (data[row] == 0) {
         printf("ERROR: Memory allocation unsuccessful.\n");
         deallocateSpace(data, size);
         return NULL;
      }
   }
   
   return data;
}

//Deallocate space
void deallocateSpace(double **data, int size)
{
   int row; //counter
   for (row = 0; row < size; row++) {
      free(data[row]);
   }
   
   free(data);
   return;
}
