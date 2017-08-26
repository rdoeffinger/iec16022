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

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#ifdef _WIN32
static inline unsigned htonl(unsigned i)
{
    return (i >> 24) | ((i & 0x00ff0000) >> 8) |  ((i & 0x0000ff00) << 8) | (i << 24);
}
#else
#include <arpa/inet.h>
#endif
#include "image.h"

#define	INTERLACE
#define CLEAR
#define USEZLIB

#ifdef USEZLIB
#include <zlib.h>
#endif

Image *ImageNew(int w, int h, int c)
{				// create a new blank image
	Image *i = NULL;
	if (!w || !h)
		goto err_out;
	i = calloc(1, sizeof(*i));
	if (!i)
		goto err_out;
	i->W = w;
	i->L = w + 1;
	i->H = h;
	i->C = c;
	i->Image = calloc(h, w + 1);
	if (!i->Image)
		goto err_out;
	if (c) {
		i->Colour = calloc(c, sizeof(Colour));
		if (!i->Colour)
			goto err_out;
	}
	return i;

err_out:
	ImageFree(i);
	return 0;
}

void ImageFree(Image * i)
{				// free an image
	if (i) {
		free(i->Image);
		free(i->Colour);
		free(i);
	}
}

// PNG code

      /* Table of CRCs of all 8-bit messages. */
static unsigned int crc_table[256];

      /* Make the table for a fast CRC. */
static void make_crc_table(void)
{
	unsigned int c;
	int n, k;
	for (n = 0; n < 256; n++) {
		c = (unsigned int)n;
		for (k = 0; k < 8; k++) {
			if (c & 1)
				c = 0xedb88320L ^ (c >> 1);
			else
				c = c >> 1;
		}
		crc_table[n] = c;
	}
}

static unsigned int writecrc(int fh, const char *ptr, int len, unsigned int c)
{
	write(fh, ptr, len);
	while (len--)
		c = crc_table[(c ^ *ptr++) & 0xff] ^ (c >> 8);
	return c;
}

static void writechunk(int fh, const char *typ, const void *ptr, int len)
{
	unsigned int v = htonl(len), crc;
	write(fh, &v, 4);
	crc = writecrc(fh, typ, 4, ~0);
	if (len)
		crc = writecrc(fh, ptr, len, crc);
	v = htonl(~crc);
	write(fh, &v, 4);
}

#ifndef USEZLIB
static unsigned int adlersum(const unsigned char *p, int l, unsigned int adler)
{
	unsigned int s1 = (adler & 65535), s2 = (adler >> 16);
	while (l--) {
		s1 += *p++;
		s2 += s1;
	}
	s1 %= 65521;		// can be delayed due to sensible "l" values...
	s2 %= 65521;
	return (s2 << 16) + s1;
}
#endif

// write PNG image
void ImageWritePNG(Image * i, int fh, int back, int trans, const char *comment)
{
	make_crc_table();
	write(fh, "\211PNG\r\n\032\n", 8);	// PNG header
	{			// IHDR
		struct {
			unsigned int width;
			unsigned int height;
			unsigned char depth;
			unsigned char colour;
			unsigned char compress;
			unsigned char filter;
			unsigned char interlace;
		} ihdr = {
		0, 0, 8, 3, 0, 0, 0};
		ihdr.width = htonl(i->W);
		ihdr.height = htonl(i->H);
		writechunk(fh, "IHDR", &ihdr, 13);
	}
	{			// PLTE
		unsigned int v = htonl(i->C * 3), crc, n;
		write(fh, &v, 4);
		crc = writecrc(fh, "PLTE", 4, ~0);
		for (n = 0; n < i->C; n++) {
			v = htonl(i->Colour[n] << 8);
			crc = writecrc(fh, (void *)&v, 3, crc);
		}
		v = htonl(~crc);
		write(fh, &v, 4);
	}
	if (back >= 0) {	// bKGD
		unsigned char b = back;
		writechunk(fh, "bKGD", &b, 1);
	}
	if (*comment) {		// tEXt
		static const char c[] = "Comment";
		unsigned int v = htonl(strlen(c) + strlen(comment) + 1), crc;
		write(fh, &v, 4);
		crc = writecrc(fh, "tEXt", 4, ~0);
		crc = writecrc(fh, c, strlen(c) + 1, crc);
		crc = writecrc(fh, comment, strlen(comment), crc);
		v = htonl(~crc);
		write(fh, &v, 4);
	}
	{			// tRNS
		int has_alpha = 0;
		unsigned char alpha[256];
		int n;
		for (n = 0; n < i->C; n++) {
			// 4th palette byte treated as 0=opaque, 255-transparren
			alpha[n] = 255 - (i->Colour[n] >> 24);
			has_alpha |= alpha[n] != 255;
		}
		if (trans >= 0 && trans < i->C) {
			// manual set of specific transparrent colour
			alpha[trans] = 0;
			has_alpha = 1;
		}
		if (has_alpha) writechunk(fh, "tRNS", alpha, i->C);
	}
#ifndef USEZLIB
	{			// IDAT
		unsigned int v = htonl(i->H * (i->L + 5) + 6),
		    crc, adler = 1, n;
		unsigned char *p = i->Image;
		write(fh, &v, 4);
		crc = writecrc(fh, "IDAT", 4, ~0);
		crc = writecrc(fh, "\170\001", 2, crc);	// zlib header for deflate
		n = i->H;
		while (n--) {
			unsigned char h[5];
			h[0] = (n ? 0 : 1);	// last chunk in deflate, un compressed
			h[1] = (i->L & 255);	// Len, LSB first as per deflate spec
			h[2] = (i->L / 256);
			h[3] = ~(i->L & 255);	// Inverse of Len
			h[4] = ~(i->L / 256);
			*p = 0;	// filter 0 (NONE)
			crc = writecrc(fh, h, 5, crc);
			crc = writecrc(fh, p, i->L, crc);
			adler = adlersum(p, i->L, adler);
			p += i->L;
		}
		v = htonl(adler);
		crc = writecrc(fh, (void *)&v, 4, crc);
		v = htonl(~crc);
		write(fh, &v, 4);
	}
#else
	{			// IDAT
		unsigned char *temp;
		unsigned long n;
		for (n = 0; n < i->H; n++)
			i->Image[n * i->L] = 0;	// filter 0
		n = i->H * i->L * 1001 / 1000 + 12;
		temp = malloc(n);
		if (compress2(temp, &n, i->Image, i->L * i->H, 9) != Z_OK)
			fprintf(stderr, "Deflate error\n");
		else
			writechunk(fh, "IDAT", temp, n);
		free(temp);
	}
#endif
	writechunk(fh, "IEND", 0, 0);	// IEND
}
