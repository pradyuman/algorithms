#ifndef PA_ANSWER03_H
#define PA_ANSWER03_H

/* define what is small enough to be considered 0 */

#define TOL 1e-10

/* read a matrix from a file, return the matrix */
/* store the size of the matrix in *size        */

double **Read_matrix_from_file(char *filename, int *size);

/* write a matrix of a given size to a file, return 1 if the write is */
/* successful, otherwise, 0 */

int Write_matrix_to_file(char *filename, double **matrix, int size);

/* invert a matrix of a given size */
/* if inversion is successful, return the inverse */
/* otherwise, return NULL */

double **Invert_matrix(double **matrix, int size);

/* multiply two matrices of the same size */
/* if the multiplication is successful, return the results */

double **Matrix_matrix_multiply(double **matrixa, double **matrixb, int size);

/* return the sum of the absolute differences between the */
/* entries of a matrix of a given size and the corresponding */
/* entries of an identity matrix of the same size */

double Deviation_from_identity(double **matrix, int size);

//Allocate space
double** allocateSpace(int size);

//Deallocate space
void deallocateSpace(double **data, int size);

//Create identity matrix
double** createIdentity(int size);

#endif
