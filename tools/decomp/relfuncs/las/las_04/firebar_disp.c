// include: driver/camdrv.h
// include: driver/animdrv.h
// include: dolphin/mtx.h
// decl: typedef struct FirebarBall { s32 pose; Vec pos; } FirebarBall;
// decl: typedef struct FirebarSetup { u8 type; u8 count; u8 field_0x2[2]; Vec pos; f32 spacing; f32 field_0x14; f32 speed; void* callback; f32 field_0x20; f32 radius; } FirebarSetup;
// decl: typedef struct FirebarWork { u8 type; u8 count; u16 flags; Vec pos; f32 prevAngle; f32 angle; f32 speed; f32 spacing; f32 field_0x20; f32 scale; f32 field_0x28; f32 radius; void (*callback)(struct FirebarWork* wp, s32 type); s32 hitCount; s32 sfxId; s32 state; f32 shadowAngle; FirebarBall* balls; FirebarSetup* setup; } FirebarWork;
// proto: void firebar_disp(CameraId camera, void* param);
void firebar_disp(CameraId camera, void* param) {
    FirebarWork* wp = param;
    FirebarBall* ball = wp->balls;
    Mtx mtx;
    s32 i;

    for (i = 0; i < wp->count; i++, ball++) {
        PSMTXTrans(mtx, ball->pos.x, ball->pos.y, ball->pos.z);
        animPoseDrawMtx(ball->pose, mtx, 1, 0.0f, 2.0f * wp->scale);
        animPoseDrawMtx(ball->pose, mtx, 2, 0.0f, 2.0f * wp->scale);
        animPoseDrawMtx(ball->pose, mtx, 3, 0.0f, 2.0f * wp->scale);
    }
}
