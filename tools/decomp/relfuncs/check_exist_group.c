// include: battle/battle.h
// proto: USER_FUNC(check_exist_group);
USER_FUNC(check_exist_group) {
    s32 i;
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 id = -1;

    for (i = 0; i < 64; i++) {
        BattleUnit* unit = BattleGetUnitPtr(wp, i);
        if (unit != NULL && (unit->initialKind == 0x64 || unit->initialKind == 0x65 || unit->initialKind == 0x66)) {
            id = i;
        }
    }
    evtSetValue(event, args[0], id);
    return EVT_RETURN_DONE;
}
