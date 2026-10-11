// include: manager/evtmgr_cmd.h
// include: driver/npcdrv.h
// proto: USER_FUNC(set_talk_memory_ry);
USER_FUNC(set_talk_memory_ry) {
    NpcEntry* npc = npcNameToPtr("\203T\203\223\203_\201[\203X");

    npc->field_148 = 270.0f;
    return EVT_RETURN_DONE;
}
