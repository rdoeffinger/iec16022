// Image handling tools, (c) AJK 2001
// Indended for use in applications that need to make images for web pages on the fly

typedef unsigned int Colour;	// RGB value

// Image object
typedef struct
{
   int      W,                  // width
	    L,			// Line length in Image (W+1)
            H;                  // height
   unsigned char *Image;        // image array, one byte per pixel
   int      C;                  // colours (can be non power of 2, max 256)
   Colour  *Colour;             // colour map (must have entry for each colour)
}
Image;

// macros and functions

#define ImagePixel(i,x,y)	((i)->Image[1+(i)->L*(y)+(x)])

Image *ImageNew(int w,int h,int c);		// create a new blank image
void ImageFree(Image* i);			// free an image
void ImageWriteGif(Image *i,int fh,int back,int trans,char *comment);
void ImageWritePNG(Image *i,int fh,int back,int trans,char *comment);
void ImageText(Image *i,int x,int y,int c,char *text);	// write 8x8 text
void ImageSmall(Image *i,int x,int y,int c,char *text);	// write 4x6 text
void ImageRect(Image *i,int x,int y,int w,int h,int c);	// fill a box
#define ImageWrite ImageWritePNG	// default
