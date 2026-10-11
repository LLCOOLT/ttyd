// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// include: mario/mariost.h
// decl: double sin(double x);
// decl: s32 psndSFXOn(const char* name);
// decl: static f32 view_dy;
// decl: static s32 view_trg;
// proto: USER_FUNC(cam_yure);
USER_FUNC(cam_yure) {
    CameraEntry* cam = camGetPtr(CAMERA_3D);
    f32 s;

    if (isFirstCall) {
        view_dy = cam->viewOffset.y;
        view_trg = 0;
    }
    s = sin(gp->retraceCount / 50.0f);
    cam->viewOffset.y += 0.3f * s;
    if (!view_trg) {
        if (cam->viewOffset.y > view_dy) {
            view_trg = 1;
        }
    } else if (cam->viewOffset.y < view_dy) {
        psndSFXOn("SFX_EVT_OPN_SHIP_CREAK1");
        view_trg = 0;
    }
    return EVT_RETURN_BLOCK;
}
