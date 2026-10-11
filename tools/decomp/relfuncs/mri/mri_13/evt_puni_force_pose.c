// decl: typedef struct PuniData { u8 field_0x0[0x4]; u32 flags; u8 field_0x8[0x12C - 0x8]; Vec position; u8 field_0x138[0x148 - 0x138]; f32 field_0x148; u8 field_0x14C[0x15C - 0x14C]; Vec field_0x15C; u8 field_0x168[0x184 - 0x168]; f32 field_0x184; f32 field_0x188; u8 field_0x18C[0x5A8 - 0x18C]; } PuniData;
// decl: PuniData* puniGetPunidat(void);
// proto: USER_FUNC(evt_puni_force_pose);
USER_FUNC(evt_puni_force_pose) {
    s32 offset = evtGetValue(event, event->args[0]) * sizeof(PuniData);
    PuniData* puni = (PuniData*)((u8*)puniGetPunidat() + offset);

    puni->field_0x148 = puni->field_0x184 = puni->field_0x188 = 0.0f;
    puni->field_0x15C = (Vec){0.0f, 0.0f, 0.0f};
    return EVT_RETURN_DONE;
}
