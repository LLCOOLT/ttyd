// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_sub.h
// proto: USER_FUNC(_wait_damage_event_end);
USER_FUNC(_wait_damage_event_end) {
    BattleWork* wp = _battleWorkPointer;
    s32 id;
    BattleUnit* unit;

    id = evtGetValue(event, event->args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    if (unit == NULL) {
        return EVT_RETURN_DONE;
    }
    if (unit->damageEventId != 0 && evtCheckID(unit->damageEventId)) {
        return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_DONE;
}
