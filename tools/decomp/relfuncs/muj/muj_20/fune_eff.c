// include: driver/effdrv.h
// include: mario/mariost.h
// decl: EffectEntry* effFunemizuEntry(s32 type, f32 x, f32 y, f32 z, f32 arg4, f32 arg5);
// decl: EffectEntry* effWaterDamageN64Entry(s32 type, s32 count, f32 x, f32 y, f32 z, f32 scale);
// decl: void mapObjGetPos(const char* name, Vec* pos);
// decl: f32 distABf(f32 x1, f32 z1, f32 x2, f32 z2);
// decl: f32 angleABf(f32 x1, f32 z1, f32 x2, f32 z2);
// proto: static USER_FUNC(fune_eff);
static USER_FUNC(fune_eff) {
    EffectEntry* eff1;
    EffectEntry* eff2;
    Vec pos;
    f32 oldX, oldZ, off85, speed;

    if (isFirstCall) {
        event->userdatap[0] = effFunemizuEntry(0, 0.0f, -1000.0f, 0.0f, 0.0f, 0.0f);
        event->userdatap[1] = effFunemizuEntry(2, 0.0f, -1000.0f, 0.0f, 0.0f, 0.0f);
        mapObjGetPos("S_fune_m", &pos);
        event->userdataf[2] = pos.x;
        *(f32*)&event->field_84 = pos.z;
    }
    eff1 = event->userdatap[0];
    eff2 = event->userdatap[1];
    oldX = event->userdataf[2];
    oldZ = *(f32*)&event->field_84;
    mapObjGetPos("S_fune_m", &pos);
    event->userdataf[2] = pos.x;
    *(f32*)&event->field_84 = pos.z;
    speed = distABf(oldX, oldZ, pos.x, pos.z);
    angleABf(oldX, oldZ, pos.x, pos.z);
    off85 = 85.0f;
    if (evtGetValue(event, GSW(0)) == 2) {
        speed = 2.0f;
    }
    ((f32*)eff1->userdata)[17] = 3.0f;
    ((f32*)eff1->userdata)[1] = pos.x + off85;
    ((f32*)eff1->userdata)[2] = pos.y - 51.0f;
    ((f32*)eff1->userdata)[3] = 30.0f + pos.z;
    ((f32*)eff1->userdata)[4] = speed;
    ((f32*)eff1->userdata)[5] = 225.0f;
    ((f32*)eff2->userdata)[1] = pos.x - 15.0f;
    ((f32*)eff2->userdata)[2] = pos.y - 51.0f;
    ((f32*)eff2->userdata)[3] = 90.0f + pos.z;
    ((f32*)eff2->userdata)[4] = speed;
    ((f32*)eff2->userdata)[5] = 180.0f;
    if (speed > 1.0f && gp->retraceCount % 15 == 0) {
        effWaterDamageN64Entry(5, 30, pos.x - 150.0f, pos.y - 50.0f, pos.z, 2.0f);
    }
    return EVT_RETURN_BLOCK;
}
