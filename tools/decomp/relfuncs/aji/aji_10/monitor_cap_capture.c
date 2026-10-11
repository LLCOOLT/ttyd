// include: driver/camdrv.h
// include: driver/npcdrv.h
// include: driver/animdrv.h
// include: dolphin/gx.h
// include: dolphin/mtx.h
// decl: typedef struct MonitorWork { void* buf; s32 ready; s32 kanbu; } MonitorWork;
// decl: static MonitorWork* monitor_wp;
// proto: void monitor_cap_capture(CameraId cameraId, void* param);
void monitor_cap_capture(CameraId cameraId, void* param) {
    CameraEntry saved = *camGetCurPtr();
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
    GXSetViewport(0.0f, 0.0f, 608.0f, 480.0f, 0.0f, 1.0f);
    GXSetScissor(1, 1, 606, 478);
    C_MTXPerspective(projMtx, 60.0f, 1.2666667f, 1.0f, 1000.0f);
    GXSetProjection(projMtx, GX_PERSPECTIVE);
    if (monitor_wp->kanbu) {
        npc = npcNameToPtr("\203J\203\223\203u\201[");
        {
            static const Vec monitor_kanbu_pos = {0.0f, 28.0f, 46.0f};
            static const Vec monitor_kanbu_up = {0.0f, 1.0f, 0.0f};
            static const Vec monitor_kanbu_target = {0.0f, 3.0f, 0.0f};
            Vec pos;
            Vec up;
            Vec target;

            target = monitor_kanbu_target;
            up = monitor_kanbu_up;
            pos = monitor_kanbu_pos;

            C_MTXLookAt(lookAt, &pos, &up, &target);
        }
    } else {
        npc = npcNameToPtr("\216\350\211\272\202P");
        {
            static const Vec monitor_teshita_pos = {0.0f, 25.0f, 30.0f};
            static const Vec monitor_teshita_up = {0.0f, 1.0f, 0.0f};
            static const Vec monitor_teshita_target = {0.0f, 0.0f, 0.0f};
            Vec pos;
            Vec up;
            Vec target;

            target = monitor_teshita_target;
            up = monitor_teshita_up;
            pos = monitor_teshita_pos;

            C_MTXLookAt(lookAt, &pos, &up, &target);
        }
    }
    PSMTXCopy(lookAt, camGetCurPtr()->view);
    PSMTXIdentity(ident);
    animPosePeraOff(npc->poseId);
    animPoseMain(npc->poseId);
    animPoseDrawMtx(npc->poseId, ident, 1, 0.0f, 1.0f);
    animPoseDrawMtx(npc->poseId, ident, 2, 0.0f, 1.0f);
    animPoseDrawMtx(npc->poseId, ident, 3, 0.0f, 1.0f);
    animPosePeraOn(npc->poseId);
    PSMTXCopy(saved.view, camGetCurPtr()->view);
    GXSetTexCopySrc(0, 0, 0x260, 0x1E0);
    GXSetTexCopyDst(0x130, 0xF0, GX_TF_RGB565, GX_TRUE);
    GXCopyTex(monitor_wp->buf, GX_TRUE);
    GXInvalidateTexAll();
    GXPixModeSync();
    GXTexModeSync();
    GXSetViewport(viewport[0], viewport[1], viewport[2], viewport[3], viewport[4], viewport[5]);
    GXSetProjectionv(proj);
    GXSetScissor(sx, sy, sw, sh);
    monitor_wp->ready = 1;
}
