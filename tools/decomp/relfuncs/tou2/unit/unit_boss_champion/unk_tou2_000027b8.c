// include: driver/effdrv.h
// include: manager/evtmgr_cmd.h
// decl: EffectEntry* effFallEntry(s32 type, f32 x, f32 y, f32 z, f32 arg4, f32 arg5, f32 arg6, s32 arg7, s32 arg8);
// proto: USER_FUNC(unk_tou2_000027b8);
USER_FUNC(unk_tou2_000027b8) {
    s32* args = event->args;
    s32 var = args[0];
    s32 type = evtGetValue(event, args[1]);
    f32 x = evtGetFloat(event, args[2]);
    f32 y = evtGetFloat(event, args[3]);
    f32 z = evtGetFloat(event, args[4]);
    f32 a = evtGetFloat(event, args[5]);
    f32 b = evtGetFloat(event, args[6]);
    f32 c = evtGetFloat(event, args[7]);
    s32 d = evtGetValue(event, args[8]);
    s32 e = evtGetValue(event, args[9]);
    EffectEntry* eff = effFallEntry(type, x, y, z, a, b, c, d, e);

    evtSetValue(event, var, (s32)eff);
    return EVT_RETURN_DONE;
}
