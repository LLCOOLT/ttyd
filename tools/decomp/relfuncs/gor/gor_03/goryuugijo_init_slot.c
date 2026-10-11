// include: driver/camdrv.h
// decl: typedef struct GoryuuWork { EventEntry* event; EventEntry* subEvent; u16 flags; s32 type; s32 (*init)(EventEntry* event, BOOL isFirstCall); s32 (*main)(EventEntry* event, BOOL isFirstCall); void (*disp)(CameraId camera, void* param); void* data; } GoryuuWork;
// decl: typedef struct SlotWork { u32 flags; s32 phase; f32 reberAngle; f32 angle[2][3]; f32 speed[3]; s8 state[3]; s8 face[2][3]; s8 stopCount[3]; s32 wait[3]; s32 extra[3]; s32 counter; s32 neonCount; s32 monteCount; s32 nowSlot; s32 caseId[2]; EventEntry* monteEvt; s32 sfxId; s16 cursor; } SlotWork;
// proto: void goryuugijo_init_slot(EventEntry* event, BOOL isFirstCall);
void goryuugijo_init_slot(EventEntry* event, BOOL isFirstCall) {
    SlotWork* data = ((GoryuuWork*)event->lwData[0])->data;

    data->counter = 0;
    data->reberAngle = 0.0f;
    data->monteEvt = NULL;
    data->flags &= ~1;
}
