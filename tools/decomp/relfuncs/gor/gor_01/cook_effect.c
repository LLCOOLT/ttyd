// include: manager/evtmgr_cmd.h
// decl: s32 chk_cook_eff_type(s32 item);
// decl: s32 psndSFXOn_3D(const char* name, Vec* position);
// decl: EffectEntry* effFireEntry(s32 type, s32 time, f32 x, f32 y, f32 z, f32 scale);
// decl: EffectEntry* effKemuri12N64Entry(s32 type, s32 time, f32 x, f32 y, f32 z, f32 scale);
// proto: USER_FUNC(cook_effect);
USER_FUNC(cook_effect) {
    switch (chk_cook_eff_type(evtGetValue(event, event->args[0]))) {
        case 0:
            psndSFXOn_3D("SFX_EVT_COOK_FIRE1", &(Vec){-380.0f, 25.0f, -170.0f});
            effFireEntry(4, 60, -380.0f, 25.0f, -170.0f, 1.5f);
            break;
        case 1:
        default:
            psndSFXOn_3D("SFX_EVT_COOK_EXPLOSION1", &(Vec){-380.0f, 60.0f, -170.0f});
            effKemuri12N64Entry(0, 60, -380.0f, 60.0f, -170.0f, 2.0f);
            break;
    }
    return EVT_RETURN_DONE;
}
