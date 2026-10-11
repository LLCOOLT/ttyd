// include: manager/evtmgr_cmd.h
// include: driver/effdrv.h
// decl: EffectEntry* effSplashEntry(s32 type, f32 x, f32 y, f32 z, f32 scale);
// proto: USER_FUNC(splash_eff);
USER_FUNC(splash_eff) {
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);

    effSplashEntry(0, x, y, z, 3.0f);
    return EVT_RETURN_DONE;
}
