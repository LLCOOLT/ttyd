// include: driver/effdrv.h
// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(eff_guruguru);
EffectEntry* effGuruguruN64Entry(s32 type, s32 arg1, f32 x, f32 y, f32 z, f32 arg5);

USER_FUNC(eff_guruguru) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);
    f32 w = evtGetFloat(event, args[4]);
    EffectEntry* eff = effGuruguruN64Entry(0, 3, x, y, z, w);

    ((f32*)eff->userdata)[11] = 0.8f;
    effSetName(eff, name);
    return EVT_RETURN_DONE;
}
