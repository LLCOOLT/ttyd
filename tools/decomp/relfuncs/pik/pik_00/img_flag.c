// include: driver/imgdrv.h
// include: driver/animdrv.h
// include: mario/mariost.h
// proto: USER_FUNC(img_flag);
USER_FUNC(img_flag) {
    animPoseSetMaterialFlagOn(imgNameToPtr("img", gp->inBattle != 0)->poseId, 0x1800);
    return EVT_RETURN_DONE;
}
