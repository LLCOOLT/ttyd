// include: battle/battle.h
// proto: USER_FUNC(unk_las_0000855c);
BOOL BtlUnit_CheckShadowGuard(BattleUnit* unit);

USER_FUNC(unk_las_0000855c) {
    s32* args = event->args;

    if (BtlUnit_CheckShadowGuard(BattleGetMarioPtr(_battleWorkPointer)) == 1) {
        evtSetValue(event, args[0], 1);
    } else {
        evtSetValue(event, args[0], 0);
    }
    return EVT_RETURN_DONE;
}
