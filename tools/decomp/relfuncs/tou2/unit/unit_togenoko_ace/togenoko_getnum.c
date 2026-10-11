// include: battle/battle.h
// proto: USER_FUNC(togenoko_getnum);
USER_FUNC(togenoko_getnum) {
    s32* args = event->args;
    s32 num = 0;
    s32 i;

    for (i = 0; i < 64; i++) {
        BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, i);
        if (unit != NULL && unit->currentKind == 0x3C) {
            num++;
        }
    }
    evtSetValue(event, args[0], num);
    return EVT_RETURN_DONE;
}
