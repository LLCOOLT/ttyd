// include: driver/npcdrv.h
// include: driver/animdrv.h
// decl: typedef struct KpaCbInfo { u8 field_0x0[0x8]; u16 field_0x8; u8 field_0xA[0x10 - 0xA]; s32 field_0x10; } KpaCbInfo;
// proto: void kpa_stg6_012_1_cb(s32 type, KpaCbInfo** param);
void kpa_stg6_012_1_cb(s32 type, KpaCbInfo** param) {
    KpaCbInfo* info = *param;

    switch (type) {
        case 0:
            // ババ
            animPoseSetAnim(npcNameToPtr("\x83\x6F\x83\x6F")->poseId, "A_2B", TRUE);
            break;
        case 5:
            if (info->field_0x10 == 8) {
                // ババ
                animPoseSetAnim(npcNameToPtr("\x83\x6F\x83\x6F")->poseId, "T_1", TRUE);
            }
            break;
    }
}
