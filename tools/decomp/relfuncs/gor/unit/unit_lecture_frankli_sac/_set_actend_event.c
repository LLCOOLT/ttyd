// include: manager/evtmgr_cmd.h
// include: battle/battle.h
// include: battle/battle_unit.h
// proto: USER_FUNC(_set_actend_event);
USER_FUNC(_set_actend_event) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 id = evtGetValue(event, args[0]);
    s32 evt = evtGetValue(event, args[1]);
    BattleUnit* unit;

    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    *(s32*)&unit->field_0x2B4[0x2C4 - 0x2B4] = evt;
    return EVT_RETURN_DONE;
}
