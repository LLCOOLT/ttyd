// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_sub.h
// decl: static s32 barriern_satellite_zanzou_sub(BOOL isFirstCall, BattleUnit* unit, f32* scales, s32 n, s32 type);
// proto: static USER_FUNC(barriern_satellite_zanzou2);
static USER_FUNC(barriern_satellite_zanzou2) {
    s32* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, args[0]));
    s32 n = evtGetValue(event, args[1]);
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit = BattleGetUnitPtr(wp, id);
    BattleUnit* sat;
    f32 scales[5] = {1.7f, 2.4f, 3.1f, 3.8f, 4.5f};

    sat = BattleGetUnitPtr(wp, unit->work[4 + n]);
    return barriern_satellite_zanzou_sub(isFirstCall, sat, scales, n, 1);
}
