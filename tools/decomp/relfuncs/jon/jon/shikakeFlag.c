// include: driver/npcdrv.h
// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(shikakeFlag);
USER_FUNC(shikakeFlag) {
    s32 type = evtGetValue(event, event->args[0]);
    NpcEntry* npc = npcNameToPtr("\223G");

    switch (type) {
        case 0:
            npc->battleInfo.field_4 |= 0x4000000;
            break;
        case 1:
            npc->battleInfo.field_4 |= 0x2000000;
            break;
        case 2:
            npc->battleInfo.field_4 |= 0x1000000;
            break;
        case 3:
            npc->battleInfo.field_4 |= 0x100;
            break;
    }
    return EVT_RETURN_DONE;
}
