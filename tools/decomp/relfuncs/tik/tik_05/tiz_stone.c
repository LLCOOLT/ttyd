// include: driver/effdrv.h
// decl: void effStardustN64SetDrawCam(EffectEntry* eff, s32 camera);
// decl: void effStardust2N64SetDrawCam(EffectEntry* eff, s32 camera);
// proto: USER_FUNC(tiz_stone);
USER_FUNC(tiz_stone) {
    f32 t = evtGetValue(event, event->args[0]);
    EffectEntry* eff;

    t /= 10000.0f;
    eff = effNameToPtr("tiz_dust");
    if (eff != NULL) {
        effStardustN64SetDrawCam(eff, 7);
    }
    eff = effNameToPtr("tiz_stone");
    if (eff != NULL) {
        ((s32*)eff->userdata)[14] = 7;
        ((u8*)eff->userdata)[0x5F] = 255.0f * t;
        ((f32*)eff->userdata)[7] = 5.0f * (360.0f * t);
    }
    eff = effNameToPtr("tiz_dust2");
    if (eff != NULL) {
        effStardust2N64SetDrawCam(eff, 7);
    }
    return EVT_RETURN_DONE;
}
