This program calculates the inverse of a matrix using the Gauss-Jordan algorithm.

Usage: run `make` in the command line and then call `./matrix` with the following commands:

**Input files must be in binary format**

* `./matrix -i [input file (matrix)] [output file]`: This calculates the inverse of the matrix in the input file and outputs the matrix to the output file.
* `./matrix -m [input file (matrix 1)] [input file (matrix 2)] [output file]`: This multiplies two matrices and stores the output in the output file. You can check to see if your inverse is correct by multiplying the inverse with it's original and checking to see if the output is an identity matrix.
* `./matrix -d [input file]`: This calculates how different a matrix is from it's identity matrix.

To clean your directory, run `make clean`. This will remove all object and executable files from your directory.


