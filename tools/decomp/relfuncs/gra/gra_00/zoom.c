// include: driver/camdrv.h
// include: manager/evtmgr_cmd.h
// include: dolphin/mtx.h
// proto: USER_FUNC(zoom);
USER_FUNC(zoom) {
    s32* args = event->args;
    CameraEntry* cam = camGetPtr(CAMERA_3D);
    Vec v;

    PSVECSubtract(&cam->cameraPos, &cam->cameraAt, &v);
    PSVECScale(&v, &v, 0.6f);
    PSVECAdd(&cam->cameraAt, &v, &v);
    evtSetFloat(event, args[0], v.x);
    evtSetFloat(event, args[1], v.y);
    evtSetFloat(event, args[2], v.z);
    evtSetFloat(event, args[3], cam->cameraAt.x);
    evtSetFloat(event, args[4], cam->cameraAt.y);
    evtSetFloat(event, args[5], cam->cameraAt.z);
    return EVT_RETURN_DONE;
}
