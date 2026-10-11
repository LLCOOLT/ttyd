// include: mario/mario.h
// include: driver/hitdrv.h
// include: driver/mapdrv.h
// include: system.h
// include: dolphin/mtx.h
// proto: USER_FUNC(hit_move);
double sin(double x);
double cos(double x);

USER_FUNC(hit_move) {
    MarioWork* mario = marioGetPtr();
    HitEntry* hit = mario->hitobjStandOn;
    Mtx rot;
    Vec dir = {0.0f, 0.0f, -1.0f};
    Vec pos;
    f32 delta;
    f32 angle;
    f32 dist;
    f32 theta;

    if (isFirstCall) {
        event->userdata[0] = 0;
        event->userdata[1] = 0;
    }
    if (hit == NULL) {
        event->userdata[0] = 0;
        event->userdata[1] = 0;
        return EVT_RETURN_BLOCK;
    }
    if (!(hit->flags & 0x30)) {
        event->userdata[0] = 0;
        event->userdata[1] = 0;
        return EVT_RETURN_BLOCK;
    }
    mtxGetRotationElement(hit->worldMtx, rot, 'x', 'z');
    PSMTXMultVec(rot, &dir, &dir);
    angle = angleABf(0.0f, 0.0f, dir.x, dir.z);
    delta = angle - event->userdataf[1];
    if (event->userdata[0] == 0) {
        event->userdata[0] = 1;
        event->userdataf[1] = angle;
        return EVT_RETURN_BLOCK;
    }
    hitObjGetPos(hit->joint->name, &pos);
    dist = distABf(mario->position.x, mario->position.z, pos.x, pos.z);
    theta = angleABf(pos.x, pos.z, mario->position.x, mario->position.z);
    theta = 6.2831855f * (theta + delta) / 360.0f;
    mario->unk174.x = pos.x + dist * (f32)sin(theta) - mario->position.x;
    mario->unk174.z = pos.z - dist * (f32)cos(theta) - mario->position.z;
    event->userdataf[1] = angle;
    return EVT_RETURN_BLOCK;
}
