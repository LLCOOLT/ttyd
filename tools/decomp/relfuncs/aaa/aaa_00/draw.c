// include: driver/camdrv.h
// include: win/win_main.h
// include: dolphin/gx.h
// proto: void draw(CameraId camera, void* param);
void draw(CameraId camera, void* param) {
    CameraEntry saved;
    f32 viewport[6];
    f32 projection[7];
    CameraEntry* cam;

    GXGetViewportv(viewport);
    GXGetProjectionv(projection);
    cam = camGetPtr(CAMERA_2D);
    GXSetProjection(camGetPtr(CAMERA_2D)->projection, cam->projType);
    saved = *camGetCurPtr();
    cam = camGetPtr(CAMERA_2D);
    *camGetCurPtr() = *cam;
    winTexInit(*(TEXPalette**)wp->tpl->data);
    winTexSet(3, (Vec){0.0f, 0.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){0xFF, 0xFF, 0xFF, wp->alpha});
    *camGetCurPtr() = saved;
    GXSetViewport(viewport[0], viewport[1], viewport[2], viewport[3], viewport[4], viewport[5]);
    GXSetProjectionv(projection);
}
