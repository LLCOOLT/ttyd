// include: battle/battle.h
// include: battle/battle_unit.h
// proto: USER_FUNC(kamec_get_live_num);
USER_FUNC(kamec_get_live_num) {
    s32 i;
    s32* args = event->args;
    s32 num = 0;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;

    for (i = 0; i < 64; i++) {
        unit = wp->units[i];
        if (unit != NULL && unit->mAlliance == 1 && !BtlUnit_CheckStatus(unit, 0x1B)) {
            num++;
        }
    }
    evtSetValue(event, args[0], num);
    return EVT_RETURN_DONE;
}
