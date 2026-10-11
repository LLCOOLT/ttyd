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
// decl: s32 psndSFXOn(const char* name);
// decl: void psndSFXOff(s32 id);
// proto: USER_FUNC(down_ceil_20_text_9C8C);
USER_FUNC(down_ceil_20_text_9C8C) {
    u8* ceil = &_battleWorkPointer->field_180DC;
    BattleStageObject* body = BattleSearchObjectPtr("if_body");
    BattleStageObject* wire = BattleSearchObjectPtr("if_wire");

    if (isFirstCall) {
        work_20_bss_6C->start = (Vec){0.0f, 250.0f, 0.0f};
        work_20_bss_6C->end = (Vec){0.0f, 130.0f, 0.0f};
        work_20_bss_6C->timer = 120;
        work_20_bss_6C->steps = 120;
        *ceil &= ~0x20;
        work_20_bss_6C->sfx = work_20_bss_6C->sfx = psndSFXOn("SFX_BOSS_TEAM_3RD_MOVE_CAILING1");
    }
    body->mPosition.y = wire->mPosition.y = intplGetValue(work_20_bss_6C->start.y, work_20_bss_6C->end.y, 4, work_20_bss_6C->steps - work_20_bss_6C->timer, work_20_bss_6C->steps);
    work_20_bss_6C->timer--;
    if (work_20_bss_6C->timer < 0) {
        psndSFXOff(work_20_bss_6C->sfx);
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}
