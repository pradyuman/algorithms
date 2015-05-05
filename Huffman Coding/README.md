This program performs various Huffman Coding operations to compress and decompress character and binary based files.

Usage: run `make` in the command line and then call `./huffman` with the following commands:

* `./huffman -pc [input file (character-based)] [output file]`: This command takes two input arguments, a compressed file that has a character-based header and an output file name. The program finds the huffman code for each character used in the file and saves the codes in the output file.
* `./huffman -dc [input file (character-based)] [output file]`: This command takes two input arguments, a compressed file that has a character-based header and an output file name. The program decompresses the file into the original text and saves the decoded information in the output file.
* `./huffman -pb [input file (bit-based)] [output file]`: This command takes two input arguments, a compressed file that has a bit-based header and an output file name. The program finds the huffman code for each character used in the file and saves the codes in the output file.
* `./huffman -db [input file (bit-based)] [output file]`: This command takes two input arguments, a compressed file that has a bit-based header and an output file name. The program decompresses the file into the original text and saves the decoded information in the output file.

Some sample files with character-based or bit-based headers are included in the *sample* folder.

To clean your directory, run `make clean`. This will remove all object and executable files from your directory.

Errors:
* 01: Incorrect number of input arguments
* 02: Input file could not be opened
* 03: Memory allocation unsuccessful
* 04: Huffman tree could not be created
* 05: Output file could not be opened or created
* 06: Tree could not be constructed
* 07: List node could not be constructed
* 08: Input flag is not valid
* 09: Input file could not be decoded
