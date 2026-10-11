// include: dolphin/os.h
// include: memory.h
// decl: typedef struct YuuCounterWork { EventEntry* event; u16 flags; u32 dispFlags; s32 type; f32 x; f32 y; s32 data; s32 field_0x1C; s64 elapsed; OSTime lastTime; s32 limit; s32 field_0x34; } YuuCounterWork;
// decl: static void* yuunpc_wp;
// decl: static YuuCounterWork* _wp;
// proto: USER_FUNC(evt_yuucounter_free);
USER_FUNC(evt_yuucounter_free) {
    YuuCounterWork* wp = _wp;

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
