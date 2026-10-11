// decl: void mapGrpFlagOn(const char* name, u32 flags);
// proto: USER_FUNC(funeflag_reset);
USER_FUNC(funeflag_reset) {
    mapGrpFlagOn("S_fune_b", 1);
    mapGrpFlagOn("S_fune_c", 1);
    return EVT_RETURN_DONE;
}
