// include: driver/camdrv.h
// decl: typedef struct GoryuuWork { EventEntry* event; EventEntry* subEvent; u16 flags; s32 type; s32 (*init)(EventEntry* event, BOOL isFirstCall); s32 (*main)(EventEntry* event, BOOL isFirstCall); void (*disp)(CameraId camera, void* param); void* data; } GoryuuWork;
// decl: typedef struct SlotWork { u32 flags; s32 phase; f32 unk8; f32 angle[2][3]; u8 unk24[0x30 - 0x24]; s8 state[3]; s8 face[2][3]; u8 unk39[0x54 - 0x39]; s32 unk54; u8 unk58[0x60 - 0x58]; s32 nowSlot; s32 caseId[2]; s32 unk6C; u8 unk70[4]; s16 unk74; u8 unk76[2]; } SlotWork;
// proto: USER_FUNC(evt_goryuugijo_set_nowslot);
USER_FUNC(evt_goryuugijo_set_nowslot) {
    s32* args = event->args;
    SlotWork* data = ((GoryuuWork*)evtGetValue(event, args[0]))->data;

    data->nowSlot = evtGetValue(event, args[1]);
    return EVT_RETURN_DONE;
}
