typedef unsigned long size_t;

#define K1 0x80808080
#define K2 0xfefefeff

#ifdef VERSION_G8ME01
/** US only: strstr (used by evt_msg). */
char* strstr(const char* str, const char* pat) {
    const unsigned char* s1 = (const unsigned char*)str - 1;
    const unsigned char* p1 = (const unsigned char*)pat;
    unsigned long firstc, c1, c2;

    if ((pat == 0) || (!(firstc = *p1)))
        return ((char*)str);

    while (c1 = *++s1) {
        if (c1 == firstc) {
            const unsigned char* s2 = s1 - 1;
            const unsigned char* p2 = p1 - 1;

            while ((c1 = *++s2) == (c2 = *++p2) && c1)
                ;

            if (!c2)
                return ((char*)s1);
        }
    }

    return 0;
}
#endif

/** Standard strchr(): first occurrence of chr in the string; searching for 0 returns the terminator. */
char* strchr(const char* str, int chr) {
    const unsigned char* p = (unsigned char*)str - 1;
    unsigned long c = (chr & 0xff);
    unsigned long ch;

    while (ch = *++p)
        if (ch == c)
            return ((char*)p);

    return (c ? 0 : (char*)p);
}

/**
 * Standard strncmp(): compares up to n bytes as unsigned chars;
 * returns the difference of the first differing bytes, 0 if equal or both end.
 */
int strncmp(const char* str1, const char* str2, size_t n) {
    const unsigned char* p1 = (unsigned char*)str1 - 1;
    const unsigned char* p2 = (unsigned char*)str2 - 1;
    unsigned long c1, c2;

    n++;

    while (--n)
        if ((c1 = *++p1) != (c2 = *++p2))
            return (c1 - c2);
        else if (!c1)
            break;

    return (0);
}

/**
 * Standard strcmp(): compares as unsigned chars;
 * the optimized version aligns and compares a word at a time
 * when both strings have the same alignment (using the K1/K2 zero-byte test), falling back to bytes otherwise.
 * Returns a byte difference, or +1/-1 from a word compare.
 */
int strcmp(const char* str1, const char* str2) {
    register unsigned char* left = (unsigned char*)str1;
    register unsigned char* right = (unsigned char*)str2;
    unsigned long align, l1, r1, x;

    l1 = *left;
    r1 = *right;
    if (l1 - r1) {
        return (l1 - r1);
    }

    if ((align = ((int)left & 3)) != ((int)right & 3)) {
        goto bytecopy;
    }
    if (align) {
        if (l1 == 0) {
            return 0;
        }
        for (align = 3 - align; align; align--) {
            l1 = *(++left);
            r1 = *(++right);
            if (l1 - r1) {
                return (l1 - r1);
            }
            if (l1 == 0) {
                return 0;
            }
        }
        left++;
        right++;
    }

    l1 = *(int*)left;
    r1 = *(int*)right;
    x = l1 + K2;
    if (x & K1) {
        goto adjust;
    }
    while (l1 == r1) {
        l1 = *(++((int*)(left)));
        r1 = *(++((int*)(right)));
        x = l1 + K2;
        if (x & K1) {
            goto adjust;
        }
    }
    if (l1 > r1) {
        return 1;
    }
    return -1;

adjust:
    l1 = *left;
    r1 = *right;
    if (l1 - r1) {
        return (l1 - r1);
    }

bytecopy:
    if (l1 == 0) {
        return 0;
    }
    do {
        l1 = *(++left);
        r1 = *(++right);
        if (l1 - r1) {
            return (l1 - r1);
        }
        if (l1 == 0) {
            return 0;
        }
    } while (1);
    return 0;
}

/** Standard strcat(): appends a string to the end of another and returns the destination. */
char* strcat(char* dst, const char* src) {
    const unsigned char* p = (unsigned char*)src - 1;
    unsigned char* q = (unsigned char*)dst - 1;

    while (*++q)
        ;

    q--;

    while (*++q = *++p)
        ;

    return (dst);
}

/** Standard strncpy(): copies at most n characters, padding with nul bytes if the source is shorter. */
char* strncpy(char* dst, const char* src, size_t n) {
    const unsigned char* p = (const unsigned char*)src - 1;
    unsigned char* q = (unsigned char*)dst - 1;

    n++;

    while (--n)
        if (!(*++q = *++p)) {
            while (--n)
                *++q = 0;
            break;
        }

    return (dst);
}

/**
 * Standard strcpy(): copies the string and terminator,
 * a word at a time when source and destination are equally aligned (stopping at the word holding the
 * terminator), else byte by byte; returns dst.
 */
char* strcpy(char* dst, const char* src) {
    register unsigned char *destb, *fromb;
    register unsigned long w, t, align;

    fromb = (unsigned char*)src;
    destb = (unsigned char*)dst;

    if ((align = ((int)fromb & 3)) != ((int)destb & 3)) {
        goto bytecopy;
    }

    if (align) {
        if ((*destb = *fromb) == 0)
            return (dst);

        for (align = 3 - align; align; align--) {
            if ((*(++destb) = *(++fromb)) == 0)
                return (dst);
        }
        ++destb;
        ++fromb;
    }

    w = *((int*)(fromb));

    t = w + K2;

    t &= K1;
    if (t)
        goto bytecopy;
    --((int*)(destb));

    do {
        *(++((int*)(destb))) = w;
        w = *(++((int*)(fromb)));

        t = w + K2;
        t &= K1;
        if (t)
            goto adjust;
    } while (1);

adjust:
    ++((int*)(destb));

bytecopy:
    if ((*destb = *fromb) == 0)
        return (dst);

    do {
        if ((*(++destb) = *(++fromb)) == 0)
            return (dst);
    } while (1);

    return (dst);
}

/** Standard strlen(): number of characters before the terminator. */
size_t strlen(const char* str) {
    size_t len = -1;
    unsigned char* p = (unsigned char*)str - 1;

    do
        len++;
    while (*++p);

    return (len);
}
