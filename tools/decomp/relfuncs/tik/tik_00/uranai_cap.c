// include: driver/camdrv.h
// include: driver/npcdrv.h
// include: driver/animdrv.h
// include: memory.h
// include: dolphin/gx.h
// include: dolphin/mtx.h
// decl: typedef struct UranaiWork { s32 lwData[16]; s32 gwData[32]; smartEntry* buf; GXTexObj tex; s32 ready; EventEntry* capEvent; s32 x; s32 y; s32 w; s32 h; } UranaiWork;
// decl: UranaiWork* uranai_wp;
// decl: double tan(double);
// decl: static inline f32 tanf(f32 x) { return tan(x); }
// proto: void uranai_cap(CameraId cameraId, void* param);
void uranai_cap(CameraId cameraId, void* param) {
    CameraEntry* cam = camGetPtr(CAMERA_3D);
    f32 half;
    u16 w = uranai_wp->w;
    u16 h = uranai_wp->h;
    f32 viewport[6];
    f32 proj[7];
    u32 sx, sy, sw, sh;
    Mtx44 projMtx;
    Mtx lookAt;
    Mtx ident;
    CameraEntry saved;
    NpcEntry* npc;
    AnimationPoseData* data;
    Vec bmin;
    Vec bmax;
    f32 scale;

    GXGetViewportv(viewport);
    GXGetProjectionv(proj);
    GXGetScissor(&sx, &sy, &sw, &sh);
    GXSetViewport(0.0f, 0.0f, w, h, 0.0f, 1.0f);
    GXSetScissor(1, 1, w - 2, h - 2);
    C_MTXPerspective(projMtx, 25.0f, w / h, 1.0f, 1000.0f);
    GXSetProjection(projMtx, GX_PERSPECTIVE);
    {
        static const Vec uranai_pos = {0.0f, 0.0f, 0.0f};
        static const Vec uranai_up = {0.0f, 1.0f, 0.0f};
        static const Vec uranai_target = {0.0f, 0.0f, 0.0f};
        Vec pos;
        Vec up;
        Vec target;

        target = uranai_target;
        target.y = h / 3.0f;
        up = uranai_up;
        pos = uranai_pos;
        half = 0.5f;
        pos.y = h / 3.0f;
        {
            f32 t = tan(0.21816616f);

            pos.z = 0.7f * ((h * half) / t);
        }
        C_MTXLookAt(lookAt, &pos, &up, &target);
    }
    saved = *camGetPtr(cameraId);
    npc = npcNameToPtr("\202\244\202\347\202\310\202\242\216t");
    data = animPoseGetAnimBaseDataPtr(npc->poseId);
    bmin = (Vec){data->bboxMin.x, data->bboxMin.y, data->bboxMin.z};
    bmax = (Vec){data->bboxMax.x, data->bboxMax.y, data->bboxMax.z};
    scale = w / (2.0f * (bmax.x - bmin.x));
    PSMTXCopy(lookAt, camGetCurPtr()->view);
    animPosePeraOff(npc->poseId);
    PSMTXIdentity(ident);
    animPoseDrawMtx(npc->poseId, ident, 1, 0.0f, scale);
    animPoseDrawMtx(npc->poseId, ident, 2, 0.0f, scale);
    animPoseDrawMtx(npc->poseId, ident, 3, 0.0f, scale);
    animPosePeraOn(npc->poseId);
    PSMTXCopy(saved.view, camGetCurPtr()->view);
    uranai_wp->buf = smartAlloc(GXGetTexBufferSize(w, h, GX_TF_RGB5A3, GX_FALSE, 0), 3);
    GXSetTexCopySrc(0, 0, w, h);
    GXSetTexCopyDst(w, h, GX_TF_RGB5A3, GX_FALSE);
    GXCopyTex(uranai_wp->buf->address, GX_TRUE);
    GXPixModeSync();
    GXInitTexObj(&uranai_wp->tex, uranai_wp->buf->address, w, h, GX_TF_RGB5A3, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&uranai_wp->tex, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXSetViewport(viewport[0], viewport[1], viewport[2], viewport[3], viewport[4], viewport[5]);
    GXSetProjectionv(proj);
    GXSetScissor(sx, sy, sw, sh);
    uranai_wp->ready = 1;
}
