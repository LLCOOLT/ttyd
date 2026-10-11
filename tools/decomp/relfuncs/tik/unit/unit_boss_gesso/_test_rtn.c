// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_sub.h
// include: battle/battle_pad.h
// include: system.h
// proto: USER_FUNC(_test_rtn);
USER_FUNC(_test_rtn) {
    BattleWork* wp = _battleWorkPointer;
    s32 id = BattleTransID(event, -2);
    BattleUnit* unit;
    BattleUnit* target;
    s32 targetId;

    if (id == -1) {
        return EVT_RETURN_DONE;
    }
    unit = BattleGetUnitPtr(wp, id);
    if (unit == NULL) {
        return EVT_RETURN_DONE;
    }
    if (isFirstCall) {
        event->userdata[0] = 0;
    }
    // debug: pick a unit with the d-pad, then scale and move it
    if (BattlePadMultiCheckTrigger(2, 1)) {
        event->userdata[0]++;
        if (event->userdata[0] >= 3) {
            event->userdata[0] = 0;
        }
    }
    if (BattlePadMultiCheckTrigger(2, 2)) {
        event->userdata[0]--;
        if (event->userdata[0] < 0) {
            event->userdata[0] = 2;
        }
    }
    switch (event->userdata[0]) {
        case 0:
            targetId = BattleTransID(event, -2);
            break;
        case 1:
            targetId = unit->work[1];
            break;
        case 2:
            targetId = unit->work[2];
            break;
    }
    target = BattleGetUnitPtr(wp, targetId);
    BattlePadMultiCheckTrigger(2, 3);
    if (BattlePadMultiCheckNow(2, 0x40)) {
        target->mScale.x += 0.02f;
        target->mScale.y += 0.02f;
        target->mScale.z += 0.02f;
    }
    if (BattlePadMultiCheckNow(2, 0x20)) {
        target->mScale.x -= 0.02f;
        target->mScale.y -= 0.02f;
        target->mScale.z -= 0.02f;
    }
    target->mPosition.x += 0.1f * keyGetStickX(2);
    target->mPosition.y += 0.1f * keyGetSubStickY(2);
    target->mPosition.z -= 0.1f * keyGetStickY(2);
    BattlePadMultiCheckTrigger(2, 0x100);
    return EVT_RETURN_BLOCK;
}
