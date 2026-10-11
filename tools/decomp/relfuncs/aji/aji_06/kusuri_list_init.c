// include: manager/evtmgr_cmd.h
// decl: extern s32 kusuri_list[];
// proto: USER_FUNC(kusuri_list_init);
USER_FUNC(kusuri_list_init) {
    s32 i;

    for (i = 0; i < 5; i++) {
        kusuri_list[i] = -1;
    }
    return EVT_RETURN_DONE;
}
