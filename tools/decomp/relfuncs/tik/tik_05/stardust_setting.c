// include: driver/effdrv.h
// decl: void effStardustN64SetDrawCam(EffectEntry* eff, s32 camera);
// proto: USER_FUNC(stardust_setting);
USER_FUNC(stardust_setting) {
    s32* args = event->args;
    const char* name1 = (const char*)evtGetValue(event, args[0]);
    const char* name2 = (const char*)evtGetValue(event, args[1]);
    EffectEntry* eff1 = effNameToPtr(name1);
    EffectEntry* eff2 = effNameToPtr(name2);

    effStardustN64SetDrawCam(eff1, 5);
    effStardustN64SetDrawCam(eff2, 5);
    return EVT_RETURN_DONE;
}
