// include: driver/camdrv.h
// include: dolphin/gx.h
// decl: typedef struct ScreenWork { void* buf; s32 ready; f32 scale; f32 scaleTarget; f32 x; f32 xTarget; f32 y; f32 yTarget; s32 count; s32 mode; f32 field_0x28; u8* noise; } ScreenWork;
// decl: static ScreenWork* screen_wp;
// proto: static void screen_capture(CameraId cameraId, void* param);
static void screen_capture(CameraId cameraId, void* param) {
    GXSetTexCopySrc(0, 0, 0x260, 0x1E0);
    GXSetTexCopyDst(0x130, 0xF0, GX_TF_RGB565, GX_TRUE);
    GXCopyTex(screen_wp->buf, GX_FALSE);
    GXPixModeSync();
    screen_wp->ready = 1;
}
