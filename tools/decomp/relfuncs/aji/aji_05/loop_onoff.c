// include: stdio.h
// decl: void mapGrpFlagOn(const char* name, u32 flags);
// decl: void mapGrpFlagOff(const char* name, u32 flags);
// proto: USER_FUNC(loop_onoff);
USER_FUNC(loop_onoff) {
    char name[64];
    s32 i;

    if (isFirstCall) {
        event->userdata[0] = 0;
        event->userdata[1] = 0;
        event->userdata[2] = 0;
    }
    // light the panels up one after another, twice
    event->userdata[0]++;
    if (event->userdata[0] > 2) {
        event->userdata[0] = 0;
        event->userdata[1]++;
        if (event->userdata[1] >= 25) {
            event->userdata[1] = 0;
            event->userdata[2]++;
            if (event->userdata[2] > 1) {
                return EVT_RETURN_DONE;
            }
        }
    }
    for (i = 1; i < 25; i++) {
        if (i == event->userdata[1]) {
            sprintf(name, "hikaru_%02d", i);
            mapGrpFlagOff(name, 1);
            sprintf(name, "nashi_%02d", i);
            mapGrpFlagOn(name, 1);
        } else {
            sprintf(name, "hikaru_%02d", i);
            mapGrpFlagOn(name, 1);
            sprintf(name, "nashi_%02d", i);
            mapGrpFlagOff(name, 1);
        }
    }
    return EVT_RETURN_BLOCK;
}
