#define EOF -1

extern unsigned char __upper_map[];

inline int toupper(int c) {
    return (c == EOF) ? EOF : (int)__upper_map[(unsigned char)c];
}

char* strupr(char* str) {
    char* p;

    for (p = str; *p; p++) {
        *p = toupper(*p);
    }
    return str;
}
