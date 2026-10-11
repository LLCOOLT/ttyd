// include: battle/battle.h
// proto: USER_FUNC(get_attacker);
USER_FUNC(get_attacker) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    BattleUnit* unit = BattleGetUnitPtr(wp, wp->activeUnitId);

    if (unit->initialKind == 0xDE) {
        evtSetValue(event, args[0], 0);
    } else if (unit->initialKind == 0xE0) {
        evtSetValue(event, args[0], 1);
    } else {
        evtSetValue(event, args[0], 2);
    }
    return EVT_RETURN_DONE;
}
