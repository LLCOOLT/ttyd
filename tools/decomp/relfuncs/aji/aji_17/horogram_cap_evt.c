// include: manager/evtmgr_cmd.h
// include: driver/dispdrv.h
// decl: void peach_capture(CameraId cameraId, void* param);
// proto: USER_FUNC(horogram_cap_evt);
USER_FUNC(horogram_cap_evt) {
    dispEntry(CAMERA_3D, 1000.0f, 0, peach_capture, NULL);
    return EVT_RETURN_BLOCK;
}
