// include: driver/camdrv.h
// include: mario/mariost.h
// decl: static char tmp[32];
// decl: Vec camPt;
// decl: Vec camAt;
// proto: USER_FUNC(omiseFukki);
USER_FUNC(omiseFukki) {
    CameraEntry* cam = camGetPtr(CAMERA_3D);

    cam->presetPos = cam->cameraPos;
    cam->presetAt = cam->cameraAt;
    cam->storedPos = camPt;
    cam->storedAt = camAt;
    cam->startTimeA = gp->renderTime;
    cam->durationA = OSMillisecondsToTicks(500);
    cam->stateA = 3;
    cam->curveA = 11;
    return EVT_RETURN_DONE;
}
