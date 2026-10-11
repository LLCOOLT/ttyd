// include: manager/evtmgr_cmd.h
// include: driver/dispdrv.h
// decl: typedef struct FirebarBall { s32 pose; Vec pos; } FirebarBall;
// decl: typedef struct FirebarSetup { u8 type; u8 count; u8 field_0x2[2]; Vec pos; f32 spacing; f32 field_0x14; f32 speed; void* callback; f32 field_0x20; f32 radius; } FirebarSetup;
// decl: typedef struct FirebarWork { u8 type; u8 count; u16 flags; Vec pos; f32 prevAngle; f32 angle; f32 speed; f32 spacing; f32 field_0x20; f32 scale; f32 field_0x28; f32 radius; void (*callback)(struct FirebarWork* wp, s32 type); s32 hitCount; s32 sfxId; s32 state; f32 shadowAngle; FirebarBall* balls; FirebarSetup* setup; } FirebarWork;
// decl: double sin(double x);
// decl: void shadowEntryMode(s32 mode, f32 x, f32 y, f32 z, f32 scale);
// decl: void shadowSetVolumeDecay(f32 a, f32 b, f32 c);
// decl: void firebar_disp(CameraId camera, void* param);
// proto: USER_FUNC(firebar_disp_evt);
USER_FUNC(firebar_disp_evt) {
    FirebarWork* wp;
    FirebarBall* ball;
    f32 a;
    s32 i;

    if (evtCheckID(event->lwData[0])) {
        wp = (FirebarWork*)evtGetPtrID(event->lwData[0])->userdata[0];
        a = sin(6.2831855f * wp->shadowAngle / 360.0f);
        a = 0.375f * a + 0.625f;
        ball = wp->balls;
        for (i = 0; i < wp->count; i++, ball++) {
            shadowEntryMode(2, ball->pos.x, ball->pos.y, ball->pos.z, 17.0f * wp->scale);
            shadowSetVolumeDecay(a, 0.2f * a, 0.4f * a);
        }
        dispEntry(CAMERA_3D, dispCalcZ(&wp->pos), 1, firebar_disp, wp);
        return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_DONE;
}
