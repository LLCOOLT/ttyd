// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_sub.h
// proto: static USER_FUNC(hand_end);
static USER_FUNC(hand_end) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id = evtGetValue(event, *args++);
    BattleUnit* unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    s32 i;
    s32 j;

    for (i = 2, j = 0; i <= 5; i++, j++) {
        if ((void*)unit->work[j] != NULL) {
            BattleFree((void*)unit->work[j]);
            unit->work[j] = 0;
        }
    }
    return EVT_RETURN_DONE;
}
