// include: manager/evtmgr_cmd.h
// include: driver/dispdrv.h
// decl: void mabutaDisp(CameraId camera, void* param);
// proto: USER_FUNC(mabuta);
USER_FUNC(mabuta) {
    dispEntry(CAMERA_2D, 1100.0f, 0, mabutaDisp, NULL);
    return EVT_RETURN_BLOCK;
}
