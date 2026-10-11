// proto: USER_FUNC(evt_shuryolight_run_evt_17_text_10828);
USER_FUNC(evt_shuryolight_run_evt_17_text_10828) {
    s32* args = event->args;
    s32* power = (s32*)evtGetValue(event, args[0]);
    s32* head = (s32*)evtGetValue(event, args[1]);
    s32* tue = (s32*)evtGetValue(event, args[2]);

    if (power != NULL) {
        slhp->powerEvt = shuryolightRunEvt(power, slhp->powerEvt);
    }
    if (head != NULL) {
        slhp->headEvt = shuryolightRunEvt(head, slhp->headEvt);
    }
    if (tue != NULL) {
        slhp->tueEvt = shuryolightRunEvt(tue, slhp->tueEvt);
    }
    return EVT_RETURN_DONE;
}
