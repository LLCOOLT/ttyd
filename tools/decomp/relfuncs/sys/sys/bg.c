// decl: EffectEntry* effItemGetEntry(s32 type, f32 x, f32 y, f32 z);
// proto: USER_FUNC(bg);
USER_FUNC(bg) {
    EffectEntry* eff = effItemGetEntry(0, 0.0f, 0.0f, 0.0f);

    ((s32*)eff->userdata)[8] = 1;
    ((s32*)eff->userdata)[14] = 5;
    return EVT_RETURN_DONE;
}
