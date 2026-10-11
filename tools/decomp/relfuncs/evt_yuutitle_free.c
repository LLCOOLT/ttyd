// include: memory.h
// decl: typedef struct YuuTitleWork { EventEntry* event; u16 flags; f32 x; f32 y; f32 startX; f32 startY; f32 targetX; f32 targetY; s32 alpha; const char* msg; } YuuTitleWork;
// decl: static YuuTitleWork* _wp;
// proto: USER_FUNC(evt_yuutitle_free);
USER_FUNC(evt_yuutitle_free) {
    YuuTitleWork* wp = _wp;

    if (wp == NULL) {
        return EVT_RETURN_DONE;
    }
    if (isFirstCall) {
        wp->flags |= 1;
    }
    if (!(wp->flags & 2)) {
        return EVT_RETURN_BLOCK;
    }
    _mapFree(_wp);
    _wp = NULL;
    return EVT_RETURN_DONE;
}
