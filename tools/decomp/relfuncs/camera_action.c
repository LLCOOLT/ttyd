// include: driver/camdrv.h
// include: mario/mariost.h
// proto: USER_FUNC(camera_action);
USER_FUNC(camera_action) {
    CameraEntry* cam = camGetPtr(CAMERA_3D);
    Vec pos = {290.0f, 150.0f, 491.0f};
    Vec at = {290.0f, 90.0f, -6.0f};
    f32 x;

    if (isFirstCall) {
        f32 speed;
        f32 dist;

        ((f32*)event->lwData)[0] = 0.0f;
        ((f32*)event->lwData)[1] = 2.5f;
        event->lwData[2] = 0;
        speed = 0.0f;
        dist = 0.0f;
        while (TRUE) {
            if (speed >= 2.5f) {
                break;
            }
            speed += 0.01f;
            dist += speed;
        }
        ((f32*)event->lwData)[2] = dist - 2.5f;
    }
    if (((f32*)event->lwData)[0] < 300.0f - ((f32*)event->lwData)[2]) {
        ((f32*)event->lwData)[0] += ((f32*)event->lwData)[1];
        x = -10.0f + ((f32*)event->lwData)[0];
        event->lwData[10] = 0;
        at.x = pos.x = x;
    } else if (((f32*)event->lwData)[0] < 300.0f) {
        ((f32*)event->lwData)[0] += ((f32*)event->lwData)[1];
        ((f32*)event->lwData)[1] -= 0.01f;
        x = -10.0f + ((f32*)event->lwData)[0];
        event->lwData[10] = 0;
        at.x = pos.x = x;
    } else {
        event->lwData[10] = 1;
    }
    cam->presetPos = cam->cameraPos;
    cam->presetAt = cam->cameraAt;
    cam->storedPos = pos;
    cam->storedAt = at;
    cam->startTimeA = gp->renderTime;
    cam->durationA = 0;
    cam->stateA = 3;
    cam->curveA = 11;
    return event->lwData[10] == 0 ? EVT_RETURN_BLOCK : EVT_RETURN_DONE;
}
