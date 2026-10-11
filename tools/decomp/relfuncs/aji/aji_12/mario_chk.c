// include: mario/mario.h
// include: party.h
// include: driver/hitdrv.h
// include: stdio.h
// include: string.h
// decl: void mapGrpFlagOn(const char* name, u32 flags);
// decl: void mapGrpFlagOff(const char* name, u32 flags);
// decl: void hitGrpAttrOn(const char* name, u32 flags);
// decl: void hitGrpAttrOff(const char* name, u32 flags);
// decl: int sscanf(const char* s, const char* format, ...);
// proto: USER_FUNC(mario_chk);
USER_FUNC(mario_chk) {
    s32 n;
    char name[256];
    MarioWork* mario = marioGetPtr();
    PartyEntry* party;
    HitEntry* hit;
    s32 i;
    s32 j;

    if (isFirstCall) {
        event->userdata[0] = 0;
        event->userdata[1] = 0;
    }
    if (evtGetValue(NULL, GSWF(4183))) {
        return EVT_RETURN_DONE;
    }
    for (i = 1; i <= 44; i++) {
        sprintf(name, "hikaru_%02d", i);
        mapGrpFlagOn(name, 1);
        sprintf(name, "nashi_%02d", i);
        mapGrpFlagOff(name, 1);
    }
    for (i = 0; i < 50; i++) {
        hitGrpAttrOn((const char*)hit_list[i], 0x800);
    }
    party = partyGetPtr(0);
    if (party != NULL && party->currentMemberId == 4 && (party->flags & 0x100)) {
        hit = mario->hitobjStandOn;
        if (hit == NULL) {
            hit = mario->hitobjJumpFrom;
        }
    } else {
        hit = (HitEntry*)mario->field_0x1F8;
    }
    if (hit == NULL) {
        mapGrpFlagOff("hikaru_01", 1);
        mapGrpFlagOn("nashi_01", 1);
        hitGrpAttrOff("A_hikaru_01", 0x800);
        event->userdata[2] = 0;
    } else if (strncmp(hitGetName(hit), "A_hikaru_", strlen("A_hikaru_")) != 0) {
        mapGrpFlagOff("hikaru_01", 1);
        mapGrpFlagOn("nashi_01", 1);
        hitGrpAttrOff("A_hikaru_01", 0x800);
        event->userdata[2] = 0;
    } else if (strcmp(hitGetName(hit), "A_hikaru_01") == 0 && event->userdata[2] == 0) {
        event->userdata[2] = 1;
        event->userdata[0] = 0;
        event->userdata[1] = 0;
    }
    n = 0;
    j = event->userdata[0];
    if (j >= 50) {
        j = 49;
    }
    sscanf((const char*)hit_list[j], "A_hikaru_%02d", &n);
    sprintf(name, "hikaru_%02d", n);
    mapGrpFlagOff(name, 1);
    sprintf(name, "nashi_%02d", n);
    mapGrpFlagOn(name, 1);
    sprintf(name, "A_hikaru_%02d", n);
    hitGrpAttrOff(name, 0x800);
    j++;
    if (j >= 50) {
        j = 49;
    }
    sscanf((const char*)hit_list[j], "A_hikaru_%02d", &n);
    sprintf(name, "hikaru_%02d", n);
    mapGrpFlagOff(name, 1);
    sprintf(name, "nashi_%02d", n);
    mapGrpFlagOn(name, 1);
    sprintf(name, "A_hikaru_%02d", n);
    hitGrpAttrOff(name, 0x800);
    event->userdata[1]++;
    if (event->userdata[1] > (event->userdata[2] == 0 ? 20 : 60)) {
        event->userdata[1] = 0;
        event->userdata[0]++;
        if (event->userdata[0] > 50) {
            event->userdata[0] = 0;
        }
    }
    return EVT_RETURN_BLOCK;
}
