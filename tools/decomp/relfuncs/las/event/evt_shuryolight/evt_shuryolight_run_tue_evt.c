// include: driver/npcdrv.h
// proto: static USER_FUNC(evt_shuryolight_run_tue_evt);
static USER_FUNC(evt_shuryolight_run_tue_evt) {
    s32* code = (s32*)evtGetValue(event, event->args[0]);

    slhp->tueEvt = shuryolightRunEvt(code, slhp->tueEvt);
    return EVT_RETURN_DONE;
}
