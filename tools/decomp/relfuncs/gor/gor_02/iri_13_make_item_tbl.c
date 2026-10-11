// include: manager/evtmgr_cmd.h
// include: memory.h
// include: mario/mario_pouch.h
// decl: s32* iri_13_item_tbl;
// proto: USER_FUNC(iri_13_make_item_tbl);
USER_FUNC(iri_13_make_item_tbl) {
    s32 count = pouchCheckItem(0x6B);

    if (count > 0) {
        iri_13_item_tbl = _mapAlloc((count + 1) * sizeof(s32));
    }
    return EVT_RETURN_DONE;
}
