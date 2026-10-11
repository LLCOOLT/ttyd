// include: driver/npcdrv.h
// include: mario/mariost.h
// include: dolphin/os.h
// include: system.h
// decl: typedef struct NanNpc { u8 field_0x0[0x10]; NpcEntry* npc; u8 field_0x14[0x18 - 0x14]; Vec pos; u8 field_0x24[0x50 - 0x24]; OSTime time; u8 field_0x58[0x60 - 0x58]; f32 dir; void (*func)(struct NanNpc*); s32 state; s32 duration; s32 index; s32 dist; u8 field_0x78[0xBF - 0x78]; u8 alpha; } NanNpc;
// decl: typedef struct NanNpcWork { NanNpc* entries; u8 field_0x4[0xC - 0x4]; s32 count; u32 flags; } NanNpcWork;
// decl: extern NanNpcWork* nanNPCWork;
// proto: void elmos1000tai_seq00(NanNpc* npc);
void elmos1000tai_seq00(NanNpc* npc) {
    s32 t;

    switch (npc->state) {
        case 0:
            npc->time = gp->renderTime;
            npc->duration = irand(1000) + npc->dist * 3;
            npc->state = 1;
        case 1:
            if ((s32)OSTicksToMilliseconds((u32)gp->renderTime - (u32)npc->time) >= npc->duration) {
                npc->time = gp->renderTime;
                npc->duration = 500;
                npc->state = 2;
            }
            break;
        case 2:
            t = OSTicksToMilliseconds((u32)gp->renderTime - (u32)npc->time);
            if (t < npc->duration) {
                npc->alpha = intplGetValue(0, t, npc->duration, 0.0f, 255.0f);
            } else {
                npc->state = 3;
            }
            break;
        case 3:
            break;
    }
}
