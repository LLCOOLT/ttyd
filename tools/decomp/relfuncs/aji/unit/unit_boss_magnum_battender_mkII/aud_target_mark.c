// include: manager/evtmgr_cmd.h
// include: battle/battle.h
// include: battle/battle_unit.h
// include: driver/effdrv.h
// decl: typedef struct BattenEffWork { s32 field_0x0; Vec pos; u8 field_0x10[0x28 - 0x10]; Mtx mtx; } BattenEffWork;
// decl: typedef struct TargetWork { s32 state; s32 count; EffectEntry* eff; } TargetWork;
// decl: f32 intplGetValue(f32 start, f32 end, s32 mode, s32 cur, s32 steps);
// decl: EffectEntry* effBattenEntry(s32 type, s32 time, f32 x, f32 y, f32 z, f32 scale);
// decl: s32 psndSFXOn(const char* name);
// decl: void psndSFXOff(s32 id);
// decl: s32 targetSoundId;
// decl: TargetWork* wp_target;
// proto: USER_FUNC(aud_target_mark);
USER_FUNC(aud_target_mark) {
    s32* args = event->args;
    f32 x = evtGetValue(event, args[0]);
    f32 y = evtGetValue(event, args[1]);
    f32 z = evtGetValue(event, args[2]);
    BattenEffWork* ew;

    if (isFirstCall) {
        wp_target = BattleAlloc(sizeof(TargetWork));
        wp_target->eff = effBattenEntry(1, 1000, 0.0f, -1000.0f, 0.0f, 1.0f);
        wp_target->state = 0;
        wp_target->count = 0;
        targetSoundId = psndSFXOn("SFX_BOSS_MBTN_SEARCH1");
    }
    ew = wp_target->eff->userdata;
    switch (wp_target->state) {
        case 0:
            wp_target->count++;
            ew->pos.x = intplGetValue(60.0f + x, x - 5.0f, 4, wp_target->count, 60);
            ew->pos.y = intplGetValue(20.0f + y, 60.0f + y, 4, wp_target->count, 60);
            ew->pos.z = 20.0f + z;
            if (wp_target->count >= 60) {
                wp_target->state = 5;
                wp_target->count = 0;
            }
            break;
        case 5:
            wp_target->count++;
            ew->pos.x = intplGetValue(x - 5.0f, x - 25.0f, 4, wp_target->count, 40);
            ew->pos.y = intplGetValue(60.0f + y, 20.0f + y, 4, wp_target->count, 40);
            ew->pos.z = 20.0f + z;
            if (wp_target->count >= 40) {
                wp_target->state = 10;
                wp_target->count = 0;
            }
            break;
        case 10:
            wp_target->count++;
            ew->pos.x = intplGetValue(x - 25.0f, x, 4, wp_target->count, 20);
            ew->pos.y = intplGetValue(20.0f + y, y, 4, wp_target->count, 20);
            ew->pos.z = 20.0f + z;
            if (wp_target->count >= 20) {
                wp_target->state = 15;
                wp_target->count = 0;
                effDelete(wp_target->eff);
                wp_target->eff = effBattenEntry(2, 1000, x, y, 10.0f + z, 1.0f);
                psndSFXOff(targetSoundId);
                psndSFXOn("SFX_BOSS_MBTN_LOCKON1");
            }
            break;
        case 15:
            wp_target->count++;
            if (wp_target->count >= 90) {
                effDelete(wp_target->eff);
                BattleFree(wp_target);
                return EVT_RETURN_DONE;
            }
            break;
    }
    return EVT_RETURN_BLOCK;
}
