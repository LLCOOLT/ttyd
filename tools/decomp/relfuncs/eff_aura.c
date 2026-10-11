// include: eff/eff_uranoko.h
// include: battle/battle_sub.h
// include: battle/battle.h
// proto: USER_FUNC(eff_aura);
USER_FUNC(eff_aura) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    EffectEntry* eff;
    EffUranokoWork* work;
    f32 x, y, z;

    if (isFirstCall) {
        unit->work[2] = (s32)effUranokoEntry(0, 120, 0.0f, -1000.0f, 0.0f);
    }
    BtlUnit_GetPos(unit, &x, &y, &z);
    eff = (EffectEntry*)unit->work[2];
    if (!(eff->flags & 1)) {
        return EVT_RETURN_DONE;
    }
    work = eff->userdata;
    work->position.x = x;
    work->position.y = y;
    work->position.z = z;
    work->baseScale = unit->mSizeMultiplier;
    return EVT_RETURN_BLOCK;
}
