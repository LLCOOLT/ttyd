// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// include: driver/icondrv.h
// include: mario/mariost.h
// decl: typedef struct MiniGameWork { EventEntry* event; EventEntry* subEvent; u16 flags; s32 type; s32 (*init)(EventEntry* event, BOOL isFirstCall); s32 (*main)(EventEntry* event, BOOL isFirstCall); void (*disp)(CameraId camera, void* param); void* data; } MiniGameWork;
// decl: typedef struct SlitWork { u32 flags; s32 phase; s32 coins; s32 result; s32 state; s32 timer; f32 rot1; f32 rot2; s32 monteCount; EventEntry* viewEvent; } SlitWork;
// decl: typedef struct MonteSub { s32 unk0; Vec pos; f32 scale; u8 unk14[0x38 - 0x14]; } MonteSub;
// decl: typedef struct Monte { u8 hidden; u8 unk1; s16 num; u8 state; u8 unk5[3]; MonteSub sub; MiniGameWork* wp; } Monte;
// decl: Monte* unk_yuu_bss00000010;
// decl: static void* yuunpc_wp;
// proto: void unk_yuu_0000365c(CameraId camera, void* param);
void unk_yuu_0000365c(CameraId camera, void* param) {
    Monte* monte = param;
    s32 i;
    Vec pos;

    if (monte != NULL) {
        for (i = 0; i < monte->num; i++) {
            if (monte[i].hidden == 0) {
                pos = monte[i].sub.pos;
                if ((gp->retraceCount & 0x1F) < 9) {
                    pos.y += 5.0f;
                }
                iconDispGx(&pos, 0, 0x1B6, 1.0f);
            }
        }
    }
}
