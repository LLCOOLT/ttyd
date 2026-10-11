// include: driver/camdrv.h
// include: dolphin/os.h
// proto: USER_FUNC(time_shift);
USER_FUNC(time_shift) {
    CameraEntry* cam = camGetPtr(CAMERA_3D);

    cam->startTimeA += OSMillisecondsToTicks((OSTime)-2000);
    event->savedTime += OSMillisecondsToTicks((OSTime)-3500);
    return EVT_RETURN_DONE;
}
