// include: driver/camdrv.h
// include: driver/icondrv.h
// decl: typedef struct SlotWork { u32 flags; s32 phase; f32 reberAngle; f32 angle[2][3]; f32 speed[3]; s8 state[3]; s8 face[2][3]; s8 stopCount[3]; s32 wait[3]; s32 extra[3]; s32 counter; s32 neonCount; s32 monteCount; s32 nowSlot; s32 caseId[2]; EventEntry* monteEvt; s32 sfxId; s16 cursor; } SlotWork;
// decl: typedef struct GMonteSub { s32 unk0; Vec pos; f32 scale; u8 unk14[0x38 - 0x14]; } GMonteSub;
// decl: typedef struct GMonte { u8 hidden; u8 state; s16 wait; s16 timer; u8 unk6[2]; GMonteSub sub; Vec vel; SlotWork* owner; } GMonte;
// decl: static GMonte* monte_p;
// proto: static void monte_disp(CameraId camera, void* param);
static void monte_disp(CameraId camera, void* param) {
    GMonte* monte = param;
    s32 i;

    for (i = 0; i < monte->owner->monteCount; i++) {
        if (monte[i].hidden == 0) {
            iconDispGx(&monte[i].sub.pos, 0x40, 0x13F, 1.0f);
        }
    }
}
