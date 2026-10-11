// include: manager/evtmgr_cmd.h
// include: evt/evt_cmd.h
// decl: s32 search_evt_moji(s32 id);
// proto: static USER_FUNC(evt_osreport);
static USER_FUNC(evt_osreport) {
    s32* args = event->args;

    switch (evtGetValue(event, args[0])) {
        case 0:
            evtSetValue(event, args[1], search_evt_moji(evtGetValue(event, GSW(0))));
            break;
    }
    return EVT_RETURN_DONE;
}
