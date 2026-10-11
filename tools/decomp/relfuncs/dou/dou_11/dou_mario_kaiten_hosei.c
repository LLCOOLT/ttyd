// include: mario/mario.h
// include: driver/hitdrv.h
// include: driver/mapdrv.h
// include: system.h
// include: string.h
// include: dolphin/mtx.h
// decl: BOOL hitIsGroup(HitEntry* target, HitEntry* group);
// decl: double sin(double x);
// decl: double cos(double x);
// proto: USER_FUNC(dou_mario_kaiten_hosei);
USER_FUNC(dou_mario_kaiten_hosei) {
    const char* name = (const char*)evtGetValue(event, event->args[0]);
    HitEntry* hit = hitNameToPtr(name);
    MarioWork* mario = marioGetPtr();
    Mtx m;
    Vec v;
    f32 angle;
    f32 delta;
    f32 dist;
    f32 rot;

    if (isFirstCall) {
        *(f32*)&event->userdata[1] = 0.0f;
        event->userdata[2] = 0;
    }
    if (mario->hitobjStandOn == NULL) {
        *(f32*)&event->userdata[1] = 0.0f;
        event->userdata[2] = 0;
        return EVT_RETURN_BLOCK;
    }
    if (hitIsGroup(mario->hitobjStandOn, hit)) {
        v = (Vec){0.0f, 1.0f, 0.0f};
        mtxGetRotationElement(hit->mapObj->unkAC, m, 'x', 'y');
        PSMTXMultVec(m, &v, &v);
        angle = angleABf(0.0f, 0.0f, v.x, v.y);
        delta = angle - *(f32*)&event->userdata[1];
        hitObjGetPos(name, &v);
        dist = distABf(mario->position.x, mario->position.y, v.x, v.y);
        rot = angleABf(v.x, v.y, mario->position.x, mario->position.y);
        if ((HitEntry*)event->userdata[2] != NULL && strcmp(hit->joint->name, ((HitEntry*)event->userdata[2])->joint->name) == 0) {
            rot = 6.2831855f * (rot + delta) / 360.0f;
            mario->unk174.x = (v.x + dist * (f32)sin(rot)) - mario->position.x;
            mario->unk174.y = (v.y - dist * (f32)cos(rot)) - mario->position.y;
        }
        *(f32*)&event->userdata[1] = angle;
        event->userdata[2] = (s32)hit;
    }
    return EVT_RETURN_BLOCK;
}
