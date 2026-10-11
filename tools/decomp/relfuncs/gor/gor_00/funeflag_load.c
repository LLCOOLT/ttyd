// decl: void mapGrpFlagOn(const char* name, u32 flags);
// decl: void mapGrpFlagOff(const char* name, u32 flags);
// proto: USER_FUNC(funeflag_load);
USER_FUNC(funeflag_load) {
    mapGrpFlagOff("S_fune_b", 1);
    mapGrpFlagOn("S_fune_b", event->lwData[8]);
    mapGrpFlagOff("S_fune_c", 1);
    mapGrpFlagOn("S_fune_c", event->lwData[9]);
    return EVT_RETURN_DONE;
}
