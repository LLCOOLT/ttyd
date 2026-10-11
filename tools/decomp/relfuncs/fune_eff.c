// include: driver/effdrv.h
// include: mario/mariost.h
// proto: USER_FUNC(fune_eff);
EffectEntry* effFunemizuEntry(s32 type, f32 x, f32 y, f32 z, f32 arg4, f32 arg5);
EffectEntry* effWaterDamageN64Entry(s32 type, s32 count, f32 x, f32 y, f32 z, f32 scale);
void mapObjGetPos(const char* name, Vec* pos);

USER_FUNC(fune_eff) {
    EffectEntry* eff1;
    EffectEntry* eff2;
    Vec pos;

    if (isFirstCall) {
        event->userdatap[0] = effFunemizuEntry(0, 0.0f, -1000.0f, 0.0f, 0.0f, 0.0f);
        event->userdatap[1] = effFunemizuEntry(2, 0.0f, -1000.0f, 0.0f, 0.0f, 0.0f);
        mapObjGetPos("S_fune_m", &pos);
        event->userdataf[2] = pos.x;
        *(f32*)&event->field_84 = pos.z;
    }
    eff1 = event->userdatap[0];
    eff2 = event->userdatap[1];
    mapObjGetPos("S_fune_m", &pos);
    event->userdataf[2] = pos.x;
    *(f32*)&event->field_84 = pos.z;
    ((f32*)eff1->userdata)[17] = 3.0f;
    ((f32*)eff1->userdata)[1] = pos.x - 81.3f;
    ((f32*)eff1->userdata)[2] = pos.y - 51.0f;
    ((f32*)eff1->userdata)[3] = pos.z - 38.9f;
    ((f32*)eff1->userdata)[4] = 1.0f;
    ((f32*)eff1->userdata)[5] = 270.0f;
    ((f32*)eff2->userdata)[1] = pos.x - 49.5f;
    ((f32*)eff2->userdata)[2] = pos.y - 51.0f;
    ((f32*)eff2->userdata)[3] = 70.7f + pos.z;
    ((f32*)eff2->userdata)[4] = 1.0f;
    ((f32*)eff2->userdata)[5] = 305.0f;
    if (gp->retraceCount % 15 == 0) {
        effWaterDamageN64Entry(5, 30, 106.1f + pos.x, pos.y - 50.0f, 106.1f + pos.z, 2.0f);
    }
    return EVT_RETURN_BLOCK;
}
