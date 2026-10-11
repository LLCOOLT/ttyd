// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// include: memory.h
// decl: typedef struct MiniGameWork { EventEntry* event; EventEntry* subEvent; u16 flags; s32 type; s32 (*init)(EventEntry* event, BOOL isFirstCall); s32 (*main)(EventEntry* event, BOOL isFirstCall); void (*disp)(CameraId camera, void* param); void* data; } MiniGameWork;
// decl: typedef struct SlitWork { u32 flags; s32 phase; s32 coins; s32 result; s32 state; s32 timer; f32 rot1; f32 rot2; s32 monteCount; EventEntry* viewEvent; } SlitWork;
// decl: typedef struct MonteSub { s32 unk0; Vec pos; f32 scale; u8 unk14[0x38 - 0x14]; } MonteSub;
// decl: typedef struct Monte { u8 hidden; u8 unk1; s16 num; u8 state; u8 unk5[3]; MonteSub sub; MiniGameWork* wp; } Monte;
// decl: Monte* unk_yuu_bss00000010;
// decl: static void* yuunpc_wp;
// decl: extern s32 unk_evt_yuu_00015fe0[];
// proto: USER_FUNC(unk_yuu_0000341c);
USER_FUNC(unk_yuu_0000341c) {
    SlitWork* data;

    if (unk_yuu_bss00000010 != NULL) {
        data = unk_yuu_bss00000010->wp->data;
        if (data->viewEvent != NULL) {
            evtDeleteID(data->viewEvent->eventId);
            data->viewEvent = NULL;
            _mapFree(unk_yuu_bss00000010);
            data->viewEvent = evtEntryType(unk_evt_yuu_00015fe0, 0, 0, 0);
            data->viewEvent->lwData[0] = (s32)unk_yuu_bss00000010->wp;
        }
    }
    return EVT_RETURN_DONE;
}
