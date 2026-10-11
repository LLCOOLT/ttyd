// include: mario/mariost.h
// include: system.h
// decl: typedef struct NanNpc { u8 field_0x0[0x18]; Vec pos; u8 field_0x24[0x30 - 0x24]; Vec basePos; u8 field_0x3C[0x50 - 0x3C]; OSTime time; u8 field_0x58[0x68 - 0x58]; s32 state; s32 duration; u8 field_0x70[0xBF - 0x70]; u8 alpha; } NanNpc;
// decl: typedef struct NanNpcWork { NanNpc* entries; } NanNpcWork;
// decl: extern NanNpcWork* nanNPCWork;
// proto: void elmosalpha_func(NanNpc* npc);
void elmosalpha_func(NanNpc* npc) {
    s32 elapsed;

    switch (npc->state) {
        case 0:
            npc->time = gp->renderTime;
            npc->duration = irand(1000);
            npc->state = 1;
        case 1:
            if ((s32)OSTicksToMilliseconds((u32)gp->renderTime - (u32)npc->time) >= npc->duration) {
                npc->time = gp->renderTime;
                npc->duration = 500;
                npc->state = 2;
            }
            break;
        case 2:
            elapsed = OSTicksToMilliseconds((u32)gp->renderTime - (u32)npc->time);
            if (elapsed < npc->duration) {
                npc->alpha = intplGetValue(0, elapsed, npc->duration, 0.0f, 255.0f);
            } else {
                npc->state = 3;
            }
            break;
        case 3:
            break;
    }
}
