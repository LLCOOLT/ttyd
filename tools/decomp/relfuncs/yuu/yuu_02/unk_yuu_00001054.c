// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// include: mario/mario.h
// include: driver/icondrv.h
// include: mario/mariost.h
// decl: typedef struct MiniGameWork { EventEntry* event; EventEntry* subEvent; u16 flags; s32 type; s32 (*init)(EventEntry* event, BOOL isFirstCall); s32 (*main)(EventEntry* event, BOOL isFirstCall); void (*disp)(CameraId camera, void* param); void* data; } MiniGameWork;
// decl: typedef struct RollWork { u32 flags; s32 phase; s32 coins; s32 result; s32 index; EventEntry* jumpEvent; Vec pos; s32 monteCount; EventEntry* viewEvent; } RollWork;
// decl: typedef struct MonteSub { s32 unk0; Vec pos; f32 scale; u8 unk14[0x38 - 0x14]; } MonteSub;
// decl: typedef struct Monte { u8 hidden; u8 unk1; s16 num; u8 state; u8 unk5[3]; MonteSub sub; MiniGameWork* wp; } Monte;
// decl: typedef struct MonteTable { f32 x0; f32 x1; f32 z0; f32 z1; s32 num; s32 type; } MonteTable;
// decl: static void* yuunpc_wp;
// decl: static Monte* monte_p; /* unk_yuu_bss00000004 */
// decl: static Monte* icon_monte_p;
// proto: void unk_yuu_00001054(CameraId camera, void* param);
void unk_yuu_00001054(CameraId camera, void* param) {
    Monte* monte = param;
    MarioWork* mario = marioGetPtr();
    s32 i;
    f32 dir;
    Vec pos;

    if (monte != NULL) {
        for (i = 0; i < monte->num; i++) {
            if (mario->position.z >= 0.0f) {
                dir = 1.0f;
            } else {
                dir = -1.0f;
            }
            if (monte[i].hidden == 0) {
                pos = monte[i].sub.pos;
                if ((gp->retraceCount & 0x1F) < 9) {
                    pos.x -= 5.0f * dir;
                }
                iconDispGx(&pos, 0, 0x163, -2.0f * dir);
            }
        }
    }
}
