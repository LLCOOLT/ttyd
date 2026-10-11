// include: driver/npcdrv.h
// proto: USER_FUNC(gravity_scale);
USER_FUNC(gravity_scale) {
    NpcEntry* npc = npcNameToPtr((const char*)evtGetValue(event, event->args[0]));

    npc->jumpGravity = 0.1f;
    return EVT_RETURN_DONE;
}
