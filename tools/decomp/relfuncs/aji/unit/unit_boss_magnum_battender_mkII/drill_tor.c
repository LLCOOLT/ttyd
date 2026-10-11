// include: manager/evtmgr_cmd.h
// include: battle/battle.h
// include: battle/battle_unit.h
// include: driver/effdrv.h
// decl: typedef struct BattenEffWork { s32 field_0x0; Vec pos; u8 field_0x10[0x28 - 0x10]; Mtx mtx; } BattenEffWork;
// decl: EffectEntry* effKamekiTornadeN64Entry(s32 type, s32 time, f32 x, f32 y, f32 z, f32 scale);
// decl: s32 torCount;
// decl: EffectEntry* eff_tor;
// proto: USER_FUNC(drill_tor);
USER_FUNC(drill_tor) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 x;
    f32 y;
    f32 z;

    BtlUnit_GetPos(unit, &x, &y, &z);
    if (isFirstCall) {
        eff_tor = effKamekiTornadeN64Entry(0, 1000, 0.0f, -1000.0f, 0.0f, 3.5f);
        torCount = 0;
    }
    if (y <= 300.0f) {
        ((BattenEffWork*)eff_tor->userdata)->pos.x = x;
        ((BattenEffWork*)eff_tor->userdata)->pos.y = y - 240.0f;
        ((BattenEffWork*)eff_tor->userdata)->pos.z = z;
    }
    if (++torCount >= 70) {
        effDelete(eff_tor);
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}
