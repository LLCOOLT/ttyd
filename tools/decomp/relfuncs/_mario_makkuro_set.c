// include: battle/battle.h
// include: battle/battle_sub.h
// include: driver/animdrv.h
// proto: USER_FUNC(_mario_makkuro_set);
void faker_mario_makkuro_set(BattleUnit* unit);

USER_FUNC(_mario_makkuro_set) {
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit = BattleGetUnitPtr(wp, BattleTransID(event, -2));

    if (unit != NULL) {
        faker_mario_makkuro_set(unit);
        animPoseSetMaterialFlagOn(BtlUnit_GetPartsPtr(unit, 1)->poseId, 0xB000000);
    }
    return EVT_RETURN_DONE;
}
