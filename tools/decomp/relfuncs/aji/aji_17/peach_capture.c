// include: driver/camdrv.h
// include: driver/npcdrv.h
// include: driver/animdrv.h
// include: dolphin/gx.h
// include: dolphin/mtx.h
// decl: typedef struct HorogramWork { void* buf0; void* buf1; GXTexObj tex0; GXTexObj tex1; u16 ready; u16 flags; } HorogramWork;
// decl: HorogramWork* horogram_wp;
// decl: static const Vec horogram_pos = {0.0f, 0.0f, 20.0f};
// decl: static const Vec horogram_up = {0.0f, 1.0f, 0.0f};
// decl: static const Vec horogram_target = {0.0f, 0.0f, 0.0f};
// proto: void peach_capture(CameraId cameraId, void* param);
void peach_capture(CameraId cameraId, void* param) {
    CameraEntry saved = *camGetCurPtr();
    Mtx44 projMtx;
    Mtx lookAt;
    Mtx ident;
    f32 viewport[6];
    f32 proj[7];
    u32 sx, sy, sw, sh;
    NpcEntry* holo;
    NpcEntry* holo2;
    NpcEntry* npc;

    holo = npcNameToPtr("\203z\203\215\203O\203\211\203\200");
    holo2 = npcNameToPtr("\203z\203\215\203O\203\211\203\2002");
    if (90.0f <= holo->direction && holo->direction < 270.0f) {
        npc = holo2;
        if (!(horogram_wp->flags & 2)) {
            animPoseSetLocalTime(holo2->poseId, 0.0f);
        }
        horogram_wp->flags |= 2;
    } else {
        npc = holo;
        if (horogram_wp->flags & 2) {
            animPoseSetLocalTime(holo->poseId, 0.0f);
        }
        horogram_wp->flags &= ~2;
    }
    if (!(horogram_wp->flags & 1)) {
        npc = holo;
    }
    GXGetViewportv(viewport);
    GXGetProjectionv(proj);
    GXGetScissor(&sx, &sy, &sw, &sh);
    GXSetViewport(0.0f, 0.0f, 608.0f, 480.0f, 0.0f, 1.0f);
    GXSetScissor(1, 1, 606, 478);
    C_MTXOrtho(projMtx, 28.0f, 0.0f, -14.0f, 14.0f, 1.0f, 100.0f);
    GXSetProjection(projMtx, GX_ORTHOGRAPHIC);
    {
        Vec pos;
        Vec up;
        Vec target;

        target = horogram_target;
        up = horogram_up;
        pos = horogram_pos;

        C_MTXLookAt(lookAt, &pos, &up, &target);
    }
    PSMTXCopy(lookAt, camGetCurPtr()->view);
    PSMTXIdentity(ident);
    animPoseSetMaterialFlagOff(npc->poseId, 0x40);
    animPoseMain(npc->poseId);
    animPoseDrawMtx(npc->poseId, ident, 1, 0.0f, 1.0f);
    animPoseDrawMtx(npc->poseId, ident, 2, 0.0f, 1.0f);
    animPoseDrawMtx(npc->poseId, ident, 3, 0.0f, 1.0f);
    GXSetTexCopySrc(0, 0, 0x260, 0x1E0);
    GXSetTexCopyDst(0x130, 0xF0, GX_TF_RGBA8, GX_TRUE);
    GXCopyTex(horogram_wp->buf0, GX_FALSE);
    GXPixModeSync();
    GXSetTexCopyDst(0x130, 0xF0, GX_TF_Z8, GX_TRUE);
    GXCopyTex(horogram_wp->buf1, GX_TRUE);
    GXPixModeSync();
    PSMTXCopy(saved.view, camGetCurPtr()->view);
    GXSetViewport(viewport[0], viewport[1], viewport[2], viewport[3], viewport[4], viewport[5]);
    GXSetProjectionv(proj);
    GXSetScissor(sx, sy, sw, sh);
    horogram_wp->ready = 1;
}
