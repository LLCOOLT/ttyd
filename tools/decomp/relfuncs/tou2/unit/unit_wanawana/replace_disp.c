// include: battle/battle_unit.h
// include: driver/animdrv.h
// include: driver/camdrv.h
// include: memory.h
// include: system.h
// include: string.h
// include: dolphin/gx.h
// include: dolphin/mtx.h
// decl: typedef struct WanaWork { s32 ready; s32 poseId; Mtx mtx; GXTexObj obj; BattleUnitPart* part; smartEntry* tex; } WanaWork;
// decl: void test_kururing_mapdisp(CameraId camera);
// decl: static f32 tanf(f32 x);
// proto: void replace_disp(CameraId camera, void* param);
void replace_disp(CameraId camera, void* param) {
    WanaWork* wp = param;
    CameraEntry saved;
    AnimationPoseData* data;
    CameraEntry* cam;
    Vec min;
    Vec max;
    Vec pos;
    s32 w;
    s32 h;

    memcpy(&saved, camGetPtr(camera), sizeof(CameraEntry));
    data = animPoseGetAnimBaseDataPtr(wp->poseId);
    min = (Vec){data->bboxMin.x, data->bboxMin.y, data->bboxMin.z};
    max = (Vec){data->bboxMax.x, data->bboxMax.y, data->bboxMax.z};
    w = 2.0f * (max.x - min.x);
    h = 2.0f * (max.z - min.z);
    cam = camGetPtr(camera);
    w += w & 1;
    h += h & 1;
    BtlUnit_GetPartsWorldPos(wp->part, &pos.x, &pos.y, &pos.z);
    cam->cameraUp = (Vec){0.0f, 0.0f, -1.0f};
    cam->cameraAt = pos;
    cam->cameraPos = pos;
    cam->cameraPos.y += (h / 2.0f) / tanf(0.21816616f);
    C_MTXPerspective(cam->projection, 25.0f, (f32)w / (f32)h, 1.0f, 32767.0f);
    cam->projType = GX_PERSPECTIVE;
    C_MTXLookAt(cam->view, &cam->cameraPos, &cam->cameraUp, &cam->cameraAt);
    GXSetProjection(cam->projection, cam->projType);
    GXSetViewport(0.0f, 0.0f, w, h, 0.0f, 1.0f);
    GXSetScissor(0, 0, w, h);
    test_kururing_mapdisp(camera);
    sysWaitDrawSync();
    GXSetTexCopySrc(0, 0, w, h);
    GXSetTexCopyDst(w / 2, h / 2, GX_TF_RGB5A3, GX_TRUE);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXCopyTex(wp->tex->address, GX_TRUE);
    GXInvalidateTexAll();
    GXPixModeSync();
    GXTexModeSync();
    memcpy(camGetPtr(camera), &saved, sizeof(CameraEntry));
    wp->ready = 1;
}
