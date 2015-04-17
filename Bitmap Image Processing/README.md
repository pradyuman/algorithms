This program performs various bitmap image processing functions.

Usage: run `gcc bmp.c main.c -o bmp` in the command line and then call `./bmp` with the following commands:

**Input files must be in bitmap format**

* `./bmp -t [input file] [output file]`: This function creates an output file that contains the top half of the input image.
* `./bmp -l [input file] [output file]`: This function creates an output file that contains the left half of the input image.
* `./bmp -c [input file] [output file]`: This command converts a 16 bit image to a 24 bit image or a 24 bit image to a 16 bit image (without dithering) and stores it in the output file. The program will automatically detect the format of the input image and will convert accordingly.
* `./bmp -d [input file] [output file]`: This command converts a 24 bit image to a 16 bit image WITH DITHERING (using the Floyd-Steinberg Dithering algorithm) and stores it in the output file. If the input file is 16 bits, the program will convert it to 24 bits without dithering. The program will automatically detect the format of the input image and will convert accordingly.


