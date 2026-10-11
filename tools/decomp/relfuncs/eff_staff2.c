// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_sub.h
// include: driver/effdrv.h
// decl: EffectEntry* effPokopiPchargeN64Entry(s32 type, f32 x, f32 y, f32 z, f32 scale, s32 lifetime);
// proto: USER_FUNC(eff_staff2);
USER_FUNC(eff_staff2) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 x;
    f32 y;
    f32 z;
    f32* wk;

    if (isFirstCall) {
        unit->work[4] = (s32)effPokopiPchargeN64Entry(0, 0.0f, -1000.0f, 0.0f, 1.0f, 60);
    }
    if (!(((EffectEntry*)unit->work[4])->flags & 1)) {
        return EVT_RETURN_DONE;
    }
    wk = ((EffectEntry*)unit->work[4])->userdata;
    wk[13] = unit->mSizeMultiplier;
    BtlUnit_GetPos(unit, &x, &y, &z);
    wk[1] = x + 22.5f * unit->mSizeMultiplier * unit->faceDirection;
    wk[2] = y + 40.0f * unit->mSizeMultiplier;
    wk[3] = 5.0f + z;
    return EVT_RETURN_BLOCK;
}
