// include: manager/evtmgr_cmd.h
// decl: extern s32 kusuri_id[];
// proto: USER_FUNC(kusuri_list_get_no);
USER_FUNC(kusuri_list_get_no) {
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 i;

    for (i = 0; id != kusuri_id[i]; i++) {
    }
    evtSetValue(event, args[1], i + 1);
    return EVT_RETURN_DONE;
}
