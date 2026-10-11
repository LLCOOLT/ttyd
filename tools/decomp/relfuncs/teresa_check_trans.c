// include: battle/battle.h
// include: battle/battle_sub.h
// proto: USER_FUNC(teresa_check_trans);
USER_FUNC(teresa_check_trans) {
    s32* args = event->args;
    s32 num = 0;
    s32 id = evtGetValue(event, args[0]);
    s32 self;
    s32 i;

    self = BattleTransID(event, id);

    for (i = 0; i < 64; i++) {
        BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, i);
        if (unit != NULL) {
            if (unit->currentKind == 0x4B && !BtlUnit_CheckStatus(unit, 0x12) && i != self) {
                num++;
            }
            if (unit->currentKind == 0x6A && !BtlUnit_CheckStatus(unit, 0x12) && i != self) {
                num++;
            }
        }
    }
    if (num >= 1) {
        evtSetValue(event, args[1], 1);
    } else {
        evtSetValue(event, args[1], 0);
    }
    return EVT_RETURN_DONE;
}
