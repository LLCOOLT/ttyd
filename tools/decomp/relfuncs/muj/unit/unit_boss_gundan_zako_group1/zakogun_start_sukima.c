// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_stage_object.h
// include: system.h
// include: dolphin/mtx.h
// include: driver/dispdrv.h
// decl: typedef struct ZakoGun { s8 field_0x0; s8 state; s32 timer; s32 timerMax; Vec pos; Vec home; s32 poseBase; s32 poseNum; s32 poseDiv; s32 poseCount; Vec start; Vec target; Vec vel; Vec ofs; Vec rot; } ZakoGun;
// decl: typedef struct ZakoGunWork { s32 flag; s32 targetId; s32 state; s32 timer; Vec pos; u8 field_0x1c[0x34 - 0x1c]; f32 radius; f32 angle; f32 speed; u8 field_0x40[0x48 - 0x40]; Vec start; Vec end; s32 timer2; s32 steps; s32 count; s32 sfx; ZakoGun* zako; } ZakoGunWork;
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: extern ZakoGun* zakogun;
// decl: extern ZakoGunWork* work_20_bss_6C;
// decl: ExtPose* extGetPosePtr(void);
// decl: void extLoadRenderMode(void);
// decl: void extLoadVertex(void);
// decl: void extLoadTexture(void);
// decl: void extLoadTev(void);
// decl: void extDraw(void);
// decl: void extLoadTextureExit(void);
// decl: void zakogun_ext_main1(void);
// decl: void zakogun_ext_main2(void);
// decl: void zakogun_ext_main3(void);
// decl: void zakogun_ext_disp(CameraId camera, void* param);
// proto: USER_FUNC(zakogun_start_sukima);
USER_FUNC(zakogun_start_sukima) {
    s32 mode = evtGetValue(event, event->args[0]);
    s32 i;

    for (i = 0; i < 6; i++) {
        ZakoGun* zako = &zakogun[i];
        if (zako->state < 80 || zako->state >= 90) {
            if (mode == 1) {
                zako->state = 96;
                zako->timer = 0;
            } else {
                zako->state = 95;
            }
        }
    }
    return EVT_RETURN_DONE;
}
