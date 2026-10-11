// include: driver/effdrv.h
// proto: USER_FUNC(crystal_bgmode);
USER_FUNC(crystal_bgmode) {
    EffectEntry* eff = effNameToPtr((const char*)evtGetValue(event, event->args[0]));

    ((s32*)eff->userdata)[14] = 5;
    return EVT_RETURN_DONE;
}
