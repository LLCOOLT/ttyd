// include: battle/battle.h
// include: battle/battle_sub.h
// proto: USER_FUNC(_set_draw_callback);
void animPoseSetDispCallBack(s32 poseId, void (*callback)(BattleUnitPart*, s32), void* userdata);

USER_FUNC(_set_draw_callback) {
    BattleWork* wp = _battleWorkPointer;
    s32 id = BattleTransID(event, -2);
    BattleUnit* unit = BattleGetUnitPtr(wp, id);
    BattleUnitPart* part = BtlUnit_GetPartsPtr(unit, 1);

    animPoseSetDispCallBack(part->poseId, _fire_point_callback, part);
    BtlUnit_GetPartsPtr(unit, 2)->attributes |= 0x1000000;
    return EVT_RETURN_DONE;
}
