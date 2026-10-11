// include: manager/evtmgr_cmd.h
// decl: extern s32 kusuri_id[];
// decl: extern s32 kusuri_list[];
// proto: USER_FUNC(kusuri_list_add);
USER_FUNC(kusuri_list_add) {
    s32 no = evtGetValue(event, event->args[0]);
    s32 i;

    for (i = 0; kusuri_list[i] != -1; i++) {
    }
    kusuri_list[i] = kusuri_id[no - 1];
    return EVT_RETURN_DONE;
}
