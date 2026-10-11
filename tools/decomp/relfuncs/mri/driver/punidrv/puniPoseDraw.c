// include: driver/punidrv.h
// include: memory.h
// proto: void puniPoseDraw(s32 index);
void puniPoseDraw(s32 index) {
    PunidrvWork* wp = work;
    PunidrvPose* pose = &wp->poses[index];
    s32 texId;
    PunidrvTex* tex;
    Mtx mtx;

    if (pose->flags & 1) {
        texId = pose->texId;
        if (wp->curTex != texId) {
            tex = &wp->texs[texId];
            GXLoadTexObjPreLoaded(smartTexObj(&tex->obj, tex->image), &tex->region, GX_TEXMAP0);
            wp->curTex = texId;
        }
        PSMTXConcat(camGetCurPtr()->view, *pose->mtx, mtx);
        GXLoadPosMtxImm(mtx, 0);
        GXSetCurrentMtx(0);
        GXCallDisplayList(&wp->dl[pose->texId * 0x80], wp->dlSize[pose->texId]);
    }
}
