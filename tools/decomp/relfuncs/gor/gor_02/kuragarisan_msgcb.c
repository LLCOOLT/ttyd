// include: driver/npcdrv.h
// include: driver/msgdrv.h
// proto: void kuragarisan_msgcb(s32 type, void* param);
void kuragarisan_msgcb(s32 type, void* param) {
    u8* msg = *(u8**)param;
    NpcEntry* npc;

    switch (type) {
        case 3:
            if (*(u16*)(msg + 8) == 1) {
                npc = npcNameToPtr("\203N\203\211\203K\203\212\202\263\202\361");
                npc->direction = 90.0f;
            }
            break;
    }
}
