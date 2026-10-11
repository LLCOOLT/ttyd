// include: battle/battle.h
// include: battle/battle_sub.h
// proto: USER_FUNC(shadow_scale_memory);
USER_FUNC(shadow_scale_memory) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BattleUnitPart* part = BtlUnit_GetPartsPtr(unit, 1);

    unit->work[0] = part->field_0x78;
    return EVT_RETURN_DONE;
}
