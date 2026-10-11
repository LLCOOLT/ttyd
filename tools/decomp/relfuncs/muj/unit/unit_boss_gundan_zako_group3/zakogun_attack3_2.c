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
// proto: USER_FUNC(zakogun_attack3_2);
USER_FUNC(zakogun_attack3_2) {
    BattleUnit* unit = zakogun_get_ptr();
    s32 sfx = evtGetValue(event, event->args[0]);

    if (isFirstCall) {
        work_20_bss_6C->count = 0;
        work_20_bss_6C->state = 0;
    }
    switch (work_20_bss_6C->state) {
        case 0:
            work_20_bss_6C->state = 5;
            work_20_bss_6C->speed = 0.0f;
        case 5:
            work_20_bss_6C->pos.x += work_20_bss_6C->speed;
            work_20_bss_6C->angle -= work_20_bss_6C->speed;
            work_20_bss_6C->speed -= 0.06f;
            if (work_20_bss_6C->targetId != -1) {
                BattleUnit* target = BattleGetUnitPtr(_battleWorkPointer, work_20_bss_6C->targetId);
                if (work_20_bss_6C->pos.x <= target->mPosition.x) {
                    unit->work[0] = 1;
                }
            }
            if (work_20_bss_6C->pos.x <= -200.0f) {
                work_20_bss_6C->state = 8;
            }
            break;
        case 8:
            work_20_bss_6C->pos.x += work_20_bss_6C->speed;
            work_20_bss_6C->angle -= work_20_bss_6C->speed;
            work_20_bss_6C->speed += 5.0f;
            if (work_20_bss_6C->speed >= 0.0f) {
                work_20_bss_6C->state = 10;
            }
            break;
        case 10:
            work_20_bss_6C->pos.x += work_20_bss_6C->speed;
            work_20_bss_6C->angle -= work_20_bss_6C->speed;
            work_20_bss_6C->speed += 0.06f;
            if (work_20_bss_6C->pos.x >= -30.0f) {
                work_20_bss_6C->state = 13;
            }
            break;
        case 13:
            work_20_bss_6C->pos.x += work_20_bss_6C->speed;
            work_20_bss_6C->angle -= work_20_bss_6C->speed;
            work_20_bss_6C->speed -= 1.0f;
            if (work_20_bss_6C->speed <= 0.0f) {
                work_20_bss_6C->state = 15;
                psndSFXOff(sfx);
                work_20_bss_6C->timer = 20;
            }
            break;
        case 15:
            work_20_bss_6C->timer--;
            if (work_20_bss_6C->timer < 0) {
                return EVT_RETURN_DONE;
            }
            break;
    }
    return EVT_RETURN_BLOCK;
}
