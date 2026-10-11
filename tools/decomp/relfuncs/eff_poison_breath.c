// include: driver/effdrv.h
// decl: s32 irand(s32 scalar);
// include: stdlib.h
// decl: EffectEntry* effVaporN64Entry(s32 type, f32 x, f32 y, f32 z, f32 scale, s32 delay);
// proto: USER_FUNC(eff_poison_breath);
USER_FUNC(eff_poison_breath) {
    f32 x;
    f32 y;
    f32 z;
    EffectEntry* eff;
    s32* wk;

    if (evtGetValue(event, event->args[0]) == 0) {
        x = -125.0f;
    } else {
        x = 125.0f;
    }
    x += irand(150) - 75;
    y = irand(70);
    z = irand(80) - 40;
    eff = effVaporN64Entry(0, x, y, z, 2.5f + rand() / 32767.0f, 15);
    wk = eff->userdata;
    wk[6] = 32;
    wk[7] = 115;
    wk[8] = 100;
    wk[9] = 255;
    wk[10] = 32;
    wk[11] = 115;
    wk[12] = 100;
    wk[13] = 255;
    return EVT_RETURN_DONE;
}
