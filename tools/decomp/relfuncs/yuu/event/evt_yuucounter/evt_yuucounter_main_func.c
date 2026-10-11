// include: dolphin/os.h
// include: driver/dispdrv.h
// decl: typedef struct YuuCounterWork { EventEntry* event; u16 flags; u32 dispFlags; s32 type; f32 x; f32 y; s32 data; s32 field_0x1C; s64 elapsed; OSTime lastTime; s32 limit; s32 field_0x34; } YuuCounterWork;
// decl: static void* yuunpc_wp;
// decl: static YuuCounterWork* _wp;
// decl: void evt_yuucounter_disp_func(CameraId camera, void* param);
// proto: USER_FUNC(evt_yuucounter_main_func);
USER_FUNC(evt_yuucounter_main_func) {
    YuuCounterWork* wp = (YuuCounterWork*)event->lwData[0];

    if (wp->flags & 1) {
        wp->flags |= 2;
        return EVT_RETURN_DONE;
    }
    dispEntry(CAMERA_2D, 1000.0f, 0, evt_yuucounter_disp_func, wp);
    return EVT_RETURN_BLOCK;
}
