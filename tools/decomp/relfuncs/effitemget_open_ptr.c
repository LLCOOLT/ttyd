// include: driver/effdrv.h
// proto: static USER_FUNC(effitemget_open_ptr);
static USER_FUNC(effitemget_open_ptr) {
    EffectEntry* eff = (EffectEntry*)evtGetValue(event, event->args[0]);

    ((s32*)eff->userdata)[8] = 1;
    return EVT_RETURN_DONE;
}
