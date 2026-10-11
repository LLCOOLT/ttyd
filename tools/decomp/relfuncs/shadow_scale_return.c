// include: battle/battle.h
// include: battle/battle_sub.h
// decl: f32 intplGetValue(f32 start, f32 end, s32 mode, s32 currStep, s32 steps);
// proto: USER_FUNC(shadow_scale_return);
USER_FUNC(shadow_scale_return) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BattleUnitPart* part = BtlUnit_GetPartsPtr(unit, 1);

    if (isFirstCall) {
        unit->work[1] = 0;
    }
    part->field_0x78 = intplGetValue(0.0f, unit->work[0], 0, unit->work[1], 15);
    if (unit->work[1] >= 15) {
        return EVT_RETURN_DONE;
    }
    unit->work[1]++;
    return EVT_RETURN_BLOCK;
}
