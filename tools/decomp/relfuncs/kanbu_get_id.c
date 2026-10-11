// include: battle/battle.h
// proto: USER_FUNC(kanbu_get_id);
USER_FUNC(kanbu_get_id) {
    s32* args = event->args;
    s32 id = -1;
    s32 i;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;

    for (i = 0; i < 64; i++) {
        unit = BattleGetUnitPtr(wp, i);
        if (unit != NULL && unit->initialKind == 99) {
            id = i;
            break;
        }
    }
    evtSetValue(event, args[0], id);
    if (id != -1) {
        evtSetValue(event, args[1], BtlUnit_GetBodyPartsId(unit));
    } else {
        evtSetValue(event, args[1], 0);
    }
    return EVT_RETURN_DONE;
}
