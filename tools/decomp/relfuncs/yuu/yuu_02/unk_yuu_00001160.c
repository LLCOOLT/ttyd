// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// decl: typedef struct MiniGameWork { EventEntry* event; EventEntry* subEvent; u16 flags; s32 type; s32 (*init)(EventEntry* event, BOOL isFirstCall); s32 (*main)(EventEntry* event, BOOL isFirstCall); void (*disp)(CameraId camera, void* param); void* data; } MiniGameWork;
// decl: typedef struct RollWork { u32 flags; s32 phase; s32 coins; s32 result; s32 index; EventEntry* jumpEvent; Vec pos; s32 monteCount; EventEntry* viewEvent; } RollWork;
// decl: typedef struct MonteSub { s32 unk0; Vec pos; f32 scale; u8 unk14[0x38 - 0x14]; } MonteSub;
// decl: typedef struct Monte { u8 hidden; u8 unk1; s16 num; u8 state; u8 unk5[3]; MonteSub sub; MiniGameWork* wp; } Monte;
// decl: typedef struct MonteTable { f32 x0; f32 x1; f32 z0; f32 z1; s32 num; s32 type; } MonteTable;
// decl: static void* yuunpc_wp;
// decl: static Monte* monte_p; /* unk_yuu_bss00000004 */
// decl: static Monte* icon_monte_p;
// proto: USER_FUNC(unk_yuu_00001160);
USER_FUNC(unk_yuu_00001160) {
    s32* args = event->args;
    s32 on = evtGetValue(event, args[0]);
    s32 idx = evtGetValue(event, args[1]);

    if (icon_monte_p != NULL) {
        if (on) {
            icon_monte_p[idx].hidden = 0;
        } else {
            icon_monte_p[idx].hidden = 1;
        }
    }
    return EVT_RETURN_DONE;
}
