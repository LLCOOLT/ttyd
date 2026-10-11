// include: driver/npcdrv.h
// proto: static USER_FUNC(evt_shuryolight_run_power_evt);
static USER_FUNC(evt_shuryolight_run_power_evt) {
    s32* code = (s32*)evtGetValue(event, event->args[0]);

    slhp->powerEvt = shuryolightRunEvt(code, slhp->powerEvt);
    return EVT_RETURN_DONE;
}
