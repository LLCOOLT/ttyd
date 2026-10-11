// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// proto: USER_FUNC(camAtY);
USER_FUNC(camAtY) {
    s32* args = event->args;

    evtSetValue(event, args[0], camGetPtr(CAMERA_3D)->cameraAt.y);
    return EVT_RETURN_DONE;
}
