// include: memory.h
// proto: USER_FUNC(evt_shuryolight_delete_17_text_10588);
USER_FUNC(evt_shuryolight_delete_17_text_10588) {
    s32 i;

    if (slhp->powerEvt != 0) {
        evtDeleteID(slhp->powerEvt);
        slhp->powerEvt = 0;
    }
    if (slhp->headEvt != 0) {
        evtDeleteID(slhp->headEvt);
        slhp->headEvt = 0;
    }
    if (slhp->tueEvt != 0) {
        evtDeleteID(slhp->tueEvt);
        slhp->tueEvt = 0;
    }
    for (i = 0; i < 5; i++) {
        npcDeleteGroup(slhp->lights[i].npc);
    }
    _mapFree(slhp);
    slhp = NULL;
    return EVT_RETURN_DONE;
}
