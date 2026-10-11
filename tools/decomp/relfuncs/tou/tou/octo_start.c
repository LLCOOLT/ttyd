// include: manager/evtmgr_cmd.h
// include: manager/evtmgr.h
// include: driver/npcdrv.h
// proto: USER_FUNC(octo_start);
USER_FUNC(octo_start) {
    NpcEntry* npc = npcNameToPtr_NoAssert("\203I\203N\203g\201[\203\213");

    if (npc != NULL) {
        evtStartID(npc->regularEvtId);
    }
    return EVT_RETURN_DONE;
}
