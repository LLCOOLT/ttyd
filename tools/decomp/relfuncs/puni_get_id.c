// decl: typedef struct PuniData { u8 field_0x0[0x116]; s16 id; u8 field_0x118[0x5A8 - 0x118]; } PuniData;
// decl: PuniData* puniGetPunidat(void);
// proto: USER_FUNC(puni_get_id);
USER_FUNC(puni_get_id) {
    s32 offset;
    s32* args = event->args;
    PuniData* puni;

    offset = evtGetValue(event, args[0]) * sizeof(PuniData);
    puni = (PuniData*)((u8*)puniGetPunidat() + offset);
    evtSetValue(event, args[1], puni->id);
    return EVT_RETURN_DONE;
}
