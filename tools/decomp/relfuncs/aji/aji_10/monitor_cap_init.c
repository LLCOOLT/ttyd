// include: manager/evtmgr_cmd.h
// include: memory.h
// include: dolphin/gx.h
// decl: typedef struct MonitorWork { void* buf; s32 ready; s32 kanbu; } MonitorWork;
// decl: static MonitorWork* monitor_wp;
// proto: USER_FUNC(monitor_cap_init);
USER_FUNC(monitor_cap_init) {
    u32 size = GXGetTexBufferSize(0x260, 0x1E0, GX_TF_I4, GX_FALSE, 0);

    monitor_wp = _mapAlloc(sizeof(MonitorWork));
    monitor_wp->buf = _mapAlloc(size);
    monitor_wp->ready = 0;
    monitor_wp->kanbu = 0;
    return EVT_RETURN_DONE;
}
