// decl: EventEntry* xevt;
// decl: char xmemo[20];
// proto: USER_FUNC(pose_check_evt_run);
USER_FUNC(pose_check_evt_run) {
    xevt = evtEntryType(maiframeanimcheck, event->priority, 0, event->type);
    xevt->unitId = event->unitId;
    xevt->ownerNPC = event->ownerNPC;
    xmemo[0] = 0;
    xevt->lwData[0] = (s32)xmemo;
    xevt->uwBase = event->uwBase;
    xevt->ufBase = event->ufBase;
    return EVT_RETURN_DONE;
}
