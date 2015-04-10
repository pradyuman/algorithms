#include <stdlib.h>
#include <stdio.h>

#include "bmp.h"

/* check whether a header is valid
 * assume that header has been read from fptr
 */

int Is_BMP_Header_Valid(BMP_Header* header, FILE *fptr) {
  // Make sure this is a BMP file
  if (header->type != 0x4d42)
     return FALSE;

  // check the offset from beginning of file to image data
  // essentially the size of the BMP header
  if (header->offset != BMP_HEADER_SIZE)
     return FALSE;
      
  // check the DIB header size == DIB_HEADER_SIZE
  if (header->DIB_header_size != DIB_HEADER_SIZE)
     return FALSE;

  // Make sure there is only one image plane
  if (header->planes != 1)
    return FALSE;
  // Make sure there is no compression
  if (header->compression != 0)
    return FALSE;

  // skip the test for xresolution, yresolution

  // ncolours and importantcolours should be 0
  if (header->ncolours != 0)
    return FALSE;
   
  if (header->importantcolours != 0)
    return FALSE;
  
  // Make sure we are getting 24 bits per pixel
  // or 16 bits per pixel
  if (header->bits != 24 && header->bits != 16)
    return FALSE;

  // check for file size, image size
  // based on bits, width, and height
  int padding = (header->width * header->bits / 8 + 3) / 4 * 4;
  int size = padding * header->height;
   
  if (header->imagesize != size)
     return FALSE;
  
  if (header->size != size + 54)
     return FALSE;

  return TRUE;
}

/* The input argument is the source file pointer. 
 * The function returns an address to a dynamically allocated BMP_Image only 
 * if the file * contains a valid image file 
 * Otherwise, return NULL
 * If the function cannot get the necessary memory to store the image, also 
 * return NULL
 */
BMP_Image *Read_BMP_Image(FILE* fptr) {
   //Rewinding the file pointer
   rewind(fptr);

   BMP_Image *bmp_image = NULL;

   //Allocate memory for BMP_Image*;
   bmp_image = (BMP_Image *)calloc(sizeof(BMP_Image),1);

   //Read the first 54 bytes of the source into the header
   fread(&(bmp_image->header), 54, 1, fptr);
   
   //Checking to see if fread working properly
   if (&(bmp_image->header) == NULL)
      return NULL;

   // if read successful, check validity of header
   if (!Is_BMP_Header_Valid(&(bmp_image->header), fptr)){
      Free_BMP_Image(bmp_image);
      return NULL;
   }
   // Allocate memory for image data
   BMP_Header *temp = &(bmp_image->header);
   int imageSize = temp->imagesize;
   //size of image
   bmp_image->data = (unsigned char *)malloc(imageSize);
  
   // read in the image data
   fread(bmp_image->data, imageSize, 1, fptr);

   return bmp_image;
}

/* The input arguments are the destination file pointer, BMP_Image *image.
 * The function write the header and image data into the destination file.
 * return TRUE if write is successful
 * FALSE otherwise
 */
int Write_BMP_Image(FILE* fptr, BMP_Image* image) 
{
   rewind(fptr);
   // write header
   fwrite(&(image->header), 54, 1, fptr);
   //Checking to see if something got written to fptr
   if(fptr == NULL)
      return FALSE;
   
   // write image data
   int fileSize = (image->header).imagesize;
   
   fwrite(image->data, fileSize, 1, fptr);
   
   if(fptr == NULL)
      return FALSE;

   return TRUE;
}

/* The input argument is the BMP_Image pointer. The function frees memory of 
 * the BMP_Image.
 */
void Free_BMP_Image(BMP_Image* image) {
   free(image->data);
   free(image);
}

/* Given a BMP_Image, create a new image that retains top half of the 
 * given image
 */
BMP_Image *Top_Half_BMP_Image(BMP_Image *image)
{
   BMP_Image *topCrop = (BMP_Image *)malloc(sizeof(BMP_Image));
   //If memory allocation failed
   if (topCrop == NULL)
      return NULL;
   
   //Divide height by two
   int height = image->header.height / 2 + image->header.height % 2;
   
   //Setting new image header to the same information as input image header
   topCrop->header = image->header;
   
   //Replacing height from old image with new height (that was divided by two)
   topCrop->header.height = height;

   //Padding (width)
   int padding = (topCrop->header.width * topCrop->header.bits / 8 + 3) / 4 * 4;

   //New image size is padding * height
   topCrop->header.imagesize = padding * height;
   
   //New total file size is new imagesize + 54
   topCrop->header.size = topCrop->header.imagesize + 54;
   
   //Write to file
   unsigned char *writeData = (unsigned char *)malloc(topCrop->header.imagesize);
   //Checking to see if the allocation was successful
   if (writeData == NULL){
      free(topCrop);
      return NULL;
   }
   
   int bound = image->header.imagesize - topCrop->header.imagesize;
   
   int i; //counter
   
   for (i = 0; i < topCrop->header.imagesize; i++) {
      writeData[i] = (image->data)[bound+i];
   }
   
   //Saving to bmp image
   topCrop->data = writeData;
   
   return topCrop;
}

/* Given a BMP_Image, create a new image that retains left half of the given 
 * image
 */
BMP_Image *Left_Half_BMP_Image(BMP_Image *image)
{
   BMP_Image *leftCrop = (BMP_Image *)malloc(sizeof(BMP_Image));
   //If memory allocation failed
   if (leftCrop == NULL) {
      return NULL;
   }
   
   //Divide width by two
   int width = image->header.width / 2 + image->header.width % 2;
   
   //Setting new image header to the same information as input image header
   leftCrop->header = image->header;
   
   //Replacing width from old image with new width (that was divided by two)
   leftCrop->header.width = width;
   
   //Padding (width)
   int padding = (leftCrop->header.width * leftCrop->header.bits / 8 + 3) / 4 * 4;
   
   //New image size is padding * height
   leftCrop->header.imagesize = padding * leftCrop->header.height;
   
   //New total file size is new imagesize + 54
   leftCrop->header.size = leftCrop->header.imagesize + 54;
   
   //Write to file
   leftCrop->data = (unsigned char*)malloc(padding * leftCrop->header.height);
   //Checking to see if the allocation was successful
   if(leftCrop->data == NULL){
      free(leftCrop);
      return NULL;
   }
   
   //Need to save data by coordinates (so the array indexes are r x c)
   int bound = padding - leftCrop->header.width * leftCrop->header.bits / 8;
   int inputPadding = (image->header.width * image->header.bits / 8 + 3) / 4 * 4;
   
   //Easier access to input and output data
   unsigned char (*writeData)[padding] = (unsigned char (*)[padding])leftCrop->data;
   unsigned char (*inputData)[inputPadding] = (unsigned char (*)[inputPadding])image->data;
   
   int i, j; //counter
   
   for (i = 0; i < leftCrop->header.height; i++) {
      //Writing data
      for (j = 0; j < padding - bound; j++) {
         writeData[i][j] = inputData[i][j];
      }
      //Adding padding zeroes
      while (j < padding) {
         writeData[i][j] = 0;
         j++;
      }
   }
   
   //Saving to bmp image
   for (i = 0; i < padding * leftCrop->header.height; i++) {
      leftCrop->data[i] = ((unsigned char *)writeData)[i];
   }
   
   return leftCrop;
}

// Given a BMP_Image, create a new 16-bit image that is converted from a given
// 24-bit image
//
BMP_Image *Convert_24_to_16_BMP_Image(BMP_Image *image) {
   BMP_Image *converted = (BMP_Image *)malloc(sizeof(BMP_Image));
   //If memory allocation failed
   if (converted == NULL)
      return NULL;
   
   //context variables
   int width = image->header.width;
   int height = image->header.height;
   
   //padding will only be 0 or 2
   int padding = width * 2 % 4;
   
   //Setting new image header to the same information as input image header
   converted->header = image->header;
   
   //Changing bits from 24 to 16
   converted->header.bits = 16;
   
   //Setting new imagesize
   converted->header.imagesize = height * (width * 2 + padding);
   
   //Setting new size
   converted->header.size = converted->header.imagesize + 54;
   
   int i, j; //counter
   uint16_t pixel = 0;
   uint16_t r = 0;
   uint16_t g = 0;
   uint16_t b = 0;
   
   /*since converted->data is an array of unsigned char (8 bits),
    *need to split each 16 bit pixel into two before writing to the array
    */
   unsigned char pixel_l; //left side of 16 bit pixel
   unsigned char pixel_r; //right side of 16 bit pixel
   
   for (i = 0; i < height; i++) {
      for (j = i * (width * 2 + padding); width; j += 3) {
         //Resetting all 16 bits of pixel to 0
         pixel = 0;
         /*Getting rgb values from image and making them 5 bits
          *Shifting over by 10/5/0 (r/g/b) so that when bitwise OR
          *is used, no data is lost.
          */
         r = (image->data[j] >> 3) << 10;
         g = (image->data[j+1] >> 3) << 5;
         b = image->data[j+2] >> 3;
         //Since pixel is all zeroes, bitwise OR will just import all the asserted values
         pixel = pixel | r | g | b;
         
         //Splitting pixel into two 8 bit parts
         pixel_l = pixel >> 8;
         pixel_r = pixel >> 8 << 8; //adds zeroes
         
         converted->data[j] = pixel_l;
         converted->data[j+1] = pixel_r;
      }
      if(padding){
         converted->data[j + 1] = 0;
         converted->data[j + 2] = 0;
      }
   }
   
   return converted;
}

// Given a BMP_Image, create a new 16-bit image that is converted from a given
// 24-bit image
//
BMP_Image *Convert_16_to_24_BMP_Image(BMP_Image *image){
   return NULL;
}
