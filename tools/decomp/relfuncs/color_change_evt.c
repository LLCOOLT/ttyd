// include: mario/mario.h
// include: driver/mapdrv.h
// include: driver/animdrv.h
// decl: static void callback(MapTevCallbackInfo* info);
// proto: s32 color_change_evt(s32 on);
s32 color_change_evt(s32 on) {
    s32 i;

    if (on == 0) {
        for (i = 0; i < 3; i++) {
            animPoseSetMaterialFlagOff(marioGetPtr()->paperAnimGroupId[i], 0x0A000000);
        }
        marioGetPtr()->flags &= ~0x40000000;
    } else {
        mapSetTevCallback(10, callback);
        for (i = 0; i < 3; i++) {
            animPoseSetMaterialFlagOn(marioGetPtr()->paperAnimGroupId[i], 0x0A000000);
        }
        marioGetPtr()->flags |= 0x40000000;
    }
    return 0;
}
