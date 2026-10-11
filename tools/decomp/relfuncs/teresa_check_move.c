// include: battle/battle.h
// proto: USER_FUNC(teresa_check_move);
USER_FUNC(teresa_check_move) {
    s32* args = event->args;
    s32 num = 0;
    s32 i;

    for (i = 0; i < 64; i++) {
        BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, i);
        if (unit != NULL) {
            if (unit->currentKind == 0x4B && unit->work[0] == 0) {
                num++;
            }
            if (unit->currentKind == 0x6A && unit->work[0] == 0) {
                num++;
            }
        }
    }
    if (num >= 1) {
        evtSetValue(event, args[0], 1);
    } else {
        evtSetValue(event, args[0], 0);
    }
    return EVT_RETURN_DONE;
}
