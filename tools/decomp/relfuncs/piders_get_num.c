// include: battle/battle.h
// include: battle/battle_unit.h
// proto: USER_FUNC(piders_get_num);
USER_FUNC(piders_get_num) {
    BattleUnit* unit;
    s32 i;
    s32* args = event->args;
    s32 num = 0;
    BattleWork* wp = _battleWorkPointer;

    for (i = 0; i < 64; i++) {
        unit = wp->units[i];
        if (unit != NULL && (unit->currentKind == 0x1B || unit->currentKind == 0xA4) && !BtlUnit_CheckStatus(unit, 0x1B)) {
            num++;
        }
    }
    evtSetValue(event, args[0], num);
    return EVT_RETURN_DONE;
}
