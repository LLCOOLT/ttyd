// include: manager/evtmgr_cmd.h
// include: mario/mario_pouch.h
// decl: s32* iri_13_item_tbl;
// proto: USER_FUNC(iri_13_update_item_tbl);
USER_FUNC(iri_13_update_item_tbl) {
    s32* args = event->args;
    s32 count = pouchCheckItem(0x6B);
    s32 i;

    if (count > 0) {
        for (i = 0; i < count; i++) {
            iri_13_item_tbl[i] = 0x6B;
        }
        iri_13_item_tbl[i] = -1;
    }
    evtSetValue(event, args[0], (s32)iri_13_item_tbl);
    evtSetValue(event, args[1], count);
    return EVT_RETURN_DONE;
}
