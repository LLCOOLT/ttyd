// include: driver/camdrv.h
// include: dolphin/mtx.h
// decl: double sin(double x);
// proto: USER_FUNC(camera_yure);
USER_FUNC(camera_yure) {
    s32 frames = evtGetValue(event, event->args[0]);
    CameraEntry* cam = camGetPtr(CAMERA_3D);
    Vec v;
    f32 amp;

    if (isFirstCall) {
        event->userdata[0] = 0;
        event->userdata[1] = frames;
    }
    // shake three times, fading out
    amp = sin(18.849556f * event->userdata[0] / event->userdata[1]);
    amp = (event->userdata[1] - event->userdata[0]) * (0.1f * amp) / event->userdata[1];
    PSVECSubtract(&cam->cameraAt, &cam->cameraPos, &v);
    PSVECScale(&v, &v, amp);
    cam->viewOffset.x = v.x;
    cam->viewOffset.y = v.y;
    cam->viewOffset.z = v.z;
    cam = camGetPtr(CAMERA_3D_IMAGE);
    cam->viewOffset.x = v.x;
    cam->viewOffset.y = v.y;
    cam->viewOffset.z = v.z;
    event->userdata[0]++;
    if (event->userdata[0] > event->userdata[1]) {
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}
