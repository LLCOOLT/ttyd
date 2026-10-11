// include: battle/battle.h
// include: battle/battle_sub.h
// include: system.h
// proto: USER_FUNC(shadow_scale_small);
USER_FUNC(shadow_scale_small) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BattleUnitPart* part = BtlUnit_GetPartsPtr(unit, 1);

    if (isFirstCall) {
        unit->work[1] = 0;
    }
    {
        f32 start = unit->work[0];
        part->field_0x78 = intplGetValue(0, unit->work[1], 15, start, 0.0f);
    }
    if (unit->work[1] >= 15) {
        return EVT_RETURN_DONE;
    }
    unit->work[1]++;
    return EVT_RETURN_BLOCK;
}
