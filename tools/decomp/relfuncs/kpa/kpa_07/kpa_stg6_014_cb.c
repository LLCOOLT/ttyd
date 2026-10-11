// include: driver/npcdrv.h
// include: string.h
// decl: typedef struct KpaCbInfo { u8 field_0x0[0x8]; u16 field_0x8; u8 field_0xA[0x10 - 0xA]; s32 field_0x10; } KpaCbInfo;
// proto: void kpa_stg6_014_cb(s32 type, KpaCbInfo** param);
void kpa_stg6_014_cb(s32 type, KpaCbInfo** param) {
    KpaCbInfo* info = *param;
    NpcEntry* npc;

    switch (type) {
        case 3:
            if (info->field_0x8 == 1) {
                // ブレッドハート
                npc = npcNameToPtr("\x83\x75\x83\x8C\x83\x62\x83\x68\x83\x6E\x81\x5B\x83\x67");
                strcpy(npc->stayAnim, "S_5");
                strcpy(npc->talkAnim, "T_5");
            }
            if (info->field_0x8 == 2) {
                // ブレッドハート
                npc = npcNameToPtr("\x83\x75\x83\x8C\x83\x62\x83\x68\x83\x6E\x81\x5B\x83\x67");
                strcpy(npc->stayAnim, "S_1");
                strcpy(npc->talkAnim, "T_1");
            }
            break;
    }
}
