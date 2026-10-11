// include: system.h
// include: mario/mariost.h
// decl: typedef struct TobiWork { Vec pos; s32 type; } TobiWork;
// decl: typedef struct NanNpc { u8 field_0x0[0x18]; Vec pos; Vec start; Vec target; u8 field_0x3C[0x50 - 0x3C]; OSTime time; u8 field_0x58[0x60 - 0x58]; f32 dir; void (*func)(struct NanNpc*); s32 state; s32 duration; s32 nextState; u8 field_0x74[0x78 - 0x74]; f32 vy; f32 dy; u8 field_0x80[0xA0 - 0x80]; TobiWork* work; s32 angle; s32 radius; u8 field_0xAC[0xC0 - 0xAC]; } NanNpc;
// decl: typedef struct NanNpcWork { NanNpc* entries; } NanNpcWork;
// decl: extern NanNpcWork* nanNPCWork;
// proto: void suifu_kyorokyoro(NanNpc* npc);
void suifu_kyorokyoro(NanNpc* npc) {
    switch (npc->state) {
        case 0:
            npc->time = gp->renderTime;
            npc->state = 1;
            npc->duration = irand(1000) + 100;
            if (npc->dir == 90.0f) {
                npc->dir = 270.0f;
            } else {
                npc->dir = 90.0f;
            }
            break;
        case 1:
            if ((s32)OSTicksToMilliseconds((u32)gp->renderTime - (u32)npc->time) > npc->duration) {
                npc->time = gp->renderTime;
                npc->state = 2;
                npc->duration = irand(350) + 350;
                if (npc->dir == 90.0f) {
                    npc->dir = 270.0f;
                } else {
                    npc->dir = 90.0f;
                }
            }
            break;
        case 2:
            if ((s32)OSTicksToMilliseconds((u32)gp->renderTime - (u32)npc->time) > npc->duration) {
                npc->time = gp->renderTime;
                npc->state = 3;
                npc->duration = irand(350) + 350;
                if (npc->dir == 90.0f) {
                    npc->dir = 270.0f;
                } else {
                    npc->dir = 90.0f;
                }
            }
            break;
        case 3:
            if ((s32)OSTicksToMilliseconds((u32)gp->renderTime - (u32)npc->time) > npc->duration) {
                npc->func = NULL;
                if (npc->dir == 90.0f) {
                    npc->dir = 270.0f;
                }
            }
            break;
    }
}
