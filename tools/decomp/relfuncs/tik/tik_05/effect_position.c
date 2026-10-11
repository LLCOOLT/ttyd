// include: driver/effdrv.h
// include: driver/itemdrv.h
// include: driver/camdrv.h
// decl: double sin(double);
// decl: double cos(double);
// proto: USER_FUNC(effect_position);
USER_FUNC(effect_position) {
    ItemEntry* item = itemNameToPtr("item00");
    f32 angle = -(6.2831855f * camGetPtr(CAMERA_3D)->viewYaw / 360.0f);
    f32 x;
    f32 z;
    EffectEntry* eff;

    x = 5.0f * (f32)sin(angle);
    z = 5.0f * (f32)cos(angle);
    eff = effNameToPtr("map_wave");
    if (eff != NULL) {
        ((f32*)eff->userdata)[1] = item->position.x + x;
        ((f32*)eff->userdata)[2] = item->position.y;
        ((f32*)eff->userdata)[3] = item->position.z + z;
    }
    x = 10.0f * (f32)sin(angle);
    z = 10.0f * (f32)cos(angle);
    eff = effNameToPtr("map_map");
    if (eff != NULL) {
        ((f32*)eff->userdata)[1] = item->position.x + x;
        ((f32*)eff->userdata)[2] = item->position.y;
        ((f32*)eff->userdata)[3] = item->position.z + z;
        ((f32*)eff->userdata)[8] = 180.0f - camGetPtr(CAMERA_3D)->viewYaw;
        ((s32*)eff->userdata)[5] = evtGetValue(event, (s32)0xFD050F8B);
        ((f32*)eff->userdata)[4] = 0.9f;
    }
    x = 15.0f * (f32)sin(angle);
    z = 15.0f * (f32)cos(angle);
    eff = effNameToPtr("map_ball");
    if (eff != NULL) {
        ((f32*)eff->userdata)[1] = item->position.x + x;
        ((f32*)eff->userdata)[2] = item->position.y;
        ((f32*)eff->userdata)[3] = item->position.z + z;
    }
    return EVT_RETURN_BLOCK;
}
