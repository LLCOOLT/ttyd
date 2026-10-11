// include: manager/evtmgr_cmd.h
// include: stdio.h
// include: driver/bgdrv.h
// include: mario/mariost.h
// proto: USER_FUNC(evt_set_bgtpl);
USER_FUNC(evt_set_bgtpl) {
    char path[64];
    const char* name = (const char*)evtGetValue(event, event->args[0]);

    if (name == NULL) {
        name = gp->currentMapName;
    }
    sprintf(path, "./b/%s.tpl", name);
    bgReEntry(path);
    return EVT_RETURN_DONE;
}
