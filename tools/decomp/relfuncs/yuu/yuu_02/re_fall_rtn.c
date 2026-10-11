// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// include: memory.h
// decl: typedef struct MiniGameWork { EventEntry* event; EventEntry* subEvent; u16 flags; s32 type; s32 (*init)(EventEntry* event, BOOL isFirstCall); s32 (*main)(EventEntry* event, BOOL isFirstCall); void (*disp)(CameraId camera, void* param); void* data; } MiniGameWork;
// decl: typedef struct RollWork { u32 flags; s32 phase; s32 coins; s32 result; s32 index; EventEntry* jumpEvent; Vec pos; s32 monteCount; EventEntry* viewEvent; } RollWork;
// decl: typedef struct MonteSub { s32 unk0; Vec pos; f32 scale; u8 unk14[0x38 - 0x14]; } MonteSub;
// decl: typedef struct Monte { u8 hidden; u8 unk1; s16 num; u8 state; u8 unk5[3]; MonteSub sub; MiniGameWork* wp; } Monte;
// decl: typedef struct MonteTable { f32 x0; f32 x1; f32 z0; f32 z1; s32 num; s32 type; } MonteTable;
// decl: static void* yuunpc_wp;
// decl: static Monte* monte_p; /* unk_yuu_bss00000004 */
// decl: static Monte* icon_monte_p;
// decl: extern s32 minigame_view_monte[];
// proto: static USER_FUNC(re_fall_rtn);
static USER_FUNC(re_fall_rtn) {
    RollWork* data;

    if (monte_p != NULL) {
        data = monte_p->wp->data;
        if (data->viewEvent != NULL) {
            evtDeleteID(data->viewEvent->eventId);
            data->viewEvent = NULL;
            _mapFree(monte_p);
            data->viewEvent = evtEntryType(minigame_view_monte, 0, 0, 0);
            data->viewEvent->lwData[0] = (s32)monte_p->wp;
        }
    }
    return EVT_RETURN_DONE;
}
