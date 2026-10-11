// include: memory.h
// proto: USER_FUNC(free_tbl);
USER_FUNC(free_tbl) {
    _mapFree(tbl);
    tbl = NULL;
    return EVT_RETURN_DONE;
}
