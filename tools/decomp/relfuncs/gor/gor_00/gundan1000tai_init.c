// include: system.h
// decl: double sin(double x);
// decl: double cos(double x);
// decl: typedef struct NanNpc { u8 field_0x0[0x18]; Vec pos; Vec posA; Vec posB; u8 field_0x3C[0x50 - 0x3C]; OSTime time; u8 field_0x58[0x60 - 0x58]; f32 dir; void (*func)(struct NanNpc*); s32 state; s32 work6C; s32 work70; s32 work74; f32 work78; f32 work7C; f32 work80; u8 field_0x84[0x88 - 0x84]; Vec posC; u8 field_0x94[0xA4 - 0x94]; s32 workA4; s32 workA8; u8 field_0xAC[0xC0 - 0xAC]; } NanNpc;
// decl: typedef struct NanNpcWork { NanNpc* entries; u8 field_0x4[0xC - 0x4]; s32 count; } NanNpcWork;
// decl: extern NanNpcWork* nanNPCWork;
// decl: void gundan1000tai_seq00(NanNpc* npc);
// proto: USER_FUNC(gundan1000tai_init);
USER_FUNC(gundan1000tai_init) {
    f32 a2;
    f32 angle;
    f32 s;
    f32 radius;
    f32 c;
    f32 base;
    f32 nv;
    s32 i;
    NanNpc* npc;
    NanNpcWork* wp = nanNPCWork;

    for (i = 0; i < wp->count; i++) {
        npc = &wp->entries[i];
        radius = irand(180) + 120;
        angle = 6.2831855f * irand(360) / 360.0f;
        s = sin(angle);
        c = cos(angle);
        npc->posA.x = 0.9f * (radius * s);
        npc->posA.y = 15.0f;
        npc->posA.z = 0.5f * (radius * c) - 300.0f;
        if (npc->posA.x < 30.0f) {
            base = -280.0f;
            npc->dir = 90.0f;
        } else {
            base = 340.0f;
            npc->dir = 270.0f;
        }
        radius = irand(100);
        nv = 6.2831855f * irand(360);
        a2 = nv / 360.0f;
        s = sin(a2);
        c = cos(a2);
        npc->pos.x = radius * s + base;
        npc->pos.y = 15.0f;
        npc->pos.z = radius * c - 300.0f;
        npc->func = gundan1000tai_seq00;
        npc->state = 0;
        npc->work74 = i;
    }
    return EVT_RETURN_DONE;
}
