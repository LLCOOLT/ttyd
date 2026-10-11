// include: driver/camdrv.h
// proto: USER_FUNC(shake);
USER_FUNC(shake) {
    CameraEntry* camera = camGetPtr(4);

    if (isFirstCall) {
        event->userdata[0] = 0;
        event->userdata[1] = 0;
    }
    event->userdata[1]--;
    if (event->userdata[1] < 0) {
        event->userdata[0] = 1 - event->userdata[0];
        event->userdata[1] = 2;
    }
    if (event->userdata[0] != 0) {
        camera->viewOffset.z = 3.0f;
    } else {
        camera->viewOffset.z = 0.0f;
    }
    return EVT_RETURN_BLOCK;
}
