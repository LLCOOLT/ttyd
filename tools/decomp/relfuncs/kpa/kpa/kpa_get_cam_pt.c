// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// proto: USER_FUNC(kpa_get_cam_pt);
USER_FUNC(kpa_get_cam_pt) {
    s32* args = event->args;
    CameraEntry* cam = camGetPtr(CAMERA_3D);

    evtSetFloat(event, args[0], cam->cameraPos.x);
    evtSetFloat(event, args[1], cam->cameraPos.y);
    evtSetFloat(event, args[2], cam->cameraPos.z);
    return EVT_RETURN_DONE;
}
