// include: driver/npcdrv.h
// decl: typedef struct NanNpc { u8 field_0x0[0x10]; NpcEntry* npc; u8 field_0x14[0x18 - 0x14]; Vec pos; u8 field_0x24[0x50 - 0x24]; OSTime time; u8 field_0x58[0x60 - 0x58]; f32 dir; void (*func)(struct NanNpc*); s32 state; s32 duration; s32 index; s32 dist; u8 field_0x78[0xBF - 0x78]; u8 alpha; } NanNpc;
// decl: typedef struct NanNpcWork { NanNpc* entries; u8 field_0x4[0xC - 0x4]; s32 count; u32 flags; } NanNpcWork;
// decl: extern NanNpcWork* nanNPCWork;
// proto: USER_FUNC(elmos1000tai_start);
USER_FUNC(elmos1000tai_start) {
    NanNpcWork* wp = nanNPCWork;
    NanNpc* npc;
    s32 i;

    for (i = 0; i < wp->count; i++) {
        npc = &wp->entries[i];
        npc->func = elmos1000tai_seq00;
        npc->state = 0;
    }
    return EVT_RETURN_DONE;
}
