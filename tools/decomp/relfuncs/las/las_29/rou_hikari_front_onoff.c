// include: manager/evtmgr_cmd.h
// include: driver/effdrv.h
// include: stdio.h
// decl: void mapGrpFlagOn(const char* name, u32 flags);
// decl: void mapGrpFlagOff(const char* name, u32 flags);
// proto: USER_FUNC(rou_hikari_front_onoff);
USER_FUNC(rou_hikari_front_onoff) {
    char name[8];
    s32* args = event->args;
    s32 on = evtGetValue(event, args[0]);
    void (*func)(const char*, u32);
    f32 scale;
    s32 i;
    EffectEntry* eff;

    evtGetValue(event, args[1]);
    func = on ? mapGrpFlagOn : mapGrpFlagOff;
    scale = on ? 0.0f : 0.5f;
    for (i = 39; i <= 62; i++) {
        sprintf(name, "S_rou%02d", i);
        func(name, 1);
        sprintf(name, "hi%d", i);
        eff = effNameToPtr(name);
        ((f32*)eff->userdata)[30] = scale;
        ((f32*)eff->userdata)[31] = scale;
    }
    return EVT_RETURN_DONE;
}
