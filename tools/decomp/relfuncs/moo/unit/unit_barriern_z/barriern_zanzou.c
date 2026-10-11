// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_sub.h
// decl: static s32 barriern_zanzou_sub(BOOL isFirstCall, BattleUnit* unit, f32* scales, s32 type);
// proto: static USER_FUNC(barriern_zanzou);
static USER_FUNC(barriern_zanzou) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 scales[5] = {1.7f, 2.4f, 3.1f, 3.8f, 4.5f};

    return barriern_zanzou_sub(isFirstCall, unit, scales, 0);
}
