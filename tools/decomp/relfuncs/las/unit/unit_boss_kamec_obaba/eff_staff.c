// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_sub.h
// include: driver/effdrv.h
// decl: EffectEntry* effThunderflareN64Entry(s32 type, f32 x, f32 y, f32 z, f32 scale, s32 lifetime);
// proto: USER_FUNC(eff_staff);
USER_FUNC(eff_staff) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 x;
    f32 y;
    f32 z;
    f32* wk;

    if (isFirstCall) {
        unit->work[3] = (s32)effThunderflareN64Entry(0, 0.0f, -1000.0f, 0.0f, 1.0f, 60);
    }
    if (!(((EffectEntry*)unit->work[3])->flags & 1)) {
        return EVT_RETURN_DONE;
    }
    wk = ((EffectEntry*)unit->work[3])->userdata;
    wk[10] = unit->mSizeMultiplier;
    BtlUnit_GetPos(unit, &x, &y, &z);
    wk[2] = x + 30.0f * unit->mSizeMultiplier * unit->faceDirection;
    wk[3] = y + 35.0f * unit->mSizeMultiplier;
    wk[4] = 5.0f + z;
    return EVT_RETURN_BLOCK;
}
