// include: battle/battle.h
// proto: USER_FUNC(_mario_ac_failed_check);
USER_FUNC(_mario_ac_failed_check) {
    evtSetValue(event, event->args[0], _battleWorkPointer->marioAcFailed);
    return EVT_RETURN_DONE;
}
