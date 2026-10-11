// include: mario/mario.h
// include: party.h
// include: driver/hitdrv.h
// include: string.h
// decl: HitEntry* marioSearchUnder(void);
// decl: void mapGrpFlagOn(const char* name, u32 flags);
// decl: void mapGrpFlagOff(const char* name, u32 flags);
// proto: USER_FUNC(under);
USER_FUNC(under) {
    HitEntry* hit;
    BOOL flag;

    marioGetPtr();
    partyGetPtr(0);
    flag = FALSE;
    if (isFirstCall) {
        event->userdata[0] = 0;
    }
    hit = marioSearchUnder();
    if (evtGetValue(event, GF(11))) {
        flag = TRUE;
    }
    if ((hit != NULL && strcmp(hitGetName(hit), "a_home_yuka") == 0) || flag) {
        if (event->userdata[0] == 0 || flag) {
            mapGrpFlagOn("ie_1", 1);
            event->userdata[0] = 1;
        }
    } else if (event->userdata[0] != 0) {
        mapGrpFlagOff("ie_1", 1);
        event->userdata[0] = 0;
    }
    return EVT_RETURN_BLOCK;
}
