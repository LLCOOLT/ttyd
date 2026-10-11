// decl: typedef struct PuniData { u8 field_0x0[0x4]; u32 flags; u8 field_0x8[0xC - 0x8]; s16 field_0xC; u8 field_0xE[0x114 - 0xE]; u16 field_0x114; u8 field_0x116[0x118 - 0x116]; s16 field_0x118; u8 field_0x11A[0x11E - 0x11A]; s16 field_0x11E; u8 field_0x120[0x12C - 0x120]; Vec position; u8 field_0x138[0x15C - 0x138]; Vec field_0x15C; u8 field_0x168[0x174 - 0x168]; f32 field_0x174; u8 field_0x178[0x180 - 0x178]; f32 field_0x180; u8 field_0x184[0x1E0 - 0x184]; s32 field_0x1E0; s32 field_0x1E4; u8 field_0x1E8[0x56C - 0x1E8]; void* field_0x56C; void* field_0x570; u8 field_0x574[0x5A8 - 0x574]; } PuniData;
// decl: PuniData* puniGetPunidat(void);
// decl: void puniModeEventparent(PuniData* puni);
// decl: void puniMoveDecel(PuniData* puni);
// proto: USER_FUNC(puni_parent);
USER_FUNC(puni_parent) {
    s32 offset = evtGetValue(event, event->args[0]) * sizeof(PuniData);
    PuniData* puni = (PuniData*)((u8*)puniGetPunidat() + offset);
    s16 side;

    if (puni->position.x > -180.0f) {
        side = 1;
        puni->field_0x1E4 = event->lwData[11] % 2;
        event->lwData[11]++;
    } else {
        side = 2;
        puni->field_0x1E4 = event->lwData[12] % 2;
        event->lwData[12]++;
    }
    puni->flags |= 0x100000;
    puni->field_0x118 = side;
    puni->field_0xC = 29;
    puni->field_0x114 = 0;
    puni->field_0x11E = 1000;
    puni->field_0x56C = puniModeEventparent;
    puni->field_0x570 = puniMoveDecel;
    return EVT_RETURN_DONE;
}
