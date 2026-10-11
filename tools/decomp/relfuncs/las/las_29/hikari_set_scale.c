// include: manager/evtmgr_cmd.h
// include: driver/effdrv.h
// include: stdio.h
// proto: USER_FUNC(hikari_set_scale);
USER_FUNC(hikari_set_scale) {
    char name[8];
    s32* args = event->args;
    s32 n = evtGetValue(event, args[0]);
    f32 scale = evtGetFloat(event, args[1]);
    EffectEntry* eff;

    sprintf(name, "hi%d", n);
    eff = effNameToPtr(name);
    ((f32*)eff->userdata)[30] = scale;
    ((f32*)eff->userdata)[31] = scale;
    return EVT_RETURN_DONE;
}
