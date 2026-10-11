// include: manager/evtmgr_cmd.h
// decl: s32* iri_09_item_tbl;
// proto: USER_FUNC(iri_09_item_tbl_make);
USER_FUNC(iri_09_item_tbl_make) {
    s32* args = event->args;
    s32 n = evtGetValue(event, args[0]);
    s32 i;

    for (i = 0; i < n; i++) {
        iri_09_item_tbl[i] = 143;
    }
    iri_09_item_tbl[i] = -1;
    evtSetValue(event, args[1], (s32)iri_09_item_tbl);
    return EVT_RETURN_DONE;
}
