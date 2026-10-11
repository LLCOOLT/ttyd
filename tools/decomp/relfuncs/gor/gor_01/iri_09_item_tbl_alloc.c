// include: manager/evtmgr_cmd.h
// include: memory.h
// decl: s32* iri_09_item_tbl;
// proto: USER_FUNC(iri_09_item_tbl_alloc);
USER_FUNC(iri_09_item_tbl_alloc) {
    iri_09_item_tbl = _mapAlloc((evtGetValue(event, event->args[0]) + 1) * sizeof(s32));
    return EVT_RETURN_DONE;
}
