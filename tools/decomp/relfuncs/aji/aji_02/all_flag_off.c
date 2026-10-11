// include: stdio.h
// decl: void mapGrpFlagOn(const char* name, u32 flags);
// decl: void mapGrpFlagOff(const char* name, u32 flags);
// decl: void hitGrpAttrOn(const char* name, u32 flags);
// decl: void hitGrpAttrOff(const char* name, u32 flags);
// proto: USER_FUNC(all_flag_off);
USER_FUNC(all_flag_off) {
    char name[64];
    s32 i;

    for (i = 1; i <= 30; i++) {
        sprintf(name, "hikaru_%02d", i);
        mapGrpFlagOn(name, 1);
        sprintf(name, "nashi_%02d", i);
        mapGrpFlagOn(name, 1);
        sprintf(name, "A_hikaru_%02d", i);
        hitGrpAttrOff(name, 0x800);
    }
    return EVT_RETURN_DONE;
}
