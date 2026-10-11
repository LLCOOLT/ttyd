// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_sub.h
// include: driver/effdrv.h
// decl: EffectEntry* effFireEntry(s32 type, f32 x, f32 y, f32 z, f32 scale, s32 lifetime);
// proto: USER_FUNC(eff_fire);
USER_FUNC(eff_fire) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BattleUnitPart* part = BtlUnit_GetPartsPtr(unit, 2);
    f32* wk;
    f32 x;
    f32 y;
    f32 z;

    if (isFirstCall) {
        eff = effFireEntry(6, 0.0f, -1000.0f, 0.0f, 1.0f, 106);
        ((f32*)eff->userdata)[30] = 0.0f;
        ((f32*)eff->userdata)[31] = 0.0f;
    }
    wk = eff->userdata;
    if (wk != NULL) {
        BtlUnit_GetPartsPos(part, &x, &y, &z);
        *(Vec*)&wk[1] = (Vec){x, y, z};
        wk[30] += 0.1f * unit->mSizeMultiplier;
        if (wk[30] >= unit->mSizeMultiplier) {
            wk[30] = unit->mSizeMultiplier;
        }
        wk[31] += 0.1f * unit->mSizeMultiplier;
        if (wk[31] >= unit->mSizeMultiplier) {
            wk[31] = unit->mSizeMultiplier;
        }
    }
    return EVT_RETURN_BLOCK;
}
