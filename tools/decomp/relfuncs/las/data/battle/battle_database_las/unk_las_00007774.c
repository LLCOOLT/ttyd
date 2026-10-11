// include: driver/effdrv.h
// decl: EffectEntry* effFireEntry(s32 type, f32 x, f32 y, f32 z, f32 scale, s32 lifetime);
// decl: void mapObjGetPos(const char* name, Vec* pos);
// proto: USER_FUNC(unk_las_00007774);
USER_FUNC(unk_las_00007774) {
    const char* names[6] = {"hi1", "hi2", "hi3", "hi4", "hi5", "hi6"};
    Vec pos;
    s32 i;

    if (isFirstCall) {
        unk_las_bss00000098 = 0;
        for (i = 0; i < 6; i++) {
            unk_las_bss0000009c[i] = effFireEntry(8, 0.0f, -1000.0f, 0.0f, 1.0f, 1000);
        }
    }
    if (unk_las_bss00000098) {
        for (i = 0; i < 6; i++) {
            effSoftDelete(unk_las_bss0000009c[i]);
        }
        return EVT_RETURN_DONE;
    }
    for (i = 0; i < 6; i++) {
        mapObjGetPos(names[i], &pos);
        if (pos.y > 0.0f) {
            f32* wk = unk_las_bss0000009c[i]->userdata;

            wk[1] = pos.x;
            wk[2] = pos.y - 15.0f;
            wk[3] = pos.z;
        }
    }
    return EVT_RETURN_BLOCK;
}
