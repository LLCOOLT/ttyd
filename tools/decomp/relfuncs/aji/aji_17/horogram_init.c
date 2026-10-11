// include: manager/evtmgr_cmd.h
// include: memory.h
// include: dolphin/gx.h
// decl: typedef struct HorogramWork { void* buf0; void* buf1; GXTexObj tex0; GXTexObj tex1; u16 ready; u16 flags; } HorogramWork;
// decl: HorogramWork* horogram_wp;
// proto: USER_FUNC(horogram_init);
USER_FUNC(horogram_init) {
    u32 size = GXGetTexBufferSize(0x260, 0x1E0, GX_TF_RGBA8, GX_FALSE, 0);

    horogram_wp = _mapAlloc(sizeof(HorogramWork));
    horogram_wp->buf0 = _mapAlloc(size);
    horogram_wp->buf1 = _mapAlloc(GXGetTexBufferSize(0x260, 0x1E0, GX_TF_Z8, GX_FALSE, 0));
    horogram_wp->ready = 0;
    horogram_wp->flags = 0;
    return EVT_RETURN_DONE;
}
