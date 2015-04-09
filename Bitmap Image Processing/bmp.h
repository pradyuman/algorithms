#ifndef _BMP_H_
#define _BMP_H_
#include <stdint.h>

#define BMP_HEADER_SIZE 54
#define DIB_HEADER_SIZE 40
#define TRUE 1
#define FALSE 0

/* bit positions of RGB in a 16-bit representation */
/* R: 0111110000000000 */
/* G: 0000001111100000 */
/* B: 0000000000011111 */

#define RED_MASK 0x7C00
#define GREEN_MASK 0x03E0
#define BLUE_MASK 0x001F

/* position from the least significant position */

#define RED_BIT 10
#define GREEN_BIT 5
#define BLUE_BIT 0

#pragma pack(push)  // save the original data alignment
#pragma pack(1)     // Set data alignment to 1 byte boundary

/*
 * BMP files are laid out in the following fashion:
 *   --------------------------
 *   |          Header        |   54 bytes
 *   |-------------------------
 *   |    Palette (optional)  |   0 bytes (for 24-bit RGB images)
 *   |-------------------------
 *   |       Image Data       |   file size - 54 (for 24-bit images)
 *   --------------------------
 */

/** 
 * BMP header (54 bytes).
 */

typedef struct _BMP_Header {
    uint16_t type;			// Magic identifier
    uint32_t size;			// File size in bytes
    uint16_t reserved1;			// Not used
    uint16_t reserved2;			// Not used
    uint32_t offset;			// Offset to image data in bytes from beginning of file (54 bytes)
    uint32_t DIB_header_size;		// DIB Header size in bytes (40 bytes)
    int32_t  width;			// Width of the image
    int32_t  height;			// Height of image
    uint16_t planes;			// Number of color planes
    uint16_t bits;			// Bits per pixel
    uint32_t compression;		// Compression type
    uint32_t imagesize;			// Image size in bytes
    int32_t  xresolution;		// Pixels per meter
    int32_t  yresolution;		// Pixels per meter
    uint32_t ncolours;			// Number of colors  
    uint32_t importantcolours;		// Important colors
} BMP_Header;

#pragma pack(pop) // restore the previous pack setting

typedef struct _BMP_Image {
    BMP_Header header;
    unsigned char *data; 
} BMP_Image;


// Read BMP_Image from a given file
//
BMP_Image *Read_BMP_Image(FILE *fptr);

// Check the validity of the header with the file from which the header is read
//
int Is_BMP_Header_Valid(BMP_Header *bmp_hdr, FILE *fptr);

// Write BMP_Image to a given file
//
int Write_BMP_Image(FILE *fptr, BMP_Image *image);

// Free memory in a given image
//
void Free_BMP_Image(BMP_Image *image);

// Given a BMP_Image, create a new image that retains top half of the given image
//
BMP_Image *Top_Half_BMP_Image(BMP_Image *image);

// Given a BMP_Image, create a new image that retains left half of the given image
//
BMP_Image *Left_Half_BMP_Image(BMP_Image *image);

// Given a BMP_Image, create a new 16-bit image that is converted from a given 
// 24-bit image
//
BMP_Image *Convert_24_to_16_BMP_Image(BMP_Image *image);

// Given a BMP_Image, create a new 16-bit image that is converted from a given 
// 24-bit image
//
BMP_Image *Convert_16_to_24_BMP_Image(BMP_Image *image);
#endif /* bmp.h */
