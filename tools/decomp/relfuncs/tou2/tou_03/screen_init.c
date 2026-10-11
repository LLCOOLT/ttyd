// include: manager/evtmgr_cmd.h
// include: memory.h
// include: dolphin/gx.h
// decl: typedef struct ScreenWork { void* buf; s32 ready; f32 scale; f32 scaleTarget; f32 x; f32 xTarget; f32 y; f32 yTarget; s32 count; s32 mode; f32 field_0x28; u8* noise; } ScreenWork;
// decl: static ScreenWork* screen_wp;
// proto: USER_FUNC(screen_init);
USER_FUNC(screen_init) {
    u32 size = GXGetTexBufferSize(0x260, 0x1E0, GX_TF_I4, GX_FALSE, 0);

    screen_wp = _mapAlloc(sizeof(ScreenWork));
    screen_wp->buf = _mapAlloc(size);
    screen_wp->ready = 0;
    screen_wp->scale = screen_wp->scaleTarget = 1.0f;
    screen_wp->x = screen_wp->xTarget = 0.0f;
    screen_wp->y = screen_wp->yTarget = 0.0f;
    screen_wp->count = 0;
    screen_wp->field_0x28 = -1.0f;
    screen_wp->noise = _mapAlloc(GXGetTexBufferSize(64, 64, GX_TF_I8, GX_FALSE, 0));
    if (evtGetValue(event, GSW(0)) == 163) {
        screen_wp->mode = 1;
    }
    return EVT_RETURN_DONE;
}
