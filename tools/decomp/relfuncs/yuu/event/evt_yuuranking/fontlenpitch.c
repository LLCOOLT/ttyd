// include: manager/fontmgr.h
// include: driver/msgdrv.h
// decl: const GXColor yuuranking_unused_color = {0xFF, 0xFF, 0xFF, 0xFF};
// proto: s32 fontlenpitch(const char* str, s32 pitch);
s32 fontlenpitch(const char* str, s32 pitch) {
    const s8* p;
    s32 n;

    if (pitch != 0) {
        p = (const s8*)str;
        n = 0;
        while (*p != '\0') {
            if (_ismbblead(*p)) {
                n++;
                p++;
            } else {
                n++;
            }
            p++;
        }
        return n * pitch;
    }
    return FontGetMessageWidth(str);
}
