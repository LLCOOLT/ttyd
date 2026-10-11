// include: manager/evtmgr_cmd.h
// include: driver/effdrv.h
// include: stdio.h
// proto: USER_FUNC(all_hikari_onoff);
USER_FUNC(all_hikari_onoff) {
    char name[16];
    f32 scale = evtGetValue(event, event->args[0]) ? 0.0f : 0.5f;
    s32 i;
    EffectEntry* eff;

    for (i = 1; i <= 66; i++) {
        sprintf(name, "hi%d", i);
        eff = effNameToPtr(name);
        ((f32*)eff->userdata)[30] = scale;
        ((f32*)eff->userdata)[31] = scale;
    }
    return EVT_RETURN_DONE;
}
