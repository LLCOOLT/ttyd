// include: stdio.h
// decl: void mapGrpFlagOn(const char* name, u32 flags);
// decl: void mapGrpFlagOff(const char* name, u32 flags);
// proto: USER_FUNC(_hikaru_off);
USER_FUNC(_hikaru_off) {
    char name[64];
    s32 i;

    for (i = 1; i < 25; i++) {
        sprintf(name, "hikaru_%02d", i);
        mapGrpFlagOn(name, 1);
        sprintf(name, "nashi_%02d", i);
        mapGrpFlagOn(name, 1);
    }
    return EVT_RETURN_DONE;
}
