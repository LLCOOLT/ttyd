// decl: typedef struct NanNpc { u8 field_0x0[0x18]; Vec pos; Vec posA; Vec posB; u8 field_0x3C[0x50 - 0x3C]; OSTime time; u8 field_0x58[0x60 - 0x58]; f32 dir; void (*func)(struct NanNpc*); s32 state; s32 work6C; s32 work70; s32 work74; f32 work78; f32 work7C; f32 work80; u8 field_0x84[0x88 - 0x84]; Vec posC; u8 field_0x94[0xA4 - 0x94]; s32 workA4; s32 workA8; u8 field_0xAC[0xC0 - 0xAC]; } NanNpc;
// decl: typedef struct NanNpcWork { NanNpc* entries; u8 field_0x4[0xC - 0x4]; s32 count; } NanNpcWork;
// decl: extern NanNpcWork* nanNPCWork;
// decl: void gundan1000tai_seq01(NanNpc* npc);
// proto: USER_FUNC(gundan1000tai_totsugeki);
USER_FUNC(gundan1000tai_totsugeki) {
    NanNpcWork* wp = nanNPCWork;
    s32 i;

    for (i = 0; i < wp->count; i++) {
        wp->entries[i].func = gundan1000tai_seq01;
        wp->entries[i].state = 0;
    }
    return EVT_RETURN_DONE;
}
