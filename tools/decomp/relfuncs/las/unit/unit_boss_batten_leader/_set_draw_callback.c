// include: battle/battle.h
// include: battle/battle_sub.h
// decl: void animPoseSetDispCallBack(s32 poseId, void (*callback)(BattleUnitPart*, s32), void* userdata);
// decl: void _light_point_callback(BattleUnitPart* part, s32 group);
// proto: USER_FUNC(_set_draw_callback);
USER_FUNC(_set_draw_callback) {
    BattleWork* wp = _battleWorkPointer;
    s32 id = BattleTransID(event, -2);
    BattleUnit* unit = BattleGetUnitPtr(wp, id);
    BattleUnitPart* part = BtlUnit_GetPartsPtr(unit, 1);
    BattleUnitPart* p3;
    BattleUnitPart* p4;
    BattleUnitPart* p5;
    BattleUnitPart* p6;
    BattleUnitPart* p7;

    animPoseSetDispCallBack(part->poseId, _light_point_callback, part);
    p3 = BtlUnit_GetPartsPtr(unit, 3);
    p4 = BtlUnit_GetPartsPtr(unit, 4);
    p5 = BtlUnit_GetPartsPtr(unit, 5);
    p6 = BtlUnit_GetPartsPtr(unit, 6);
    p7 = BtlUnit_GetPartsPtr(unit, 7);
    p3->attributes |= 0x1000000;
    p4->attributes |= 0x1000000;
    p5->attributes |= 0x1000000;
    p6->attributes |= 0x1000000;
    p7->attributes |= 0x1000000;
    return EVT_RETURN_DONE;
}
