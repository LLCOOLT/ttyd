// include: manager/evtmgr_cmd.h
// include: driver/dispdrv.h
// decl: void kpa_stageclear_disp(CameraId camera, void* param);
// proto: USER_FUNC(kpa_stageclear_disp_entry);
USER_FUNC(kpa_stageclear_disp_entry) {
    dispEntry(CAMERA_2D, 1000.0f, 0, kpa_stageclear_disp, NULL);
    return EVT_RETURN_DONE;
}
