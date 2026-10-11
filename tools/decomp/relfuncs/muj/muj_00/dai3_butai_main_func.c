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
    NanNpcWork* wp = nanNPCWork;
    NanNpc* npc;
    f32 rad;
    f32 r;
    s32 i;

    for (i = 0; i < 100; i++) {
        npc = &wp->entries[i + 205];
        npc->angle += d;
        rad = 3.141592f * npc->angle / 180.0f;
        r = npc->radius;
        npc->pos.x = r * (f32)sin(rad) + cx;
        npc->pos.z = r * (f32)cos(rad) + cz;
    }
    return EVT_RETURN_DONE;
}
