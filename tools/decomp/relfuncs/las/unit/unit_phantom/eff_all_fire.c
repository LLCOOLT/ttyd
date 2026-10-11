// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_sub.h
// include: driver/effdrv.h
// decl: EffectEntry* effFireEntry(s32 type, f32 x, f32 y, f32 z, f32 scale, s32 lifetime);
// decl: static EffectEntry* eff;
// decl: static EffectEntry* eff2[10];
// decl: static s32 step[10];
// proto: USER_FUNC(eff_all_fire);
USER_FUNC(eff_all_fire) {
    s32* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, args[0]));
    s32 index = evtGetValue(event, args[1]);
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 scales[10] = {1.0f, 1.25f, 1.5f, 1.75f, 2.0f, 2.25f, 2.0f, 1.75f, 1.5f, 1.25f};
    f32* wk;
    f32 x;
    f32 y;
    f32 z;

    if (isFirstCall) {
        eff2[index] = effFireEntry(7, 0.0f, -1000.0f, 0.0f, 1.0f, 120);
        ((f32*)eff2[index]->userdata)[30] = 2.0f;
        ((f32*)eff2[index]->userdata)[31] = unit->mSizeMultiplier * scales[index];
    }
    wk = eff2[index]->userdata;
    if (wk != NULL) {
        BtlUnit_GetPos(unit, &x, &y, &z);
        *(Vec*)&wk[1] = (Vec){x + 24.0f * unit->faceDirection * (index + 1), y - 15.0f - 2.0f * scales[index], z - 10.0f};
    }
    return EVT_RETURN_BLOCK;
}
