// include: manager/evtmgr_cmd.h
// include: driver/npcdrv.h
// proto: USER_FUNC(slowturnoff_check);
USER_FUNC(slowturnoff_check) {
    return (npcNameToPtr((const char*)evtGetValue(event, event->args[0]))->flags & 0x8000) ? EVT_RETURN_BLOCK : EVT_RETURN_DONE;
}
