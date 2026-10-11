// include: manager/evtmgr_cmd.h
// decl: extern s32 kusuri_tyogo_list[];
// proto: USER_FUNC(peach_evt_seikai_check);
USER_FUNC(peach_evt_seikai_check) {
    s32* args = event->args;
    s32 idx = evtGetValue(event, args[0]);
    s32 v = evtGetValue(event, args[1]);

    if (v == kusuri_tyogo_list[idx]) {
        evtSetValue(event, args[2], 1);
    } else {
        evtSetValue(event, args[2], 0);
    }
    return EVT_RETURN_DONE;
}
