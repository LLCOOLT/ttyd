// include: driver/npcdrv.h
// proto: USER_FUNC(setmertn);
USER_FUNC(setmertn) {
    event->ownerNPC = npcNameToPtr((const char*)evtGetValue(event, event->args[0]));
    return EVT_RETURN_DONE;
}
