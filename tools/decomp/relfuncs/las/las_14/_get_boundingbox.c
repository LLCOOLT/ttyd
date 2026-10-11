// include: driver/hitdrv.h
// include: driver/camdrv.h
// include: dolphin/mtx.h
// proto: static BOOL _get_boundingbox(const char* name, s32* x, s32* y, s32* w, s32* h);
static BOOL _get_boundingbox(const char* name, s32* x, s32* y, s32* w, s32* h) {
    Vec pos;
    Vec screen;
    s32 minX;
    s32 maxX;
    s32 minY;
    s32 maxY;

    hitObjGetPos(name, &pos);
    PSVECAdd(&pos, &((Vec*)v_list)[0], &screen);
    getScreenPoint(&screen, &screen);
    {
        s32 sx = screen.x;
        s32 sy = screen.y;

        minX = sx;
        maxX = sx;
        minY = sy;
        maxY = sy;
    }
    {
        s32 i;

        for (i = 1; i < 8; i++) {
            PSVECAdd(&pos, &((Vec*)v_list)[i], &screen);
            getScreenPoint(&screen, &screen);
            if (screen.x < minX) {
                minX = screen.x;
            }
            if (maxX < screen.x) {
                maxX = screen.x;
            }
            if (screen.y < minY) {
                minY = screen.y;
            }
            if (maxY < screen.y) {
                maxY = screen.y;
            }
        }
    }
    *x = minX + 304;
    *y = minY + 240;
    *w = maxX - minX;
    *h = maxY - minY;
    if (*x < 0) {
        *x = 0;
    }
    if (*y < 0) {
        *y = 0;
    }
    if (*x + *w > 608) {
        *w = 608 - *x;
    }
    if (*y + *h > 480) {
        *h = 480 - *y;
    }
    if (*x < 0) {
        *x = 0;
    }
    if (*y < 0) {
        *y = 0;
    }
    return TRUE;
}
