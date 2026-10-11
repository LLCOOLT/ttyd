// decl: typedef struct GorCbInfo { u8 field_0x0[0x8]; u16 field_0x8; } GorCbInfo;
// proto: void gor_stg4_018_cb(s32 type, GorCbInfo** param);
void gor_stg4_018_cb(s32 type, GorCbInfo** param) {
    GorCbInfo* info = *param;

    switch (type) {
        case 3:
            if (info->field_0x8 == 1) {
                evtSetValue(NULL, LSWF(6), 1);
            }
            break;
    }
}
