// include: battle/battle.h
// include: battle/battle_unit.h
// decl: BOOL BtlUnit_CanActStatus(BattleUnit* unit);
// proto: USER_FUNC(piders_get_first_pos_attr);
USER_FUNC(piders_get_first_pos_attr) {
    s32 i;
    s32* args = event->args;
    s32 attr;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;

    // find the first living pider
    for (i = 0; i < 64; i++) {
        unit = wp->units[i];
        if (unit != NULL && (unit->currentKind == 0x1B || unit->currentKind == 0xA4) && !BtlUnit_CheckStatus(unit, 0x1B)) {
            break;
        }
    }
    attr = unit->work[0];
    if (BtlUnit_CanActStatus(unit)) {
        if (attr == 0) {
            attr = 1;
        } else {
            attr = 0;
        }
    }
    evtSetValue(event, args[0], attr);
    return EVT_RETURN_DONE;
}
