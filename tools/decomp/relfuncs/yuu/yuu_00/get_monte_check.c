// include: dolphin/mtx.h
// proto: static BOOL get_monte_check(Vec* a, Vec* b);
static BOOL get_monte_check(Vec* a, Vec* b) {
    if (PSVECDistance(a, b) < 20.0f && __fabs(a->y - b->y) < 20.0) {
        return TRUE;
    }
    return FALSE;
}
