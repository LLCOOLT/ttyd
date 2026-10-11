// include: driver/npcdrv.h
// proto: USER_FUNC(wait_landon);
USER_FUNC(wait_landon) {
    // マッキノ
    NpcEntry* npc = npcNameToPtr("\203}\203b\203L\203m");

    if (!(npc->flags & 0x10) || (u32)npc->field_0x300 != 0) {
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}
