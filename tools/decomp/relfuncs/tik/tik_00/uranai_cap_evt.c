// include: manager/evtmgr_cmd.h
// include: driver/dispdrv.h
// decl: void uranai_cap(CameraId cameraId, void* param);
// proto: USER_FUNC(uranai_cap_evt);
USER_FUNC(uranai_cap_evt) {
    dispEntry(CAMERA_SHADOW, 0.0f, 3, uranai_cap, NULL);
    return EVT_RETURN_BLOCK;
}
