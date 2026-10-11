// include: manager/evtmgr_cmd.h
// include: driver/dispdrv.h
// decl: void monitor_cap_capture(CameraId cameraId, void* param);
// proto: USER_FUNC(monitor_cap_evt);
USER_FUNC(monitor_cap_evt) {
    dispEntry(CAMERA_3D, 1000.0f, 0, monitor_cap_capture, NULL);
    return EVT_RETURN_BLOCK;
}
