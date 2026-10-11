// include: driver/camdrv.h
// include: driver/npcdrv.h
// include: driver/animdrv.h
// include: dolphin/gx.h
// include: dolphin/mtx.h
// proto: void make_gonbaba_projection(CameraId camera, void* param);
void make_gonbaba_projection(CameraId camera, void* param) {
    GonbabaProj* wp = param;
    CameraEntry saved;
    Mtx44 proj;
    Mtx view;
    Mtx mtx;
    f32 viewport[6];
    f32 projv[7];
    NpcEntry* npc;
    u32 left;
    u32 top;
    u32 width;
    u32 height;

    GXGetViewportv(viewport);
    GXGetProjectionv(projv);
    GXGetScissor(&left, &top, &width, &height);
    GXSetViewport(0.0f, 0.0f, 608.0f, 480.0f, 0.0f, 1.0f);
    GXSetScissor(1, 1, 606, 478);
    C_MTXPerspective(proj, 25.0f, 1.2666667f, 1.0f, 1000.0f);
    GXSetProjection(proj, GX_PERSPECTIVE);
    C_MTXLookAt(view, &(Vec){0.0f, 190.0f, 0.0f}, &(Vec){0.0f, 0.0f, -1.0f}, &(Vec){0.0f, 0.0f, 0.0f});
    saved = *camGetCurPtr();
    npc = npcNameToPtr("\203S\203\223\203o\203o\211e");
    PSMTXCopy(view, camGetCurPtr()->view);
    PSMTXIdentity(mtx);
    animPoseDrawMtx(npc->poseId, mtx, 1, 0.0f, 2.0f);
    animPoseDrawMtx(npc->poseId, mtx, 2, 0.0f, 2.0f);
    animPoseDrawMtx(npc->poseId, mtx, 3, 0.0f, 2.0f);
    PSMTXCopy(saved.view, camGetCurPtr()->view);
    GXSetTexCopySrc(0, 0, 608, 480);
    GXSetTexCopyDst(608, 480, GX_TF_RGBA8, GX_FALSE);
    GXCopyTex(wp->tex->address, GX_TRUE);
    GXInvalidateTexAll();
    GXPixModeSync();
    GXTexModeSync();
    GXSetViewport(viewport[0], viewport[1], viewport[2], viewport[3], viewport[4], viewport[5]);
    GXSetProjectionv(projv);
    GXSetScissor(left, top, width, height);
}
