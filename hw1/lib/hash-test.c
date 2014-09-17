#include <stdio.h>
#include <string.h>
#include "hash.h"

int main()
{   /* test out the hash function */
    int i, hash;
    char cur;
    int size = (int)(sizeof(cur) * 8 - 1);

    for (i = 65; i <= 90; i++) {
        cur = (char)i;  // uppercase
        hash = adler32(&cur, strlen(&cur));
        printf("hash of %c: (%i) mod 2^%i = %c\n",
            cur, hash, size, hash);
        cur = (char)(i + 32);  // lowercase
        hash = adler32(&cur, strlen(&cur));
        printf("hash of %c: (%i) mod 2^%i = %c\n",
            cur, hash, size, hash);
    }
}
