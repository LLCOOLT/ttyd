// include: system.h
// decl: typedef struct TobiWork { Vec pos; s32 type; } TobiWork;
// decl: typedef struct NanNpc { u8 field_0x0[0x18]; Vec pos; Vec start; Vec target; u8 field_0x3C[0x50 - 0x3C]; OSTime time; u8 field_0x58[0x60 - 0x58]; f32 dir; void (*func)(struct NanNpc*); s32 state; s32 duration; s32 nextState; u8 field_0x74[0x78 - 0x74]; f32 vy; f32 dy; u8 field_0x80[0xA0 - 0x80]; TobiWork* work; s32 angle; s32 radius; u8 field_0xAC[0xC0 - 0xAC]; } NanNpc;
// decl: typedef struct NanNpcWork { NanNpc* entries; } NanNpcWork;
// decl: extern NanNpcWork* nanNPCWork;
// proto: NanNpc* random_choice_target(s32 type);
NanNpc* random_choice_target(s32 type) {
    NanNpcWork* wp = nanNPCWork;
    s32 idx;

    switch (type) {
        case 0:
        case 1:
            idx = irand(100) + 205;
            break;
        case 2:
        default:
            if (irand(2)) {
                idx = irand(95) + 10;
            } else {
                idx = irand(100) + 105;
            }
            break;
    }
    return &wp->entries[idx];
}
