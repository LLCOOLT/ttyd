// decl: void countDownStop(void);
// proto: USER_FUNC(evt_countdown_stop);
USER_FUNC(evt_countdown_stop) {
    countDownStop();
    return EVT_RETURN_DONE;
}
