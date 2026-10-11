// include: manager/evtmgr_cmd.h
// include: mario/mariost.h
// include: driver/camdrv.h
// include: dolphin/mtx.h
// proto: static USER_FUNC(enzan_cam_turn_keisan_f);
static USER_FUNC(enzan_cam_turn_keisan_f) {
    f32 t = evtGetFloat(event, event->args[0]) / 100.0f;
    CameraEntry* cam = camGetPtr(CAMERA_3D);
    Vec base;
    Vec pos;
    Vec pivot;
    Mtx mtx;
    f32 x = -362.0f;

    base = (Vec){x, 193.0f + -62.0f * t, 686.0f + -354.0f * t};
    pos = base;
    pivot = (Vec){-362.0f, 37.0f, -200.0f};
    PSVECSubtract(&pos, &pivot, &pos);
    PSMTXRotRad(mtx, 'Y', 0.017453292f * (720.0f * t));
    PSMTXMultVec(mtx, &pos, &pos);
    PSVECAdd(&pos, &pivot, &pos);
    cam->presetPos = cam->cameraPos;
    cam->presetAt = cam->cameraAt;
    cam->storedPos = pos;
    cam->storedAt = cam->cameraAt;
    cam->startTimeA = gp->renderTime;
    cam->durationA = 0;
    cam->stateA = 3;
    cam->curveA = 0;
    return EVT_RETURN_DONE;
}
