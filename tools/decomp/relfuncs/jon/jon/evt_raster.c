// include: driver/dispdrv.h
// include: manager/evtmgr.h
// decl: void raster_disp(CameraId cameraId, void* param);
// proto: USER_FUNC(evt_raster);
USER_FUNC(evt_raster) {
    f32* work = (f32*)event->lwData;

    if (isFirstCall) {
        work[0] = 0.0f;
        work[1] = 0.0f;
    }
    work[0] += 0.2f;
    work[1] += 0.01f;
    dispEntry(CAMERA_2D, 0.0f, 3, raster_disp, event);
    return EVT_RETURN_BLOCK;
}
