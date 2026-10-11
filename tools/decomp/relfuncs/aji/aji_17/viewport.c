// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// proto: static USER_FUNC(viewport);
static USER_FUNC(viewport) {
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 w = evtGetFloat(event, args[2]);
    f32 h = evtGetFloat(event, args[3]);
    CameraEntry* cam;

    cam = camGetPtr(CAMERA_3D);
    cam->viewport[0] = x;
    cam->viewport[1] = y;
    cam->viewport[2] = w;
    cam->viewport[3] = h;
    cam = camGetPtr(CAMERA_2D);
    cam->viewport[0] = x;
    cam->viewport[1] = y;
    cam->viewport[2] = w;
    cam->viewport[3] = h;
    return EVT_RETURN_DONE;
}
