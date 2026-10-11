// include: driver/npcdrv.h
// proto: static USER_FUNC(evt_shuryolight_run_head_evt);
static USER_FUNC(evt_shuryolight_run_head_evt) {
    s32* code = (s32*)evtGetValue(event, event->args[0]);

    slhp->headEvt = shuryolightRunEvt(code, slhp->headEvt);
    return EVT_RETURN_DONE;
}
