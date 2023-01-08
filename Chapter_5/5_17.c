#include <stdint.h>

typedef unsigned long size_t;

void *memset(void *s, unsigned long c, size_t n) {
    size_t cnt = 0, k = sizeof(c);
    unsigned char *schar = s;
    unsigned long *slong;

    while ((uintptr_t) s % k != 0 && cnt < n) {
        *schar++ = (unsigned char) c;
        cnt++;
    }

    slong = (unsigned long) schar;
    
    for(;(cnt < n - k) && (n - k < n); slong++, cnt += k) {
        *slong = c;
    }

    schar = (unsigned char) slong;

    while(cnt < n) {
        *schar++ = (unsigned char) c;
        cnt++;
    }
}

void *basic_memset(void *s, int c, size_t n) {
    size_t cnt = 0;
    unsigned char *schar = s;
    while (cnt < n) {
        *schar++ = (unsigned char) c;
        cnt++;
    }

    return s;
}