// include: manager/evtmgr_cmd.h
// decl: typedef struct TobiWork { Vec pos; s32 type; } TobiWork;
// decl: typedef struct NanNpc { u8 field_0x0[0x18]; Vec pos; Vec start; Vec target; u8 field_0x3C[0x50 - 0x3C]; OSTime time; u8 field_0x58[0x60 - 0x58]; f32 dir; void (*func)(struct NanNpc*); s32 state; s32 duration; s32 nextState; u8 field_0x74[0x78 - 0x74]; f32 vy; f32 dy; u8 field_0x80[0xA0 - 0x80]; TobiWork* work; s32 angle; s32 radius; u8 field_0xAC[0xC0 - 0xAC]; } NanNpc;
// decl: typedef struct NanNpcWork { NanNpc* entries; } NanNpcWork;
// decl: extern NanNpcWork* nanNPCWork;
// decl: double sin(double x);
// decl: double cos(double x);
// proto: USER_FUNC(dai3_butai_main_func);
USER_FUNC(dai3_butai_main_func) {
    s32* args = event->args;
    f32 a = evtGetValue(event, args[0]);
    f32 b = evtGetValue(event, args[1]);
    f32 cx = evtGetValue(event, args[2]);
    f32 cz = evtGetValue(event, args[3]);
    s32 d = b - a;
    s32 i;
    NanNpc* npc;
    f32 r;
    f32 rad;
    f32 s;
    f32 c;
    NanNpcWork* wp = nanNPCWork;

    for (i = 0; i < 100; i++) {
        npc = &wp->entries[i + 205];
        npc->angle += d;
        r = npc->radius;
        rad = npc->angle;
        rad = 3.141592f * rad / 180.0f;
        s = sin(rad);
        c = cos(rad);
        npc->pos.x = r * s + cx;
        npc->pos.z = r * c + cz;
    }
    return EVT_RETURN_DONE;
}
