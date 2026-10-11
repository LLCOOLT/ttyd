// include: battle/battle.h
// include: battle/battle_unit.h
// proto: USER_FUNC(kamec_get_bunsin);
USER_FUNC(kamec_get_bunsin) {
    s32* args = event->args;
    s32 copies[4];
    s32 n = 0;
    s32 i;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;

    // indices of the magikoopa's copies
    for (i = 0; i < 64; i++) {
        unit = wp->units[i];
        if (unit != NULL && unit->currentKind == 0x32) {
            copies[n] = i;
            n++;
        }
    }
    for (i = 0; i < 4; i++) {
        if (i < n) {
            evtSetValue(event, *args++, copies[i]);
        } else {
            evtSetValue(event, *args++, -1);
        }
    }
    evtSetValue(event, *args, n);
    return EVT_RETURN_DONE;
}
