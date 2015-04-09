#include <stdlib.h>
#include <stdio.h>

#include "bmp.h"

/* check whether a header is valid
 * assume that header has been read from fptr
 */

int Is_BMP_Header_Valid(BMP_Header* header, FILE *fptr) {
  // Make sure this is a BMP file
  if (header->type != 0x4d42) {
     return FALSE;
  }

  // check the offset from beginning of file to image data
  // essentially the size of the BMP header
  // BMP_HEADER_SIZE for this exercise/assignment
  if (header->offset != BMP_HEADER_SIZE) {
     return FALSE;
  }
      
  // check the DIB header size == DIB_HEADER_SIZE
  if (header->DIB_header_size != DIB_HEADER_SIZE) {
     return FALSE;
  }

  // Make sure there is only one image plane
  if (header->planes != 1) {
    return FALSE;
  }
  // Make sure there is no compression
  if (header->compression != 0) {
    return FALSE;
  }

  // skip the test for xresolution, yresolution

  // ncolours and importantcolours should be 0
  if (header->ncolours != 0) {
    return FALSE;
  }
  if (header->importantcolours != 0) {
    return FALSE;
  }
  
  // Make sure we are getting 24 bits per pixel
  // or 16 bits per pixel
  if (header->bits != 24 && header->bits != 16) {
    return FALSE;
  }

  // check for file size, image size
  // based on bits, width, and height
   int padding = (header->width * header->bits / 8 + 3) / 16;
   
   if (header->bits == 24){
      //Checking if imagesize is correct
      if (header->imagesize != padding * (header->width * header->height * 3)) {
         return FALSE;
      }
      //Checking is size is correct
      if(header->size != padding * (header->width * header->height * 3) + 54){
         return FALSE;
      }
      
   }
   else if (header->bits == 16){
      //Checking if imagesize is correct
      if (header->imagesize != padding * (header->width * header->height * 2)) {
         return FALSE;
      }
      //Checking if size is correct
      if(header->size != padding * (header->width * header->height * 2) + 54){
         return FALSE;
      }
   }

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
   if (!Is_BMP_Header_Valid(&(bmp_image->header), fptr))
      return NULL;

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
   
   BMP_Image *topCrop = NULL;
   
   topCrop = (BMP_Image *)malloc(sizeof(BMP_Image));
   //If memory allocation failed
   if (topCrop == NULL) {
      return NULL;
   }
   
   //Divide height by two
   long int height = image->header.height / 2 + image->header.height % 2;
   
   //Setting new image header to the same information as input image header
   topCrop->header = image->header;
   
   //Replacing height from old image with new height (that was divided by two)
   topCrop->header.height = height;

   //Padding
   int padding = (topCrop->header.width * topCrop->header.bits / 8 + 3) / 16;

   //New image size is padding * height
   topCrop->header.imagesize = padding * height;
   
   //New total file size is new imagesize + 54
   topCrop->header.size = topCrop->header.imagesize + 54;
   
   //Write to file
   unsigned char *writeData = (unsigned char *)malloc(topCrop->header.imagesize);
   //Checking to see if the allocation was successful
   if (writeData == NULL) {
      return NULL;
   }
   
   int bound = image->header.imagesize - topCrop->header.imagesize;
   
   int i; //counter
   
   for (i = 0; i < topCrop->header.imagesize; i++) {
      writeData[i] = (image->data)[bound+i];
   }
   
   //Saving to bmp image
   topCrop->data = writeData;
   
   printf("complete\n");
   
   return NULL;
}

/* Given a BMP_Image, create a new image that retains left half of the given 
 * image
 */
BMP_Image *Left_Half_BMP_Image(BMP_Image *image)
{
   printf("Did not complete\n");
   return NULL;
}
