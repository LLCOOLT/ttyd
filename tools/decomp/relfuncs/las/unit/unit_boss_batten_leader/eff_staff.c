// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_sub.h
// include: driver/effdrv.h
// include: eff/eff_syuryou.h
// proto: USER_FUNC(eff_staff);
USER_FUNC(eff_staff) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 x;
    f32 y;
    f32 z;
    f32* wk;

    wk = effSyuryouEntry(0, 90, 0.0f, -1000.0f, 0.0f)->userdata;
    BtlUnit_GetPos(unit, &x, &y, &z);
    wk[1] = x + 6.0f * (unit->mSizeMultiplier * unit->faceDirection);
    wk[2] = y + 68.0f * unit->mSizeMultiplier;
    wk[3] = 5.0f + z;
    wk[4] = unit->mSizeMultiplier;
    return EVT_RETURN_DONE;
}
