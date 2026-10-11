// include: driver/offscreendrv.h
// proto: static s32 _ofs_get_boundingbox(const char* name, s32* x, s32* y, s32* w, s32* h);
static s32 _ofs_get_boundingbox(const char* name, s32* x, s32* y, s32* w, s32* h) {
    u16 left;
    u16 top;
    u16 right;
    u16 bottom;

    if (!offscreenGetBoundingBox_BeforeFrame(offscreenNameToId(name), &left, &top, &right, &bottom)) {
        return 0;
    }
    *x = left;
    *y = top;
    *w = right - left + 50;
    *h = bottom - top;
    if (*x + *w >= 608) {
        *w = 608 - *x;
    }
    return 2;
}
