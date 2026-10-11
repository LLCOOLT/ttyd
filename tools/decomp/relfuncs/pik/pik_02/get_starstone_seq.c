// include: driver/effdrv.h
// proto: USER_FUNC(get_starstone_seq);
USER_FUNC(get_starstone_seq) {
    s32* args = event->args;
    EffectEntry* eff = effNameToPtr((const char*)evtGetValue(event, args[0]));

    evtSetValue(event, args[1], ((s32*)eff->userdata)[15]);
    return EVT_RETURN_DONE;
}
