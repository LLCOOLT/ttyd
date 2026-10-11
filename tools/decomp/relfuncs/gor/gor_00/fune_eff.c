// include: driver/effdrv.h
// include: mario/mariost.h
// include: system.h
// decl: EffectEntry* effFunemizuEntry(s32 type, f32 x, f32 y, f32 z, f32 arg4, f32 arg5);
// decl: EffectEntry* effWaterDamageN64Entry(s32 type, s32 count, f32 x, f32 y, f32 z, f32 scale);
// decl: void mapObjGetPos(const char* name, Vec* pos);
// proto: static USER_FUNC(fune_eff);
static USER_FUNC(fune_eff) {
    EffectEntry* eff1;
    EffectEntry* eff2;
    f32 oldX;
    f32 oldZ;
    f32 dist;
    f32 angle;
    f32 sign;
    Vec pos;

    if (isFirstCall) {
        event->userdatap[0] = effFunemizuEntry(0, 0.0f, -1000.0f, 0.0f, 0.0f, 0.0f);
        event->userdatap[1] = effFunemizuEntry(2, 0.0f, -1000.0f, 0.0f, 0.0f, 0.0f);
        mapObjGetPos("S_fune_a", &pos);
        event->userdataf[2] = pos.x;
        *(f32*)&event->field_84 = pos.z;
    }
    eff1 = event->userdatap[0];
    eff2 = event->userdatap[1];
    oldX = event->userdataf[2];
    oldZ = *(f32*)&event->field_84;
    mapObjGetPos("S_fune_a", &pos);
    event->userdataf[2] = pos.x;
    *(f32*)&event->field_84 = pos.z;
    dist = distABf(oldX, oldZ, pos.x, pos.z);
    angle = angleABf(oldX, oldZ, pos.x, pos.z);
    if (angle < 180.0f) {
        sign = 1.0f;
    } else {
        sign = -1.0f;
    }
    ((f32*)eff1->userdata)[17] = 3.0f;
    ((f32*)eff1->userdata)[1] = pos.x + 85.0f * sign;
    ((f32*)eff1->userdata)[2] = pos.y - 51.0f;
    ((f32*)eff1->userdata)[3] = 30.0f + pos.z;
    ((f32*)eff1->userdata)[4] = dist;
    if (angle < 180.0f) {
        ((f32*)eff1->userdata)[5] = 135.0f + angle;
    } else {
        ((f32*)eff1->userdata)[5] = 45.0f + angle;
    }
    ((f32*)eff2->userdata)[1] = pos.x - 15.0f * sign;
    ((f32*)eff2->userdata)[2] = pos.y - 51.0f;
    ((f32*)eff2->userdata)[3] = 90.0f + pos.z;
    ((f32*)eff2->userdata)[4] = dist;
    ((f32*)eff2->userdata)[5] = 90.0f + angle;
    if (dist > 1.0f && gp->retraceCount % 15 == 0) {
        effWaterDamageN64Entry(5, 30, pos.x - 150.0f * sign, pos.y - 50.0f, pos.z, 2.0f);
    }
    return EVT_RETURN_BLOCK;
}
