typedef unsigned long size_t;
#define NULL 0

#define __min_bytes_for_long_copy 32

void __copy_longs_aligned(void* dst, const void* src, unsigned long n);
void __copy_longs_rev_aligned(void* dst, const void* src, unsigned long n);
void __copy_longs_unaligned(void* dst, const void* src, unsigned long n);
void __copy_longs_rev_unaligned(void* dst, const void* src, unsigned long n);

int memcmp(const void* src1, const void* src2, size_t n) {
    const unsigned char* p1;
    const unsigned char* p2;

    for (p1 = (const unsigned char*)src1 - 1, p2 = (const unsigned char*)src2 - 1, n++; --n;)
        if (*++p1 != *++p2)
            return ((*p1 < *p2) ? -1 : +1);

    return (0);
}

void* __memrchr(const void* src, int val, size_t n) {
    const unsigned char* p;
    unsigned long v = (val & 0xff);

    for (p = (unsigned char*)src + n, n++; --n;)
        if (*--p == v)
            return ((void*)p);

    return (NULL);
}

void* memchr(const void* src, int val, size_t n) {
    const unsigned char* p;
    unsigned long v = (val & 0xff);

    for (p = (unsigned char*)src - 1, n++; --n;)
        if ((*++p & 0xff) == v)
            return ((void*)p);

    return (NULL);
}

void* memmove(void* dst, const void* src, size_t n) {
    unsigned char* csrc;
    unsigned char* cdst;
    int reverse = (unsigned long)src < (unsigned long)dst;

    if (n >= __min_bytes_for_long_copy) {
        if ((((int)dst ^ (int)src)) & 3)
            if (!reverse)
                __copy_longs_unaligned(dst, src, n);
            else
                __copy_longs_rev_unaligned(dst, src, n);
        else if (!reverse)
            __copy_longs_aligned(dst, src, n);
        else
            __copy_longs_rev_aligned(dst, src, n);

        return (dst);
    } else {
        if (!reverse) {
            csrc = ((unsigned char*)src) - 1;
            cdst = ((unsigned char*)dst) - 1;

            n++;

            while (--n)
                *++cdst = *++csrc;
        } else {
            csrc = (unsigned char*)src + n;
            cdst = (unsigned char*)dst + n;

            n++;

            while (--n)
                *--cdst = *--csrc;
        }
    }

    return (dst);
}
