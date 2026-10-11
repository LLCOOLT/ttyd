// include: manager/evtmgr_cmd.h
// include: driver/dispdrv.h
// decl: void noiseDisp(CameraId cameraId, void* param);
// proto: USER_FUNC(noise);
USER_FUNC(noise) {
    s32 alpha = evtGetValue(event, event->args[0]);
    dispEntry(CAMERA_2D, 1100.0f, 0, noiseDisp, (void*)alpha);
    return EVT_RETURN_DONE;
}
