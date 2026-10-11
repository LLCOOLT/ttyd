// include: mario/mariost.h
// include: mario/mario.h
// include: system.h
// include: dolphin/os.h
// decl: typedef struct NanNpc { u8 field_0x0[0x18]; Vec pos; Vec posA; Vec posB; u8 field_0x3C[0x50 - 0x3C]; OSTime time; u8 field_0x58[0x60 - 0x58]; f32 dir; void (*func)(struct NanNpc*); s32 state; s32 work6C; s32 work70; s32 work74; f32 work78; f32 work7C; f32 work80; u8 field_0x84[0x88 - 0x84]; Vec posC; u8 field_0x94[0xA4 - 0x94]; s32 workA4; s32 workA8; u8 field_0xAC[0xC0 - 0xAC]; } NanNpc;
// decl: typedef struct NanNpcWork { NanNpc* entries; u8 field_0x4[0xC - 0x4]; s32 count; } NanNpcWork;
// decl: extern NanNpcWork* nanNPCWork;
// decl: void evt_nannpc_set_animtbl_sub(NanNpc* npc, void* animtbl);
// proto: void gundan1000tai_seq00(NanNpc* npc);
void gundan1000tai_seq00(NanNpc* npc) {
    MarioWork* mario = marioGetPtr();
    s32 wait;
    f32 dist;
    f32 speed;
    f32 angle;

    switch (npc->state) {
        case 0:
            npc->time = gp->renderTime;
            wait = (npc->work74 % 6) * 500;
            npc->work6C = wait + irand(500);
            npc->state++;
        case 1:
            if ((s32)OSTicksToMilliseconds((u32)gp->renderTime - (u32)npc->time) > npc->work6C) {
                npc->state++;
            }
            break;
        case 2:
            dist = distABf(npc->pos.x, npc->pos.z, npc->posA.x, npc->posA.z);
            angle = angleABf(npc->pos.x, npc->pos.z, npc->posA.x, npc->posA.z);
            speed = dist / 2.0f + (irand(180) + 180);
            speed = sysFrame2SecFloat(speed / 2.0f);
            npc->work78 = speed;
            npc->work7C = angle;
            npc->work70 = dist / speed;
            npc->work6C = 0;
            npc->workA4 = 0;
            evt_nannpc_set_animtbl_sub(npc, dai3_run_animtbl);
            npc->state++;
        case 3:
            movePos(&npc->pos.x, &npc->pos.z, npc->work78, npc->work7C);
            npc->work6C++;
            if (npc->work6C >= npc->work70) {
                npc->pos.x = npc->posA.x;
                npc->pos.z = npc->posA.z;
                npc->workA4 = 1;
                evt_nannpc_set_animtbl_sub(npc, dai3_animtbl);
                npc->state++;
            }
            break;
        case 4:
            npc->posB = npc->pos;
            break;
    }
}
