// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_stage_object.h
// decl: f32 intplGetValue(f32 start, f32 end, s32 mode, s32 cur, s32 steps);
// decl: s32 irand(s32 scalar);
// decl: typedef struct ZakoGun { s8 field_0x0; s8 state; s32 timer; s32 timerMax; Vec pos; Vec home; s32 poseBase; s32 poseNum; s32 poseDiv; s32 poseCount; Vec start; Vec target; Vec vel; u8 field_0x58[0x64 - 0x58]; Vec rot; } ZakoGun;
// decl: typedef struct ZakoGunWork { s32 flag; s32 targetId; u8 field_0x8[0x48 - 0x8]; Vec start; Vec end; s32 timer; s32 steps; s32 count; s32 sfx; } ZakoGunWork;
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: extern ZakoGun* zakogun;
// decl: extern ZakoGunWork* work_20_bss_6C;
// proto: USER_FUNC(zakogun_attack2_yusuri);
USER_FUNC(zakogun_attack2_yusuri) {
    s32 i;
    s32 n;

    if (isFirstCall) {
        for (i = 0; i < 25; i++) {
            zakogun[i].state = 60;
        }
    }
    i = 0;
    n = 0;
    for (; i < 25; i++) {
        if (zakogun[i].state == 10) {
            n++;
        }
    }
    return n == 25 ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}
