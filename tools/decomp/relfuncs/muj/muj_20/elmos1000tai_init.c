// include: driver/npcdrv.h
// include: system.h
// decl: typedef struct NanNpc { u8 field_0x0[0x10]; NpcEntry* npc; u8 field_0x14[0x18 - 0x14]; Vec pos; u8 field_0x24[0x50 - 0x24]; OSTime time; u8 field_0x58[0x60 - 0x58]; f32 dir; void (*func)(struct NanNpc*); s32 state; s32 duration; s32 index; s32 dist; u8 field_0x78[0xBF - 0x78]; u8 alpha; } NanNpc;
// decl: typedef struct NanNpcWork { NanNpc* entries; u8 field_0x4[0xC - 0x4]; s32 count; u32 flags; } NanNpcWork;
// decl: extern NanNpcWork* nanNPCWork;
// decl: double sin(double x);
// decl: double cos(double x);
// proto: USER_FUNC(elmos1000tai_init);
USER_FUNC(elmos1000tai_init) {
    NanNpcWork* wp = nanNPCWork;
    s32 i;
    NanNpc* npc;
    s32 deg;
    s32 a;
    s32 r;
    f32 sn;
    f32 rad;
    f32 cs;
    f32 dist;
    f32 fdeg;

    wp->flags |= 1;
    for (i = 0; i < wp->count; i++) {
        npc = &wp->entries[i];
        npc->npc->flags |= 4;
        npc->alpha = 0;
        npc->dir = 90.0f;
        npc->index = i;
        if (i % 3) {
            deg = irand(140) + 110;
        } else {
            deg = irand(360);
        }
        fdeg = deg;
        npc->dist = 250;
        r = 330;
        a = __abs(180 - deg);
        if (a < 70) {
            r = (70 - a) * 1000 / 70 + 330;
        }
        npc->dist += irand(r);
        rad = 6.2831855f * fdeg / 360.0f;
        dist = npc->dist;
        sn = sin(rad);
        cs = cos(rad);
        npc->pos.x = 0.9f * (dist * sn);
        npc->pos.y = 100.0f;
        npc->pos.z = 0.5f * (dist * cs) - 100.0f;
    }
    return EVT_RETURN_DONE;
}
