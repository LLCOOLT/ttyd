// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_sub.h
// include: manager/evtmgr_cmd.h
// proto: static USER_FUNC(set_hand_dest);
static USER_FUNC(set_hand_dest) {
    s32 hand;
    BattleUnit* unit;
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id;
    f32* dest;
    f32 x;
    f32 y;
    f32 z;

    id = evtGetValue(event, args[0]);
    hand = evtGetValue(event, args[1]);
    x = evtGetFloat(event, args[2]);
    y = evtGetFloat(event, args[3]);
    z = evtGetFloat(event, args[4]);
    unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    if (unit == NULL) {
        return EVT_RETURN_BLOCK;
    }
    hand -= 2;
    dest = (f32*)unit->work[hand];
    if (BtlUnit_CheckStatus(unit, 10)) {
        dest[0] = 1.25f * -x;
        dest[1] = 1.25f * y;
        dest[2] = 1.25f * z;
    } else if (BtlUnit_CheckStatus(unit, 11)) {
        dest[0] = 0.75f * -x;
        dest[1] = 0.75f * y;
        dest[2] = 0.75f * z;
    } else {
        dest[0] = -x;
        dest[1] = y;
        dest[2] = z;
    }
    return EVT_RETURN_DONE;
}
