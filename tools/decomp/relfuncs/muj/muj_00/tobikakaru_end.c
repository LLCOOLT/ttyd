// include: manager/evtmgr_cmd.h
// decl: typedef struct TobiWork { Vec pos; s32 type; } TobiWork;
// decl: typedef struct NanNpc { u8 field_0x0[0x18]; Vec pos; Vec start; Vec target; u8 field_0x3C[0x50 - 0x3C]; OSTime time; u8 field_0x58[0x60 - 0x58]; f32 dir; void (*func)(struct NanNpc*); s32 state; s32 duration; s32 nextState; u8 field_0x74[0x78 - 0x74]; f32 vy; f32 dy; u8 field_0x80[0xA0 - 0x80]; TobiWork* work; s32 angle; s32 radius; u8 field_0xAC[0xC0 - 0xAC]; } NanNpc;
// decl: typedef struct NanNpcWork { NanNpc* entries; } NanNpcWork;
// decl: extern NanNpcWork* nanNPCWork;
// decl: void evt_nannpc_set_animtbl_sub(NanNpc* npc, void* animtbl);
// proto: USER_FUNC(tobikakaru_end);
USER_FUNC(tobikakaru_end) {
    NanNpcWork* wp = nanNPCWork;
    NanNpc* npc;
    s32 i;

    for (i = 0; i < 95; i++) {
        npc = &wp->entries[i + 10];
        npc->func = NULL;
        evt_nannpc_set_animtbl_sub(npc, suifu_animtbl);
    }
    for (i = 0; i < 100; i++) {
        wp->entries[i + 105].func = NULL;
    }
    for (i = 0; i < 100; i++) {
        npc = &wp->entries[i + 205];
        npc->func = NULL;
        evt_nannpc_set_animtbl_sub(npc, dai3_animtbl);
    }
    return EVT_RETURN_DONE;
}
