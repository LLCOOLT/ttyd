// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// include: memory.h
// include: string.h
// include: mario/mario.h
// include: driver/dispdrv.h
// decl: typedef struct MiniGameWork { EventEntry* event; EventEntry* subEvent; u16 flags; s32 type; s32 (*init)(EventEntry* event, BOOL isFirstCall); s32 (*main)(EventEntry* event, BOOL isFirstCall); void (*disp)(CameraId camera, void* param); void* data; } MiniGameWork;
// decl: typedef struct SlitWork { u32 flags; s32 phase; s32 coins; s32 result; s32 state; s32 timer; f32 rot1; f32 rot2; s32 monteCount; EventEntry* viewEvent; } SlitWork;
// decl: typedef struct MonteSub { s32 unk0; Vec pos; f32 scale; u8 unk14[0x38 - 0x14]; } MonteSub;
// decl: typedef struct Monte { u8 hidden; u8 unk1; s16 num; u8 state; u8 unk5[3]; MonteSub sub; MiniGameWork* wp; } Monte;
// decl: Monte* unk_yuu_bss00000010;
// decl: static void* yuunpc_wp;
// decl: void unk_yuu_0000365c(CameraId camera, void* param);
// proto: USER_FUNC(unk_yuu_000034bc);
USER_FUNC(unk_yuu_000034bc) {
    BOOL exists = FALSE;
    MiniGameWork* wp = (MiniGameWork*)event->lwData[0];
    MarioWork* mario = marioGetPtr();
    s32 total;
    s32 i;
    MonteSub* sub;
    Monte* m;

    if (isFirstCall) {
        if (unk_yuu_bss00000010 != NULL) {
            exists = TRUE;
        }
        total = 0;
        for (i = 0; i < 1; i++) {
            total++;
        }
        unk_yuu_bss00000010 = _mapAlloc(total * sizeof(Monte));
        memset(unk_yuu_bss00000010, 0, total * sizeof(Monte));
        unk_yuu_bss00000010->num = total;
        unk_yuu_bss00000010->wp = wp;
        for (i = 0; i < unk_yuu_bss00000010->num; i++) {
            sub = &unk_yuu_bss00000010[i].sub;
            sub->pos = mario->position;
            sub->pos.y += 40.0f;
            sub->scale = 1.0f;
        }
    }
    for (i = 0; i < unk_yuu_bss00000010->num; i++) {
        m = &unk_yuu_bss00000010[i];
        switch (m->state) {
            case 0:
                m->sub.pos = mario->position;
                m->sub.pos.y += 40.0f;
                break;
            case 1:
                break;
        }
    }
    if (!exists) {
        dispEntry(CAMERA_3D, 0.0f, 1, unk_yuu_0000365c, unk_yuu_bss00000010);
    }
    return EVT_RETURN_BLOCK;
}
