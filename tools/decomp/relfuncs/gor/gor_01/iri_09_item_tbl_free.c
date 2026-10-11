// include: manager/evtmgr_cmd.h
// include: memory.h
// decl: s32* iri_09_item_tbl;
// proto: USER_FUNC(iri_09_item_tbl_free);
USER_FUNC(iri_09_item_tbl_free) {
    _mapFree(iri_09_item_tbl);
    iri_09_item_tbl = NULL;
    return EVT_RETURN_DONE;
}
