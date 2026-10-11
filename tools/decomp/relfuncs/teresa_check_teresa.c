// include: battle/battle.h
// proto: USER_FUNC(teresa_check_teresa);
USER_FUNC(teresa_check_teresa) {
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 result = 0;
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);

    if (unit == NULL) {
        evtSetValue(event, args[1], 0);
        return EVT_RETURN_DONE;
    }
    if (unit->currentKind == 0x4B) {
        result = 1;
    }
    if (unit->currentKind == 0x6A) {
        result = 1;
    }
    evtSetValue(event, args[1], result);
    return EVT_RETURN_DONE;
}
