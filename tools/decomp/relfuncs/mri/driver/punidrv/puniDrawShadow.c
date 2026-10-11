// include: driver/punidrv.h
// proto: void puniDrawShadow(void);
void puniDrawShadow(void) {
    PunidrvWork* wp = work;
    s32 i;
    PunidrvSort* sort;
    PunidrvPose* pose;
    Mtx mtx;

    sort = &wp->sort[wp->poseNum - 1];
    for (i = wp->poseNum - 1; i >= 0; i--, sort--) {
        pose = &wp->poses[sort->index];
        if (!(pose->flags & 4)) {
            PSMTXConcat(camGetCurPtr()->view, *pose->mtx, mtx);
            PSMTXConcat(mtx, wp->shadowMtx, mtx);
            if (pose->flags & 0x10) {
                PSMTXTransApply(mtx, mtx, 0.0f, -(*pose->mtx)[1][3] + pose->shadowY, 0.0f);
            }
            GXLoadPosMtxImm(mtx, 0);
            GXSetCurrentMtx(0);
            GXCallDisplayList(shadow_dl, 0x20);
        }
    }
}
