// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_sub.h
// proto: USER_FUNC(piders_get_zyun);
USER_FUNC(piders_get_zyun) {
    s32 id;
    s32 i;
    s32* args = event->args;
    s32 order = 0;
    BattleWork* wp;
    BattleUnit* unit;

    id = evtGetValue(event, args[0]);
    wp = _battleWorkPointer;
    id = BattleTransID(event, id);
    for (i = 0; i < 64; i++) {
        unit = wp->units[i];
        if (unit != NULL && (unit->currentKind == 0x1B || unit->currentKind == 0xA4)) {
            if (!BtlUnit_CheckStatus(unit, 0x1B)) {
                order++;
            }
            if (unit->unitId == id) {
                break;
            }
        }
    }
    evtSetValue(event, args[1], order);
    return EVT_RETURN_DONE;
}
