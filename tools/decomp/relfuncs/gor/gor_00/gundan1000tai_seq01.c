// include: mario/mariost.h
// include: mario/mario.h
// include: system.h
// include: dolphin/os.h
// decl: double sin(double x);
// decl: double cos(double x);
// decl: typedef struct NanNpc { u8 field_0x0[0x18]; Vec pos; Vec posA; Vec posB; u8 field_0x3C[0x50 - 0x3C]; OSTime time; u8 field_0x58[0x60 - 0x58]; f32 dir; void (*func)(struct NanNpc*); s32 state; s32 work6C; s32 work70; s32 work74; f32 work78; f32 work7C; f32 work80; u8 field_0x84[0x88 - 0x84]; Vec posC; u8 field_0x94[0xA4 - 0x94]; s32 workA4; s32 workA8; u8 field_0xAC[0xC0 - 0xAC]; } NanNpc;
// decl: typedef struct NanNpcWork { NanNpc* entries; u8 field_0x4[0xC - 0x4]; s32 count; } NanNpcWork;
// decl: extern NanNpcWork* nanNPCWork;
// decl: void evt_nannpc_set_animtbl_sub(NanNpc* npc, void* animtbl);
// proto: void gundan1000tai_seq01(NanNpc* npc);
void gundan1000tai_seq01(NanNpc* npc) {
    MarioWork* mario = marioGetPtr();
    s32 r;
    s32 elapsed;
    f32 radius;
    f32 angle;
    f32 s;
    f32 c;
    f32 t;
    f32 dist;

    switch (npc->state) {
        case 0:
            npc->posB = npc->pos;
            npc->workA4 = 0;
            npc->workA8 = 0;
            r = irand(1000);
            if (r < 50) {
                npc->state = 10;
            } else if (r < 150) {
                npc->state = 1;
                npc->work6C = irand(500) + 300;
                npc->time = gp->renderTime;
            } else {
                npc->state = 1;
                npc->work6C = irand(2500) + 500;
                npc->time = gp->renderTime;
            }
            break;
        case 1:
            if (npc->workA8) {
                npc->state = 100;
            } else if ((s32)OSTicksToMilliseconds((u32)gp->renderTime - (u32)npc->time) > npc->work6C) {
                evt_nannpc_set_animtbl_sub(npc, dai3_run_animtbl);
                npc->state = 10;
            }
            break;
        case 10:
        case 11:
            npc->time = gp->renderTime;
            npc->posA = npc->pos;
            if (npc->state == 10) {
                radius = irand(25) + 25;
            } else {
                radius = irand(180) + 120;
            }
            angle = 6.2831855f * irand(360) / 360.0f;
            s = sin(angle);
            c = cos(angle);
            npc->posC.x = 0.9f * (radius * s) + 30.0f;
            npc->posC.y = 15.0f;
            npc->posC.z = 0.5f * (radius * c) - 300.0f;
            npc->work78 = -4.0f * (irand(60) + 50);
            npc->work7C = npc->posC.y - npc->posA.y - npc->work78;
            npc->work6C = irand(500) + 600;
            if (npc->state == 10) {
                npc->work70 = 21;
                if (npc->posA.x < npc->posC.x) {
                    npc->dir = 90.0f;
                } else {
                    npc->dir = 270.0f;
                }
            } else {
                npc->work70 = 22;
                if (npc->posA.x < npc->posC.x) {
                    npc->dir = 270.0f;
                } else {
                    npc->dir = 90.0f;
                }
            }
            npc->state = 20;
            evt_nannpc_set_animtbl_sub(npc, dai3_run_animtbl);
            break;
        case 20:
            elapsed = OSTicksToMilliseconds((u32)gp->renderTime - (u32)npc->time);
            if (elapsed < npc->work6C) {
                t = (f32)elapsed / (f32)npc->work6C;
                npc->pos.x = intplGetValue(0, elapsed, npc->work6C, npc->posA.x, npc->posC.x);
                npc->pos.z = intplGetValue(0, elapsed, npc->work6C, npc->posA.z, npc->posC.z);
                npc->pos.y = npc->posA.y + t * (npc->work78 * t + npc->work7C);
            } else {
                npc->pos = npc->posC;
                npc->state = npc->work70;
                npc->time = gp->renderTime;
                npc->work6C = irand(2000) + 500;
            }
            break;
        case 21:
            if (npc->workA8) {
                npc->state = 100;
            } else if ((s32)OSTicksToMilliseconds((u32)gp->renderTime - (u32)npc->time) > npc->work6C) {
                npc->state = 11;
            }
            break;
        case 22:
            if (npc->workA8) {
                npc->state = 102;
                break;
            }
            npc->work6C = irand(2000) + 500;
            npc->time = gp->renderTime;
            npc->posB = npc->pos;
            npc->work78 = 15.0f + npc->posB.x;
            npc->work7C = npc->posB.x - 15.0f;
            if (irand(1)) {
                npc->work80 = 1.0f;
                npc->dir = 90.0f;
            } else {
                npc->work80 = -1.0f;
                npc->dir = 270.0f;
            }
            npc->state = 30;
            break;
        case 30:
            if (npc->workA8) {
                npc->state = 102;
                break;
            }
            if ((s32)OSTicksToMilliseconds((u32)gp->renderTime - (u32)npc->time) > npc->work6C) {
                npc->state = 10;
                break;
            }
            if (npc->work78 < npc->pos.x) {
                npc->work80 = -1.0f;
                npc->dir = 270.0f;
            }
            if (npc->work7C > npc->pos.x) {
                npc->work80 = 1.0f;
                npc->dir = 90.0f;
            }
            npc->pos.x += npc->work80;
            break;
        case 100:
            radius = irand(180) + 120;
            angle = 6.2831855f * irand(360) / 360.0f;
            s = sin(angle);
            c = cos(angle);
            npc->posC.x = 0.9f * (radius * s) + 30.0f;
            npc->posC.z = 0.5f * (radius * c) - 300.0f;
            dist = distABf(npc->pos.x, npc->pos.z, npc->posA.x, npc->posA.z);
            angle = angleABf(npc->pos.x, npc->pos.z, npc->posA.x, npc->posA.z);
            npc->work78 = sysFrame2SecFloat(dist * 0.5f + (irand(180) + 180));
            npc->work7C = angle;
            npc->work70 = dist / npc->work78;
            npc->work6C = 0;
            npc->state = 101;
        case 101:
            movePos(&npc->pos.x, &npc->pos.z, npc->work78, npc->work7C);
            npc->work6C++;
            if (npc->work6C >= npc->work70) {
                npc->pos.x = npc->posA.x;
                npc->pos.z = npc->posA.z;
                npc->state = 102;
            }
            break;
        case 102:
            evt_nannpc_set_animtbl_sub(npc, dai3_animtbl);
            npc->workA4 = 1;
            break;
    }
}
