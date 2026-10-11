// include: battle/battle.h
// include: battle/battle_sub.h
// proto: USER_FUNC(_check_zenei_kouei);
USER_FUNC(_check_zenei_kouei) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 out = args[1];
    f32 x, y, z;

    id = BattleTransID(event, id);
    BtlUnit_GetPos(BattleGetUnitPtr(wp, id), &x, &y, &z);
    if (x >= -120.0f) {
        evtSetValue(event, out, 0);
    } else {
        evtSetValue(event, out, 1);
    }
    return EVT_RETURN_DONE;
}
