// include: manager/evtmgr_cmd.h
// include: driver/npcdrv.h
// proto: USER_FUNC(chusan1_alwaysencont);
USER_FUNC(chusan1_alwaysencont) {
    s32* args = event->args;
    NpcWork* wp = npcGetWorkPtr();

    if (evtGetValue(event, args[0])) {
        wp->flags |= 1;
    } else {
        wp->flags &= ~1;
    }
    return EVT_RETURN_DONE;
}
