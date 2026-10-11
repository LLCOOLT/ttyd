// include: system.h
// include: mario/mariost.h
// decl: typedef struct TobiWork { Vec pos; s32 type; } TobiWork;
// decl: typedef struct NanNpc { u8 field_0x0[0x18]; Vec pos; Vec start; Vec target; u8 field_0x3C[0x50 - 0x3C]; OSTime time; u8 field_0x58[0x60 - 0x58]; f32 dir; void (*func)(struct NanNpc*); s32 state; s32 duration; s32 nextState; u8 field_0x74[0x78 - 0x74]; f32 vy; f32 dy; u8 field_0x80[0xA0 - 0x80]; TobiWork* work; s32 angle; s32 radius; u8 field_0xAC[0xC0 - 0xAC]; } NanNpc;
// decl: typedef struct NanNpcWork { NanNpc* entries; } NanNpcWork;
// decl: extern NanNpcWork* nanNPCWork;
// decl: NanNpc* random_choice_target(s32 type);
// proto: void tobikakari_seq00(NanNpc* npc);
void tobikakari_seq00(NanNpc* npc) {
    TobiWork* work = npc->work;
    NanNpc* target;
    s32 r;
    s32 elapsed;
    f32 t;

    switch (npc->state) {
        case 0:
            r = irand(1000);
            if (r < 100) {
                npc->state = 10;
            } else if (r < 200) {
                npc->time = (s32)gp->renderTime;
                npc->duration = irand(500) + 1;
                npc->state = 21;
            } else {
                npc->time = (s32)gp->renderTime;
                npc->duration = irand(2000) + 500;
                npc->state = 22;
            }
            break;
        case 10:
            npc->time = (s32)gp->renderTime;
            npc->start = npc->pos;
            target = random_choice_target(work->type);
            npc->target = target->work->pos;
            npc->target.y += 2.0f;
            npc->vy = -4.0f * (f32)(irand(30) + 100);
            npc->dy = npc->target.y - npc->start.y - npc->vy;
            npc->duration = irand(500) + 400;
            if (npc->start.x < npc->target.x) {
                npc->dir = 90.0f;
            } else {
                npc->dir = 270.0f;
            }
            npc->state = 20;
            npc->nextState = 21;
            break;
        case 11:
            npc->time = (s32)gp->renderTime;
            npc->start = npc->pos;
            npc->target = work->pos;
            npc->vy = -4.0f * (f32)(irand(30) + 100);
            npc->dy = npc->target.y - npc->start.y - npc->vy;
            npc->duration = irand(500) + 400;
            npc->state = 20;
            npc->nextState = 22;
            break;
        case 20:
            elapsed = OSTicksToMilliseconds((u32)gp->renderTime - (u32)npc->time);
            if (elapsed < npc->duration) {
                t = (f32)elapsed / (f32)npc->duration;
                npc->pos.x = intplGetValue(0, elapsed, npc->duration, npc->start.x, npc->target.x);
                npc->pos.z = intplGetValue(0, elapsed, npc->duration, npc->start.z, npc->target.z);
                npc->pos.y = npc->start.y + t * (npc->vy * t + npc->dy);
            } else {
                npc->pos = npc->target;
                npc->time = (s32)gp->renderTime;
                npc->duration = irand(2000) + 500;
                npc->state = npc->nextState;
            }
            break;
        case 21:
            if ((s32)OSTicksToMilliseconds((u32)gp->renderTime - (u32)npc->time) > npc->duration) {
                npc->state = 11;
            }
            break;
        case 22:
            if ((s32)OSTicksToMilliseconds((u32)gp->renderTime - (u32)npc->time) > npc->duration) {
                npc->state = 10;
            }
            break;
    }
}
