// include: pmario_sound.h
// decl: typedef struct UsuCbInfo { u8 field_0x0[0x8]; u16 field_0x8; } UsuCbInfo;
// proto: void kpa_stg5_009_7_cb(s32 type, UsuCbInfo** param);
void kpa_stg5_009_7_cb(s32 type, UsuCbInfo** param) {
    UsuCbInfo* info = *param;

    switch (type) {
        case 3:
            if (info->field_0x8 == 1) {
                psndBGMOn(0x201, "BGM_FF_GET_ITEM1");
            }
            break;
    }
}
