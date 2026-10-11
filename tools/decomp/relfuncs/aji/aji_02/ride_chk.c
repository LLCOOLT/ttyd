// include: stdio.h
// decl: void mapGrpFlagOn(const char* name, u32 flags);
// decl: void mapGrpFlagOff(const char* name, u32 flags);
// include: mario/mario.h
// include: party.h
// include: driver/hitdrv.h
// include: string.h
// proto: USER_FUNC(ride_chk);
USER_FUNC(ride_chk) {
    static s32 onoff[30];
    char hitName[64];
    char name[64];
    MarioWork* mario = marioGetPtr();
    PartyEntry* party = partyGetPtr(0);
    s32 i;
    HitEntry* hit;

    if (isFirstCall) {
        memset(onoff, 0, sizeof(onoff));
    }
    if (party != NULL && party->currentMemberId == 4 && (party->flags & 0x100)) {
        hit = mario->hitobjStandOn;
        if (hit == NULL) {
            hit = mario->hitobjJumpFrom;
        }
    } else {
        hit = (HitEntry*)mario->field_0x1F8;
    }
    // panels stay lit for 30 frames after being touched
    for (i = 0; i < 30; i++) {
        if (hit != NULL) {
            sprintf(hitName, "A_hikaru_%02d", i + 1);
            if (strcmp(hit->joint->name, hitName) == 0) {
                onoff[i] = 30;
            }
        }
    }
    for (i = 0; i < 30; i++) {
        if (onoff[i] > 0) {
            onoff[i]--;
        }
        if (onoff[i] != 0) {
            sprintf(name, "hikaru_%02d", i + 1);
            mapGrpFlagOff(name, 1);
            sprintf(name, "nashi_%02d", i + 1);
            mapGrpFlagOn(name, 1);
        } else {
            sprintf(name, "hikaru_%02d", i + 1);
            mapGrpFlagOn(name, 1);
            sprintf(name, "nashi_%02d", i + 1);
            mapGrpFlagOff(name, 1);
        }
    }
    if (evtGetValue(event, GSW(0)) >= 362) {
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}
