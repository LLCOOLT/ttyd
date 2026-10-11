// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_stage_object.h
// include: system.h
// include: dolphin/mtx.h
// decl: typedef struct ZakoGun { s8 field_0x0; s8 state; s32 timer; s32 timerMax; Vec pos; Vec home; s32 poseBase; s32 poseNum; s32 poseDiv; s32 poseCount; Vec start; Vec target; Vec vel; Vec ofs; Vec rot; } ZakoGun;
// decl: typedef struct ZakoGunWork { s32 flag; s32 targetId; s32 state; s32 timer; Vec pos; u8 field_0x1c[0x34 - 0x1c]; f32 radius; f32 angle; f32 speed; u8 field_0x40[0x48 - 0x40]; Vec start; Vec end; s32 timer2; s32 steps; s32 count; s32 sfx; } ZakoGunWork;
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: extern ZakoGun* zakogun;
// decl: extern ZakoGunWork* work_20_bss_6C;
// decl: ExtPose* extGetPosePtr(void);
// decl: BattleUnit* zakogun_get_ptr(void);
// decl: s32 zakogun_get_kanbu_id(void);
// decl: void zakogun_set_pose(ZakoGun* zako, s32 base, s32 num, s32 div);
// decl: void zakogun_ext_init123_common(ExtPose* pose, s32 i);
// decl: void psndSFXOff(s32 id);
// decl: int rand(void);
// proto: USER_FUNC(zakogun_attack3_1);
USER_FUNC(zakogun_attack3_1) {
    s32 i;
    s32 n;

    if (isFirstCall) {
        Vec pos = {0.0f, 55.0f, 0.0f};
        work_20_bss_6C->pos = pos;
        work_20_bss_6C->radius = 25.0f;
        work_20_bss_6C->angle = 0.0f;
        work_20_bss_6C->count = 0;
        for (i = 0; i < 500; i++) {
            zakogun[i].state = 20;
        }
    }
    for (i = 0, n = 0; i < 500; i++) {
        if (zakogun[i].state == 40) {
            n++;
        }
    }
    return n == 500 ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}
