// include: battle/battle.h
// include: string.h
// proto: USER_FUNC(kamec_copy_status);
USER_FUNC(kamec_copy_status) {
    s32* args = event->args;
    s32 id1 = evtGetValue(event, args[0]);
    s32 id2 = evtGetValue(event, args[1]);
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit1 = BattleGetUnitPtr(wp, id1);
    BattleUnit* unit2 = BattleGetUnitPtr(wp, id2);

    // the copy shares the real magikoopa's hp and status
    unit2->currentHp = unit1->currentHp;
    memcpy((u8*)unit2 + 0x118, (u8*)unit1 + 0x118, 0x1E);
    unit2->hpGauge.field_0xC = unit2->currentHp;
    unit2->hpGauge.field_0x10 = unit2->currentHp;
    unit2->hpGauge.field_0x14 = unit2->hpGauge.field_0x18 = (f32)unit2->currentHp / unit2->maxHp;
    return EVT_RETURN_DONE;
}
