// include: driver/npcdrv.h
// proto: USER_FUNC(evt_shuryolight_run_head_evt_17_text_10718);
USER_FUNC(evt_shuryolight_run_head_evt_17_text_10718) {
    s32* code = (s32*)evtGetValue(event, event->args[0]);

    slhp->headEvt = shuryolightRunEvt(code, slhp->headEvt);
    return EVT_RETURN_DONE;
}
