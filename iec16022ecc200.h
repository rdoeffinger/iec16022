// IEC16022 encoder, see IEC16022
// $Log: iec16022ecc200.h,v $
// Revision 1.3  2004/09/09 07:45:09  cvs
// Added change history to source files
// Added "info" type to IEC16022
// Added exact size checking shortcodes on encoding generation for iec16022
//

// Main encoding function
// Returns the grid (malloced) containing the matrix. L corner at 0,0.
// Takes suggested size in *Wptr, *Hptr, or 0,0. Fills in actual size.
// Takes barcodelen and barcode to be encoded
// Note, if *encodingptr is null, then fills with auto picked (malloced) encoding
// If lenp not null, then the length of encoded data before any final unlatch or pad is stored
// If maxp not null, then the max storage of this size code is stored
// If eccp not null, then the number of ecc bytes used in this size is stored
// Returns 0 on error (writes to stderr with details).

unsigned char *
iec16022ecc200 (int *Wptr, int *Hptr, char **encodingptr, int barcodelen, unsigned char *barcode, int *lenp,int *maxp,int *eccp);
#define MAXBARCODE 3116

