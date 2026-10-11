// include: driver/camdrv.h
// decl: typedef struct GoryuuWork { EventEntry* event; EventEntry* subEvent; u16 flags; s32 type; s32 (*init)(EventEntry* event, BOOL isFirstCall); s32 (*main)(EventEntry* event, BOOL isFirstCall); void (*disp)(CameraId camera, void* param); void* data; } GoryuuWork;
// decl: typedef struct SlotWork { u32 flags; s32 phase; f32 reberAngle; f32 angle[2][3]; f32 speed[3]; s8 state[3]; s8 face[2][3]; s8 stopCount[3]; s32 wait[3]; s32 extra[3]; s32 counter; s32 neonCount; s32 monteCount; s32 nowSlot; s32 caseId[2]; EventEntry* monteEvt; s32 sfxId; s16 cursor; } SlotWork;
// proto: USER_FUNC(evt_goryuugijo_get_caseid);
USER_FUNC(evt_goryuugijo_get_caseid) {
    s32* args = event->args;
    SlotWork* data = ((GoryuuWork*)evtGetValue(event, args[0]))->data;
    s32 idx = evtGetValue(event, args[1]);

    evtSetValue(event, args[2], data->caseId[idx]);
    return EVT_RETURN_DONE;
}
