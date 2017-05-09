// To run fuzzer use:
// CC=clang-5.0 ./configure --disable-shared
// make CFLAGS="-g3 -Og -fsanitize=fuzzer,address" fuzzer
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "iec16022ecc200.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    int w = 0, h = 0;
    char *enc = NULL;
    unsigned char *res = iec16022ecc200f(&w, &h, &enc, size, data, NULL, NULL, NULL, 0);
    free(res);
    free(enc);
    return 0;  // Non-zero return values are reserved for future use.
}
