// include: battle/battle.h
// proto: USER_FUNC(get_id);
USER_FUNC(get_id) {
    s32* args = event->args;
    s32 i;
    s32 id1;
    s32 id2;

    for (i = 0; i < 64; i++) {
        BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, i);
        if (unit != NULL) {
            if (unit->currentKind == 0x3D) {
                id1 = i;
            }
            if (unit->currentKind == 0x3E) {
                id2 = i;
            }
        }
    }
    evtSetValue(event, args[0], id1);
    evtSetValue(event, args[1], id2);
    return EVT_RETURN_DONE;
}
