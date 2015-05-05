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
   if(input == NULL) {
      fprintf(stderr, "ERROR: File could not be opened for reading.\n");
      return NULL;
   }
   
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
   if(output == NULL){
      fprintf(stderr, "ERROR: File could not be opened for writing.\n");
      return 0;
   }
   
   int i; //x-coordinate
   int j; //y-coordinate
   
   fwrite(&size, sizeof(int), 1, output);
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
   if(inverse == NULL){
      fprintf(stderr, "ERROR: Memory allocation failed for the inverse matrix.\n");
      return NULL;
   }
   
   int i,j,k; //counters
   int pivot, y, z;
   double lower, current;
   double leftState,rightState,state,currState; //positions in left/right part of augmented matrix
   
   for(i=0;i<size;i++)
   {
      //get pivot row
      pivot = i;
      for(y=i+1;y<size;y++)
      {
         lower = data[y-1][i];
         current = data[y][i];
         lower = lower > 0 ? lower: -1 * lower;
         current = current > 0 ? current: -1 * current;
         if(current>lower)
         {
            pivot = y;
         }
      }
      
      //Checking to see if invertible
      if(Is_zero(data[pivot][i]))
      {
         deallocateSpace(inverse, size);
         deallocateSpace(data, size);
         return NULL;
      }
      
      //Swapping rows based on pivot
      for(z=0;z<size;z++)
      {
         //swap rows on left side
         leftState=data[i][z];
         data[i][z]=data[pivot][z];
         data[pivot][z]=leftState;
         
         //swap rows on right side
         rightState=inverse[i][z];
         inverse[i][z]=inverse[pivot][z];
         inverse[pivot][z]=rightState;
      }
      
      //Divide column element by the current value which should be the highest based on the row operations
      state=data[i][i];
      j = 0;
      while(j<size)
      {
         data[i][j] /= state;
         inverse[i][j] /= state;
         j++;
      }
      
      j = 0;
      while(j<size)
      {
         if(j!=i)
         {
            currState=data[j][i];
            for(k=0;k<size;k++)
            {
               data[j][k] -= currState*data[i][k];
               inverse[j][k] -= currState*inverse[i][k];
            }
         }
         j++;
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

/* multiply two matrices of the same size */
/* if the multiplication is successful, return the results */

double **Matrix_matrix_multiply(double **matrixa, double **matrixb, int size)
{
   double sum = 0;
   double** output = allocateSpace(size);
   if(output == NULL){
      return NULL;
   }
   int i, j, k; //counter
   for (i = 0; i <size; i++) {
      for (j = 0; j < size; j++) {
         for (k = 0; k < size; k++) {
            sum += matrixa[i][k] * matrixb[k][j];
         }
         output[i][j] = sum;
         sum = 0;
      }
   }
   
   return output;
}

/* return the sum of the absolute differences between the */
/* entries of a matrix of a given size and the corresponding */
/* entries of an identity matrix of the same size */

double Deviation_from_identity(double **matrix, int size)
{
   double** identity = createIdentity(size);
   double sum = 0;
   int i, j; //counters
   
   for(i = 0; i < size; i++){
      for (j = 0; j < size; j++) {
         sum += fabs(matrix[i][j] - identity[i][j]);
      }
   }
   
   deallocateSpace(identity, size);
   deallocateSpace(matrix, size);
   return sum;
}

//Allocate space for data
double ** allocateSpace(int size)
{
   //Initializing maze dynamically
   double** data = (double **)malloc(size * sizeof(double *));
   
   //Checking to see if memory allocation was successful
   if (data == 0) {
      fprintf(stderr, "ERROR: Memory allocation unsuccessful.\n");
      deallocateSpace(data,0);
      return NULL;
   }
   
   int row; //Incrememnting through the rows
   
   for (row = 0; row < size; row++) {
      data[row] = (double *)malloc(size * sizeof(double));
      if (data[row] == 0) {
         fprintf(stderr, "ERROR: Memory allocation unsuccessful.\n");
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
