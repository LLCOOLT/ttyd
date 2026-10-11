// include: manager/evtmgr_cmd.h
// include: memory.h
// decl: s32* iri_13_item_tbl;
// proto: USER_FUNC(iri_13_free_item_tbl);
USER_FUNC(iri_13_free_item_tbl) {
    _mapFree(iri_13_item_tbl);
    iri_13_item_tbl = NULL;
    return EVT_RETURN_DONE;
}
