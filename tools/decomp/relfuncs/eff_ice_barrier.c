// include: battle/battle.h
// include: battle/battle_sub.h
// include: driver/effdrv.h
// proto: USER_FUNC(eff_ice_barrier);
EffectEntry* effKumokumoN64Entry(s32 type, f32 x, f32 y, f32 z, f32 arg4, f32 arg5, f32 arg6, s32 arg7);

USER_FUNC(eff_ice_barrier) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    EffectEntry* eff;
    f32 x, y, z;

    if (isFirstCall && unit->work[1] == 0) {
        unit->work[1] = (s32)effKumokumoN64Entry(3, 0.0f, -1000.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1000);
    }
    eff = (EffectEntry*)unit->work[1];
    BtlUnit_GetPos(unit, &x, &y, &z);
    ((f32*)eff->userdata)[1] = x;
    ((f32*)eff->userdata)[2] = 10.0f * unit->mSizeMultiplier + y;
    ((f32*)eff->userdata)[3] = z;
    ((f32*)eff->userdata)[23] = unit->mSizeMultiplier;
    return EVT_RETURN_DONE;
}
