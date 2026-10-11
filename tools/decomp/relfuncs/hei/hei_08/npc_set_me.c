// include: driver/npcdrv.h
// proto: USER_FUNC(npc_set_me);
USER_FUNC(npc_set_me) {
    // チョロボン
    event->ownerNPC = npcNameToPtr("\x83\x60\x83\x87\x83\x8D\x83\x7B\x83\x93");
    return EVT_RETURN_DONE;
}
