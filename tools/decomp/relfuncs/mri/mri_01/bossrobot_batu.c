// include: driver/npcdrv.h
// include: driver/animdrv.h
// include: driver/dispdrv.h
// include: system.h
// include: dolphin/mtx.h
// proto: void bossrobot_batu(CameraId camera, void* param);
void bossrobot_batu(CameraId camera, void* param) {
    u8* alpha = param;
    NpcEntry* robot = npcNameToPtr("\203{\203X\203\215\203{\203b\203g");
    NpcEntry* batu = npcNameToPtr("\203{\203X\203\215\203{\203b\203g\203o\203c");
    Mtx* mtxs = *animPoseGetAnimPosePtr(robot->poseId)->worldMatrices;
    s32 idx = animPoseGetGroupIdx(robot->poseId, "locator23");
    Mtx rot;
    Mtx mtx;

    mtxGetRotationElement(mtxs[idx], rot, 'x', 'z');
    PSMTXTrans(mtx, mtxs[idx][0][3], mtxs[idx][1][3], mtxs[idx][2][3]);
    PSMTXConcat(mtx, rot, mtx);
    PSMTXTrans(rot, 0.0f, 0.0f, 0.2f);
    PSMTXConcat(mtx, rot, mtx);
    animPosePeraOff(batu->poseId);
    animPoseSetMaterialFlagOn(batu->poseId, 0x40);
    animPoseSetMaterialEvtColor(batu->poseId, (GXColor){0xFF, 0xFF, 0xFF, *alpha});
    switch (dispGetCurWork()->renderMode) {
        case 0:
            animPoseDrawMtx(batu->poseId, mtx, 1, 0.0f, 2.0f);
            break;
        case 1:
            animPoseDrawMtx(batu->poseId, mtx, 2, 0.0f, 2.0f);
            break;
        case 2:
            animPoseDrawMtx(batu->poseId, mtx, 3, 0.0f, 2.0f);
            break;
    }
}
