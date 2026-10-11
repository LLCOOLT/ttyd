// include: manager/evtmgr_cmd.h
// include: driver/dispdrv.h
// decl: void kpa_status_disp(CameraId camera, void* param);
// proto: USER_FUNC(kpa_status_main);
USER_FUNC(kpa_status_main) {
    dispEntry(CAMERA_2D, 1000.0f, 0, kpa_status_disp, NULL);
    return EVT_RETURN_DONE;
}
