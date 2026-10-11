// include: battle/battle.h
// proto: USER_FUNC(_status_window_off);
USER_FUNC(_status_window_off) {
    _battleWorkPointer->statusWindowOff = 1;
    return EVT_RETURN_DONE;
}
