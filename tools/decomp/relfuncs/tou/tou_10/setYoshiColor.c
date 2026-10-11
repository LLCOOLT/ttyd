// include: mario/mariost.h
// include: mario/mario_pouch.h
// include: driver/swdrv.h
// proto: USER_FUNC(setYoshiColor);
USER_FUNC(setYoshiColor) {
    OSTime start;
    s32 i;
    s32 minutes;

    // the time the Yoshi egg was received
    for (i = 0; i < 8; i++) {
        ((u8*)&start)[i] = swByteGet(i + 508);
    }
    minutes = (s32)OSTicksToSeconds(gp->retraceLocalTime - start) / 60;
    minutes %= 20;
    if (minutes <= 5) {
        pouchSetPartyColor(4, 0);
    } else if (minutes <= 8) {
        pouchSetPartyColor(4, 1);
    } else if (minutes <= 11) {
        pouchSetPartyColor(4, 2);
    } else if (minutes <= 14) {
        pouchSetPartyColor(4, 3);
    } else if (minutes <= 17) {
        pouchSetPartyColor(4, 4);
    } else if (minutes <= 18) {
        pouchSetPartyColor(4, 5);
    } else {
        pouchSetPartyColor(4, 6);
    }
    return EVT_RETURN_DONE;
}
