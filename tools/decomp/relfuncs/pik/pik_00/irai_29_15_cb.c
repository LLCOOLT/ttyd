// include: pmario_sound.h
// decl: typedef struct PikCbInfo { u8 field_0x0[0x8]; u16 field_0x8; } PikCbInfo;
// proto: void irai_29_15_cb(s32 type, PikCbInfo** param);
void irai_29_15_cb(s32 type, PikCbInfo** param) {
    PikCbInfo* info = *param;

    if (type == 3 && info->field_0x8 == 1) {
        psndBGMOn(0x200, "BGM_EVT_NOKO_SAIKAI1");
    }
}
