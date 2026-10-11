// include: battle/battle.h
// include: battle/battle_unit.h
// proto: static void outSplineTableSet_Sub(BattleUnit* unit, s32 n, s32* table);
static void outSplineTableSet_Sub(BattleUnit* unit, s32 n, s32* table) {
    BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, unit->work[4 + n]), 1)->work[2] = (s32)table;
}
