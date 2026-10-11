// include: manager/evtmgr_cmd.h
// include: driver/dispdrv.h
// include: system.h
// decl: f32 point[4];
// decl: s32 darkCount;
// decl: u8 dark;
// proto: void spot_square_disp(CameraId cameraId, void* param);
// proto: USER_FUNC(spot_square);
USER_FUNC(spot_square) {
    s32* args = event->args;
    s32 time;
    s32 wait;

    point[0] = evtGetFloat(event, args[0]);
    point[1] = evtGetFloat(event, args[1]);
    point[2] = evtGetFloat(event, args[2]);
    point[3] = evtGetFloat(event, args[3]);
    time = evtGetValue(event, args[4]);
    wait = evtGetValue(event, args[5]);
    if (isFirstCall) {
        dark = 0;
        darkCount = 0;
    }
    darkCount++;
    if (darkCount >= 0 && darkCount <= time) {
        dark = intplGetValue(0, darkCount, time, 0.0f, 192.0f);
    }
    if (darkCount >= time + wait && darkCount <= wait + time * 2) {
        dark = intplGetValue(0, darkCount - (time + wait), time, 192.0f, 0.0f);
    }
    dispEntry(CAMERA_2D, 500.0f, 2, spot_square_disp, NULL);
    return darkCount >= wait + time * 2 ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}
