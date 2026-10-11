// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_sub.h
// proto: USER_FUNC(unk_las_0000d538);
USER_FUNC(unk_las_0000d538) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id = evtGetValue(event, *args++);
    BattleUnit* unit;

    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    if (unit != NULL) {
        unit->hpGauge.field_0x2 |= 1;
    }
    return EVT_RETURN_DONE;
}
