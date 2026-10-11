// decl: typedef struct KpaCbInfo { u8 field_0x0[0x8]; u16 field_0x8; u8 field_0xA[0x10 - 0xA]; s32 field_0x10; } KpaCbInfo;
// proto: void kpa_stg1_014_2_cb(s32 type, KpaCbInfo** param);
void kpa_stg1_014_2_cb(s32 type, KpaCbInfo** param) {
    KpaCbInfo* info = *param;

    switch (type) {
        case 3:
            if (info->field_0x8 == 2) {
                evtSetValue(NULL, LSWF(1), 1);
            }
            break;
    }
}
