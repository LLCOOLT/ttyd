// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_sub.h
// decl: void BtlUnit_SetAnim(BattleUnitPart* part, const char* anim);
// proto: USER_FUNC(chain_init);
USER_FUNC(chain_init) {
    BattleWork* wp = _battleWorkPointer;
    s32 id;
    BattleUnit* unit;
    BattleUnitPart* part;
    f32 x;
    f32 y;
    f32 z;
    s32 i;

    id = evtGetValue(event, event->args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    BtlUnit_GetPos(unit, &x, &y, &z);
    // the chain links all start at the chomp
    for (i = 2; i <= 7; i++) {
        part = BtlUnit_GetPartsPtr(unit, i);
        BtlUnit_SetPartsPos(part, x, y, z);
        BtlUnit_SetAnim(part, "WAN_S_1B");
    }
    part = BtlUnit_GetPartsPtr(unit, 8);
    BtlUnit_SetPartsPos(part, x - 20.0f * unit->faceDirection, y, z);
    BtlUnit_SetAnim(part, "WAN_S_1B");
    part = BtlUnit_GetPartsPtr(unit, 9);
    BtlUnit_SetPartsPos(part, x - 20.0f * unit->faceDirection, y, z);
    BtlUnit_SetAnim(part, "WAN_Z_2");
    return EVT_RETURN_DONE;
}
