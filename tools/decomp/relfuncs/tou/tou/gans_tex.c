// include: manager/evtmgr_cmd.h
// include: memory.h
// include: driver/npcdrv.h
// include: driver/animdrv.h
// include: driver/camdrv.h
// include: dolphin/gx.h
// include: dolphin/mtx.h
// decl: typedef struct GansWork { smartEntry* buf; GXTexObj tex; s32 onoff; s32 alpha; s32 ready; } GansWork;
// proto: void gans_tex(CameraId cameraId, void* param);
void gans_tex(CameraId cameraId, void* param) {
    GansWork* wp = param;
    CameraEntry saved;
    Mtx44 projMtx;
    Mtx lookAt;
    Mtx ident;
    f32 viewport[6];
    f32 proj[7];
    u32 sx, sy, sw, sh;
    NpcEntry* npc;

    GXGetViewportv(viewport);
    GXGetProjectionv(proj);
    GXGetScissor(&sx, &sy, &sw, &sh);
    GXSetViewport(0.0f, 0.0f, 128.0f, 128.0f, 0.0f, 1.0f);
    GXSetScissor(1, 1, 126, 126);
    C_MTXPerspective(projMtx, 25.0f, 1.0f, 1.0f, 1000.0f);
    GXSetProjection(projMtx, GX_PERSPECTIVE);
    {
        static const Vec gans_pos = {0.0f, 20.0f, 130.0f};
        static const Vec gans_up = {0.0f, 1.0f, 0.0f};
        static const Vec gans_target = {0.0f, 20.0f, 0.0f};
        Vec pos;
        Vec up;
        Vec target;

        target = gans_target;
        up = gans_up;
        pos = gans_pos;

        C_MTXLookAt(lookAt, &pos, &up, &target);
    }
    saved = *camGetPtr(cameraId);
    npc = npcNameToPtr(evtGetValue(NULL, GSW(0)) < 0xAC ? "\203K\203\223\203X" : "\203L\203m\203V\203R\203\217");
    PSMTXCopy(lookAt, camGetCurPtr()->view);
    animPosePeraOff(npc->poseId);
    PSMTXIdentity(ident);
    animPoseMain(npc->poseId);
    animPoseDrawMtx(npc->poseId, ident, 1, 0.0f, 2.0f);
    animPoseDrawMtx(npc->poseId, ident, 2, 0.0f, 2.0f);
    animPoseDrawMtx(npc->poseId, ident, 3, 0.0f, 2.0f);
    animPosePeraOn(npc->poseId);
    PSMTXCopy(saved.view, camGetCurPtr()->view);
    GXSetTexCopySrc(0, 0, 0x80, 0x80);
    GXSetTexCopyDst(0x80, 0x80, GX_TF_RGB5A3, GX_FALSE);
    GXCopyTex(wp->buf->address, GX_TRUE);
    GXPixModeSync();
    GXSetViewport(viewport[0], viewport[1], viewport[2], viewport[3], viewport[4], viewport[5]);
    GXSetProjectionv(proj);
    GXSetScissor(sx, sy, sw, sh);
    wp->ready = 1;
}
