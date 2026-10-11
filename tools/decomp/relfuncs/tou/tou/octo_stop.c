// include: manager/evtmgr_cmd.h
// include: manager/evtmgr.h
// include: driver/npcdrv.h
// proto: USER_FUNC(octo_stop);
USER_FUNC(octo_stop) {
    NpcEntry* npc = npcNameToPtr_NoAssert("\203I\203N\203g\201[\203\213");

    if (npc != NULL) {
        evtStopID(npc->regularEvtId);
        npc->prevPosition = (Vec){80.0f, 0.0f, 85.0f};
        npc->position = npc->prevPosition;
        npc->direction = 270.0f;
    }
    return EVT_RETURN_DONE;
}
