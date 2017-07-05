/**
 *
 * Image handling tools, (c) AJK 2001-2005
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 *
 */

#ifndef __IMAGE_H
#define __IMAGE_H

typedef unsigned int Colour;	// RGB value

// Image object
typedef struct {
	int W,			// width
	 L,			// Line length in Image (W+1)
	 H;			// height
	unsigned char *Image;	// image array, one byte per pixel
	int C;			// colours (can be non power of 2, max 256)
	Colour *Colour;		// colour map (must have entry for each colour)
} Image;

// macros and functions

#define ImagePixel(i,x,y)	((i)->Image[1+(i)->L*(y)+(x)])

Image *ImageNew(int w, int h, int c);	// create a new blank image
void ImageFree(Image * i);	// free an image
void ImageWritePNG(Image * i, int fh, int back, int trans, const char *comment);

#endif				/* __IMAGE_H */
