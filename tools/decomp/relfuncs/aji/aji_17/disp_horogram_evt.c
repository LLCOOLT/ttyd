// include: manager/evtmgr_cmd.h
// include: driver/dispdrv.h
// decl: void disp_horogram(CameraId cameraId, void* param);
// proto: USER_FUNC(disp_horogram_evt);
USER_FUNC(disp_horogram_evt) {
    dispEntry(CAMERA_3D, 0.0f, 2, disp_horogram, NULL);
    return EVT_RETURN_BLOCK;
}
