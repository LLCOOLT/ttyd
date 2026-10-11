// include: battle/battle.h
// proto: USER_FUNC(check_exist_kenkyu);
USER_FUNC(check_exist_kenkyu) {
    s32 i;
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 id = -1;

    for (i = 0; i < 64; i++) {
        BattleUnit* unit = BattleGetUnitPtr(wp, i);
        if (unit != NULL && unit->initialKind == 0x77) {
            id = i;
        }
    }
    evtSetValue(event, args[0], id);
    return EVT_RETURN_DONE;
}
