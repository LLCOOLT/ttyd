// include: stdio.h
// decl: void mapGrpFlagOn(const char* name, u32 flags);
// decl: void mapGrpFlagOff(const char* name, u32 flags);
// decl: void hitGrpAttrOn(const char* name, u32 flags);
// decl: void hitGrpAttrOff(const char* name, u32 flags);
// proto: USER_FUNC(hikaru_on_func);
USER_FUNC(hikaru_on_func) {
    char name[64];
    s32 idx = evtGetValue(event, GW(10));
    // root_data holds {panel list, panel count} for each route
    u8* panels = (u8*)root_data[idx * 2];
    s32 count = root_data[idx * 2 + 1];
    s32 i;

    // light the panels on the chosen route
    for (i = 1; i <= 30; i++) {
        u8* p = panels;
        s32 j;

        for (j = 0; j < count; j++, p++) {
            if (i == *p) {
                sprintf(name, "hikaru_%02d", i);
                mapGrpFlagOff(name, 1);
                sprintf(name, "nashi_%02d", i);
                mapGrpFlagOn(name, 1);
                sprintf(name, "A_hikaru_%02d", i);
                hitGrpAttrOff(name, 0x800);
                break;
            }
        }
        if (j >= count) {
            sprintf(name, "hikaru_%02d", i);
            mapGrpFlagOn(name, 1);
            sprintf(name, "nashi_%02d", i);
            mapGrpFlagOff(name, 1);
            sprintf(name, "A_hikaru_%02d", i);
            hitGrpAttrOn(name, 0x800);
        }
    }
    return EVT_RETURN_DONE;
}
