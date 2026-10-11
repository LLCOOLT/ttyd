// include: battle/battle.h
// proto: USER_FUNC(_mario_ac_success_check);
USER_FUNC(_mario_ac_success_check) {
    evtSetValue(event, event->args[0], _battleWorkPointer->marioAcSuccess);
    return EVT_RETURN_DONE;
}
