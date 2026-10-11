// include: driver/punidrv.h
// include: memory.h
// proto: void puniDraw(void);
void puniDraw(void) {
    PunidrvWork* wp = work;
    s32 i;
    PunidrvSort* sort;
    PunidrvPose* pose;
    s32 texId;
    PunidrvTex* tex;
    Mtx mtx;
    Mtx scale;
    Mtx rot;
    Mtx trans;

    for (i = wp->poseNum - 1, sort = wp->sort; i >= 0; i--, sort++) {
        pose = &wp->poses[sort->index];
        if (pose->flags & 1) {
            texId = pose->texId;
            if (texId != wp->curTex) {
                tex = &wp->texs[texId];
                GXLoadTexObjPreLoaded(smartTexObj(&tex->obj, tex->image), &tex->region, GX_TEXMAP0);
                wp->curTex = texId;
            }
            PSMTXTrans(trans, 0.0f, pose->offsetY, 0.0f);
            PSMTXRotRad(rot, 'Z', 0.017453292f * pose->rotZ);
            PSMTXScale(scale, pose->scale, pose->scale, 1.0f);
            PSMTXConcat(*pose->mtx, trans, mtx);
            PSMTXConcat(mtx, rot, mtx);
            PSMTXConcat(mtx, scale, mtx);
            PSMTXConcat(camGetCurPtr()->view, mtx, mtx);
            GXLoadPosMtxImm(mtx, 0);
            GXSetCurrentMtx(0);
            GXCallDisplayList(&wp->dl[texId * 0x80], wp->dlSize[texId]);
        }
    }
}
