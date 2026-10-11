// include: driver/npcdrv.h
// proto: USER_FUNC(npc_dead);
USER_FUNC(npc_dead) {
    // チョロボン
    npcGroupDead(npcNameToPtr("\x83\x60\x83\x87\x83\x8D\x83\x7B\x83\x93"), FALSE);
    return EVT_RETURN_DONE;
}
