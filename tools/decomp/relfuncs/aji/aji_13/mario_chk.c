// include: mario/mario.h
// include: party.h
// include: driver/hitdrv.h
// include: driver/mapdrv.h
// include: system.h
// include: string.h
// include: dolphin/mtx.h
// decl: BOOL hitIsGroup(HitEntry* target, HitEntry* group);
// decl: void* _mapAlloc(u32 size);
// decl: double sin(double x);
// decl: double cos(double x);
// decl: typedef struct { Vec pos; Vec delta; } BeltWork;
// proto: USER_FUNC(mario_chk);
USER_FUNC(mario_chk) {
    BeltWork* work;
    s32 i;
    f32 angle;
    f32 delta;
    f32 dist;
    f32 rot;

    if (isFirstCall) {
        work = _mapAlloc(sizeof(BeltWork) * 13);
        for (i = 0; i < 13; i++) {
            work[i].pos = (Vec){0.0f, 0.0f, 0.0f};
            work[i].delta = (Vec){0.0f, 0.0f, 0.0f};
        }
        event->userdata[0] = (s32)work;
        *(f32*)&event->userdata[1] = 0.0f;
        event->userdata[2] = 0;
    }
    work = (BeltWork*)event->userdata[0];
    for (i = 0; i < 13; i++) {
        HitEntry* hit = hitNameToPtr((const char*)name_tbl[i]);
        if (hit != NULL && hit->mapObj != NULL) {
            Vec pos = (Vec){hit->mapObj->unkAC[0][3], hit->mapObj->unkAC[1][3], hit->mapObj->unkAC[2][3]};
            PSVECSubtract(&pos, &work[i].pos, &work[i].delta);
            work[i].pos = pos;
        }
    }
    for (i = 0; i < 13; i++) {
        HitEntry* hit = hitNameToPtr((const char*)name_tbl[i]);
        MarioWork* mario = marioGetPtr();
        if (hit != NULL && mario != NULL && mario->hitobjStandOn != NULL && hitIsGroup(mario->hitobjStandOn, hit)) {
            mario->unk174.x = 10.0f * work[i].delta.x;
            mario->unk174.z = 10.0f * work[i].delta.z;
            break;
        }
    }
    for (i = 0; i < 13; i++) {
        HitEntry* hit = hitNameToPtr((const char*)name_tbl[i]);
        PartyEntry* party = partyGetPtr(0);
        if (hit != NULL && party != NULL && party->field_138 != NULL && hitIsGroup(party->field_138, hit)) {
            party->field_AC = 10.0f * work[i].delta.x;
            party->field_B4 = 10.0f * work[i].delta.z;
            break;
        }
    }
    if (evtGetValue(event, GSW(0)) >= 370) {
        MarioWork* mario = marioGetPtr();
        PartyEntry* party = partyGetPtr(0);
        if (mario != NULL && mario->hitobjStandOn != NULL && hitIsGroup(mario->hitobjStandOn, hitNameToPtr("A_bel"))) {
            mario->unk174.x = 0.6f;
        }
        if (party != NULL && party->field_144 != NULL && hitIsGroup(party->field_138, hitNameToPtr("A_bel"))) {
            party->field_AC = 0.6f;
        }
    }
    for (i = 0; i < 6; i++) {
        HitEntry* hit = hitNameToPtr((const char*)name_tbl2[i]);
        MarioWork* mario = marioGetPtr();
        if (hit == NULL) {
            continue;
        }
        if (mario->hitobjStandOn == NULL) {
            *(f32*)&event->userdata[1] = 0.0f;
            event->userdata[2] = 0;
            continue;
        }
        if (hitIsGroup(mario->hitobjStandOn, hit)) {
            Vec v = (Vec){0.0f, 1.0f, 0.0f};
            Mtx m;
            mtxGetRotationElement(hit->mapObj->unkAC, m, 'x', 'y');
            PSMTXMultVec(m, &v, &v);
            angle = angleABf(0.0f, 0.0f, v.x, v.y);
            delta = angle - *(f32*)&event->userdata[1];
            hitObjGetPos((const char*)name_tbl2[i], &v);
            dist = distABf(mario->position.x, mario->position.y, v.x, v.y);
            rot = angleABf(v.x, v.y, mario->position.x, mario->position.y);
            if ((HitEntry*)event->userdata[2] != NULL && strcmp(hit->joint->name, ((HitEntry*)event->userdata[2])->joint->name) == 0) {
                rot = 6.2831855f * (rot + delta) / 360.0f;
                mario->unk174.x = (v.x + dist * (f32)sin(rot)) - mario->position.x;
                mario->unk174.y = (v.y - dist * (f32)cos(rot)) - mario->position.y;
            }
            *(f32*)&event->userdata[1] = angle;
            event->userdata[2] = (s32)hit;
            break;
        }
    }
    return EVT_RETURN_BLOCK;
}
