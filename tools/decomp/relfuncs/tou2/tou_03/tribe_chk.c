// include: driver/npcdrv.h
// include: manager/evtmgr_cmd.h
// include: string.h
// proto: USER_FUNC(tribe_chk);
USER_FUNC(tribe_chk) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    const char* tribe = (const char*)evtGetValue(event, args[1]);

    if (strcmp(npcNameToPtr(name)->tribe->nameJp, tribe) == 0) {
        evtSetValue(event, args[2], 1);
    } else {
        evtSetValue(event, args[2], 0);
    }
    return EVT_RETURN_DONE;
}
