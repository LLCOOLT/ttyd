// include: mario/mariost.h
// include: system.h
// include: dolphin/os.h
// include: dolphin/mtx.h
// decl: typedef struct NanNpc { u8 field_0x0[0x18]; Vec pos; Vec posA; Vec posB; u8 field_0x3C[0x50 - 0x3C]; OSTime time; u8 field_0x58[0x60 - 0x58]; f32 dir; void (*func)(struct NanNpc*); s32 state; s32 work6C; s32 work70; s32 work74; f32 work78; f32 work7C; f32 work80; u8 field_0x84[0x88 - 0x84]; Vec posC; u8 field_0x94[0xA4 - 0x94]; s32 workA4; s32 workA8; u8 field_0xAC[0xC0 - 0xAC]; } NanNpc;
// decl: typedef struct NanNpcWork { NanNpc* entries; u8 field_0x4[0xC - 0x4]; s32 count; } NanNpcWork;
// decl: extern NanNpcWork* nanNPCWork;
// decl: extern Vec suifu100kaidanDOWN[];
// decl: extern Vec suifu100kaidanUP[];
// proto: void suifu100taikikan_seq01(NanNpc* npc);
void suifu100taikikan_seq01(NanNpc* npc) {
    Vec v;
    Vec d;
    s32 elapsed;
    s32 duration;

    switch (npc->state) {
        case 0:
            npc->posA = npc->pos;
            npc->posA.x = -180.0f + irand(50);
            npc->work78 = 140.0f + irand(120);
            npc->dir = 270.0f;
            npc->work70 = 1;
            npc->state = 100;
            break;
        case 1:
            npc->posA = npc->pos;
            npc->posA.x = -255.0f + irand(30);
            npc->posA.z = -230.0f + irand(30);
            npc->work70 = 10;
            npc->state = 100;
            break;
        case 10:
            npc->posA = npc->pos;
            npc->posA.z = -350.0f + irand(50);
            npc->work70 = 20;
            npc->state = 100;
            break;
        case 20:
            npc->posA = npc->pos;
            npc->posA.x += 520.0f + irand(50);
            npc->dir = 90.0f;
            npc->work70 = 30;
            npc->state = 100;
            break;
        case 30:
            npc->posA = suifu100kaidanDOWN[irand(3)];
            npc->work70 = 40;
            npc->state = 100;
            break;
        case 40:
            npc->posA = suifu100kaidanUP[irand(3)];
            npc->dir = 270.0f;
            npc->work70 = 50;
            npc->state = 100;
            break;
        case 50:
            npc->posA = npc->pos;
            npc->posA.x = -30.0f + irand(60);
            npc->work70 = 60;
            npc->state = 100;
            break;
        case 60:
            npc->posA = npc->pos;
            npc->posA.z -= 100.0f;
            npc->work70 = 99;
            npc->state = 100;
            break;
        case 99:
            npc->pos = (Vec){0.0f, -1000.0f, 0.0f};
            break;
        case 100:
            npc->time = gp->renderTime;
            npc->posB = npc->pos;
            npc->state = 101;
        case 101:
            PSVECSubtract(&npc->posA, &npc->posB, &v);
            duration = 1000.0f * PSVECMag(&v) / npc->work78;
            elapsed = OSTicksToMilliseconds((u32)gp->renderTime - (u32)npc->time);
            PSVECScale(&v, &d, (f32)elapsed / (f32)duration);
            if (elapsed < duration) {
                PSVECAdd(&npc->posB, &d, &npc->pos);
            } else {
                npc->pos = npc->posA;
                npc->state = npc->work70;
            }
            break;
    }
}
