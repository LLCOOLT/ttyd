// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_sub.h
// include: driver/effdrv.h
// include: system.h
// include: stdlib.h
// decl: EffectEntry* effVaporN64Entry(s32 type, f32 x, f32 y, f32 z, f32 scale, s32 delay);
// proto: USER_FUNC(eff_poison_barrier);
USER_FUNC(eff_poison_barrier) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 x;
    f32 y;
    f32 z;
    s32 i;

    for (i = 0; i < 3; i++) {
        EffectEntry* eff;
        s32* wk;

        BtlUnit_GetPos(unit, &x, &y, &z);
        x += irand(20) - 10;
        y += irand(30);
        eff = effVaporN64Entry(2, x, y, z, 0.5f + 0.5f * rand() / 32767.0f, (i + 1) * 10);
        wk = eff->userdata;
        wk[6] = 32;
        wk[7] = 115;
        wk[8] = 100;
        wk[9] = 255;
        wk[10] = 32;
        wk[11] = 115;
        wk[12] = 100;
        wk[13] = 255;
        ((f32*)wk)[16] = unit->mSizeMultiplier;
    }
    return EVT_RETURN_DONE;
}
