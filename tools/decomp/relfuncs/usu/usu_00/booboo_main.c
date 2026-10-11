// include: driver/npcdrv.h
// include: driver/animdrv.h
// proto: static USER_FUNC(booboo_main);
static USER_FUNC(booboo_main) {
    u32 i;

    for (i = 0; i < 5; i++) {
        animPoseSetMaterialLightFlagOn(npcNameToPtr((const char*)booboo_name[i * 2])->poseId, 0x10);
    }
    return EVT_RETURN_DONE;
}
