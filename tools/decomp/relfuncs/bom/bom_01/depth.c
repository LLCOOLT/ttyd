// include: manager/evtmgr_cmd.h
// include: driver/dispdrv.h
// decl: static void depthDisp(CameraId camera, void* param);
// proto: static USER_FUNC(depth);
static USER_FUNC(depth) {
    dispEntry(CAMERA_2D, 1000.0f, 0, depthDisp, NULL);
    return EVT_RETURN_BLOCK;
}
