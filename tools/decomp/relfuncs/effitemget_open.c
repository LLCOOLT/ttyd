// include: driver/effdrv.h
// proto: static USER_FUNC(effitemget_open);
static USER_FUNC(effitemget_open) {
    EffectEntry* eff = effNameToPtr((const char*)evtGetValue(event, event->args[0]));

    ((s32*)eff->userdata)[8] = 1;
    return EVT_RETURN_DONE;
}
