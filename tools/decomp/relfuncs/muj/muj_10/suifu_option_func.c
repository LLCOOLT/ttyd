// include: manager/evtmgr_cmd.h
// decl: typedef struct NanNpc { u8 field_0x0[0x18]; Vec pos; u8 field_0x24[0x30 - 0x24]; Vec basePos; u8 field_0x3C[0x50 - 0x3C]; OSTime time; u8 field_0x58[0x68 - 0x58]; s32 state; s32 duration; u8 field_0x70[0xBF - 0x70]; u8 alpha; } NanNpc;
// decl: typedef struct NanNpcWork { NanNpc* entries; } NanNpcWork;
// decl: extern NanNpcWork* nanNPCWork;
// proto: USER_FUNC(suifu_option_func);
USER_FUNC(suifu_option_func) {
    f32 y = evtGetFloat(event, event->args[0]);
    NanNpcWork* wp = nanNPCWork;
    s32 i;

    for (i = 0; i < 95; i++) {
        // "- -y" reproduces the operand order of the original fadds
        wp->entries[i].pos.y = wp->entries[i].basePos.y - -y;
    }
    return EVT_RETURN_DONE;
}
