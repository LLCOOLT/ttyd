// include: driver/imgdrv.h
// include: driver/animdrv.h
// include: mario/mariost.h
// include: dolphin/mtx.h
// proto: USER_FUNC(img_alpha);
USER_FUNC(img_alpha) {
    Mtx trans;
    Mtx scale;
    Mtx rot;
    s32 alpha = evtGetValue(event, event->args[0]);
    ImageEntry* img = imgNameToPtr("img", gp->inBattle != 0);

    animPoseSetMaterialFlagOn(img->poseId, 0x40);
    animPoseSetMaterialEvtColor(img->poseId, (GXColor){0xFF, 0xFF, 0xFF, alpha});
    PSMTXTrans(trans, 0.0f, 1.5f, 0.0f);
    PSMTXScale(scale, 0.9f, 0.9f, 0.9f);
    PSMTXRotRad(rot, 'x', -0.5235988f);
    PSMTXConcat(trans, scale, trans);
    PSMTXConcat(trans, rot, img->field_0x120);
    return EVT_RETURN_DONE;
}
