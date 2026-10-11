// include: driver/effdrv.h
// decl: EffectEntry* effFunemizuEntry(s32 type, f32 x, f32 y, f32 z, f32 arg4, f32 arg5);
// decl: void mapObjGetPos(const char* name, Vec* pos);
// decl: f32 distABf(f32 x1, f32 z1, f32 x2, f32 z2);
// decl: f32 angleABf(f32 x1, f32 z1, f32 x2, f32 z2);
// proto: USER_FUNC(kaizoku_fune_eff);
USER_FUNC(kaizoku_fune_eff) {
    EffectEntry* eff;
    Vec pos;
    f32 oldX, oldZ, speed, angle, dir;

    if (isFirstCall) {
        event->userdatap[0] = effFunemizuEntry(0, 0.0f, -1000.0f, 0.0f, 0.0f, 0.0f);
        mapObjGetPos("S_b", &pos);
        event->userdataf[2] = pos.x;
        *(f32*)&event->field_84 = pos.z;
    }
    eff = event->userdatap[0];
    oldX = event->userdataf[2];
    oldZ = *(f32*)&event->field_84;
    mapObjGetPos("S_b", &pos);
    event->userdataf[2] = pos.x;
    *(f32*)&event->field_84 = pos.z;
    speed = distABf(oldX, oldZ, pos.x, pos.z);
    angle = angleABf(oldX, oldZ, pos.x, pos.z);
    if (angle < 180.0f) {
        dir = 1.0f;
    } else {
        dir = -1.0f;
    }
    ((f32*)eff->userdata)[17] = 5.0f;
    ((f32*)eff->userdata)[1] = 140.0f * dir + pos.x;
    ((f32*)eff->userdata)[2] = pos.y - 160.0f;
    ((f32*)eff->userdata)[3] = 40.0f + pos.z;
    ((f32*)eff->userdata)[4] = speed;
    if (angle < 180.0f) {
        ((f32*)eff->userdata)[5] = 135.0f + angle;
    } else {
        ((f32*)eff->userdata)[5] = 45.0f + angle;
    }
    return EVT_RETURN_BLOCK;
}
