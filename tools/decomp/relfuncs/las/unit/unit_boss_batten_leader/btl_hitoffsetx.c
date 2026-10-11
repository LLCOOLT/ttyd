// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_sub.h
// proto: USER_FUNC(btl_hitoffsetx);
USER_FUNC(btl_hitoffsetx) {
    s32 id;
    s32* args = event->args;
    s32 partNo;
    BattleUnitPart* part;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    partNo = evtGetValue(event, args[1]);
    part = BattleGetUnitPartsPtr(id, partNo);


    part->field_0x1A0 = evtGetValue(event, args[2]);
    return EVT_RETURN_DONE;
}
