// include: driver/effdrv.h
// proto: USER_FUNC(starstone_fall);
USER_FUNC(starstone_fall) {
    EffectEntry* eff = effNameToPtr((const char*)evtGetValue(event, event->args[0]));

    ((s32*)eff->userdata)[15] = 1;
    return EVT_RETURN_DONE;
}
