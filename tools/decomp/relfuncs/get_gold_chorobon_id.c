// include: battle/battle.h
// proto: USER_FUNC(get_gold_chorobon_id);
USER_FUNC(get_gold_chorobon_id) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 i;

    for (i = 0; i < 64; i++) {
        BattleUnit* unit = BattleGetUnitPtr(wp, i);
        if (unit != NULL && unit->initialKind == 0x14) {
            break;
        }
    }
    if (i != 64) {
        evtSetValue(event, args[0], i);
    } else {
        evtSetValue(event, args[0], -1);
    }
    return EVT_RETURN_DONE;
}
