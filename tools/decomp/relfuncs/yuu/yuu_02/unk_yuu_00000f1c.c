// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// include: memory.h
// include: string.h
// include: mario/mario.h
// include: driver/dispdrv.h
// decl: typedef struct MiniGameWork { EventEntry* event; EventEntry* subEvent; u16 flags; s32 type; s32 (*init)(EventEntry* event, BOOL isFirstCall); s32 (*main)(EventEntry* event, BOOL isFirstCall); void (*disp)(CameraId camera, void* param); void* data; } MiniGameWork;
// decl: typedef struct RollWork { u32 flags; s32 phase; s32 coins; s32 result; s32 index; EventEntry* jumpEvent; Vec pos; s32 monteCount; EventEntry* viewEvent; } RollWork;
// decl: typedef struct MonteSub { s32 unk0; Vec pos; f32 scale; u8 unk14[0x38 - 0x14]; } MonteSub;
// decl: typedef struct Monte { u8 hidden; u8 unk1; s16 num; u8 state; u8 unk5[3]; MonteSub sub; MiniGameWork* wp; } Monte;
// decl: typedef struct MonteTable { f32 x0; f32 x1; f32 z0; f32 z1; s32 num; s32 type; } MonteTable;
// decl: static void* yuunpc_wp;
// decl: static Monte* monte_p; /* unk_yuu_bss00000004 */
// decl: static Monte* icon_monte_p;
// decl: void unk_yuu_00001054(CameraId camera, void* param);
// proto: USER_FUNC(unk_yuu_00000f1c);
USER_FUNC(unk_yuu_00000f1c) {
    BOOL exists = FALSE;
    MiniGameWork* wp = (MiniGameWork*)event->lwData[0];
    MarioWork* mario = marioGetPtr();
    s32 total;
    s32 i;
    MonteSub* sub;

    if (isFirstCall) {
        if (icon_monte_p != NULL) {
            exists = TRUE;
        }
        total = 0;
        for (i = 0; i < 1; i++) {
            total++;
        }
        icon_monte_p = _mapAlloc(total * sizeof(Monte));
        memset(icon_monte_p, 0, total * sizeof(Monte));
        icon_monte_p->num = total;
        icon_monte_p->wp = wp;
        for (i = 0; i < icon_monte_p->num; i++) {
            sub = &icon_monte_p[i].sub;
            sub->pos = (Vec){0.0f, 0.0f, 0.0f};
            sub->scale = 1.0f;
            icon_monte_p[i].hidden = 1;
        }
    }
    for (i = 0; i < icon_monte_p->num; i++) {
    }
    if (!exists) {
        dispEntry(CAMERA_2D, 0.0f, 0, unk_yuu_00001054, icon_monte_p);
    }
    return EVT_RETURN_BLOCK;
}
