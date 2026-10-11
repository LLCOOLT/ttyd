// include: manager/evtmgr_cmd.h
// include: string.h
// decl: void mapGrpFlagOn(const char* name, u32 flags);
// decl: void mapGrpFlagOff(const char* name, u32 flags);
// proto: USER_FUNC(stonechangertn);
USER_FUNC(stonechangertn) {
    const char* name = (const char*)evtGetValue(event, event->args[0]);

    if (!strcmp(name, "S_i01_sui_ao")) {
        mapGrpFlagOff("S_i01_sui_ao", 1);
        mapGrpFlagOn("S_i01_sui_aka", 1);
    } else if (!strcmp(name, "S_i01_sui_aka")) {
        mapGrpFlagOn("S_i01_sui_ao", 1);
        mapGrpFlagOff("S_i01_sui_aka", 1);
    }
    return EVT_RETURN_DONE;
}
