// include: battle/battle.h
// include: battle/battle_sub.h
// proto: USER_FUNC(bubble_copy_status);
USER_FUNC(bubble_copy_status) {
    s32* args = event->args;
    s32 id1 = BattleTransID(event, evtGetValue(event, args[0]));
    s32 id2 = BattleTransID(event, evtGetValue(event, args[1]));
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit1 = BattleGetUnitPtr(wp, id1);
    BattleUnit* unit2 = BattleGetUnitPtr(wp, id2);

    unit2->currentHp = unit1->currentHp;
    if (unit2->currentHp > unit2->maxHp) {
        unit2->currentHp = unit2->maxHp;
    }
    unit2->mSizeChangeTurns = unit1->mSizeChangeTurns;
    unit2->mSizeChangeStrength = unit1->mSizeChangeStrength;
    unit2->hpGauge.field_0xC = unit2->currentHp;
    unit2->hpGauge.field_0x10 = unit2->currentHp;
    unit2->hpGauge.field_0x14 = unit2->hpGauge.field_0x18 = (f32)unit2->currentHp / unit2->maxHp;
    return EVT_RETURN_DONE;
}
