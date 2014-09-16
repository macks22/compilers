#include "hash.h"

uint32_t
adler32(const void *buf, size_t buflength)
{    /* 32 bit Adler Checksum function.
        Call like so:
            hash = adler32(word, strlen(word));
      */
     const uint8_t *buffer = (const uint8_t*)buf;

     uint32_t s1 = 1;
     uint32_t s2 = 0;
     size_t n;

     for (n = 0; n < buflength; n++) {
        s1 = (s1 + buffer[n]) % 65521;
        s2 = (s2 + s1) % 65521;
     }
     return (s2 << 16) | s1;
}
