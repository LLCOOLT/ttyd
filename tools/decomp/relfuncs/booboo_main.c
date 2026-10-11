// include: driver/npcdrv.h
// include: driver/animdrv.h
// proto: USER_FUNC(booboo_main);
USER_FUNC(booboo_main) {
    animPoseSetMaterialLightFlagOn(npcNameToPtr((const char*)booboo_name[0])->poseId, 0x10);
    return EVT_RETURN_DONE;
}
