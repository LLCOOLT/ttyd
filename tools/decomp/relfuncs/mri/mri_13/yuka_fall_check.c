// include: driver/hitdrv.h
// include: dolphin/mtx.h
// decl: typedef struct PuniData { u8 field_0x0[0x4]; u32 flags; u8 field_0x8[0x12C - 0x8]; Vec position; u8 field_0x138[0x148 - 0x138]; f32 field_0x148; u8 field_0x14C[0x15C - 0x14C]; Vec field_0x15C; u8 field_0x168[0x184 - 0x168]; f32 field_0x184; f32 field_0x188; u8 field_0x18C[0x5A8 - 0x18C]; } PuniData;
// decl: PuniData* puniGetPunidat(void);
// proto: USER_FUNC(yuka_fall_check);
USER_FUNC(yuka_fall_check) {
    s32 i;

    for (i = 1; i < 103; i++) {
        PuniData* puni = &puniGetPunidat()[i];
        if (puni->flags & 0x400) {
            Vec dir = {0.0f, -1.0f, 0.0f};
            Vec fall = {0.0f, -3.0f, 0.0f};
            Vec pos;
            Vec hit;
            Vec n;
            f32 dist;

            dist = 3.0f;
            pos = puni->position;
            if (hitCheckFilter(NULL, &hit.x, &hit.y, &hit.z, &dist, &n.x, &n.y, &n.z, pos.x, pos.y, pos.z, dir.x, dir.y,
                               dir.z)) {
                puni->position = hit;
            } else {
                PSVECAdd(&puni->position, &fall, &puni->position);
            }
        }
    }
    return EVT_RETURN_DONE;
}
