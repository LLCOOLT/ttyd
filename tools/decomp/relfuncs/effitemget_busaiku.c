// include: driver/camdrv.h
// include: mario/mariost.h
// include: dolphin/mtx.h
// decl: static inline void effitemget_cam_move(CameraEntry* camera, Vec ofs) { camera->presetPos = camera->cameraPos; camera->presetAt = camera->cameraAt; PSVECAdd(&camera->cameraPos, &ofs, &camera->storedPos); PSVECAdd(&camera->cameraAt, &ofs, &camera->storedAt); camera->startTimeA = gp->renderTime; camera->durationA = 0; camera->stateA = 3; camera->curveA = 11; }
// proto: static USER_FUNC(effitemget_busaiku);
static USER_FUNC(effitemget_busaiku) {
    s32 up = evtGetValue(event, event->args[0]);
    CameraEntry* camera = camGetPtr(4);
    Vec ofs;

    if (up) {
        ofs = (Vec){0.0f, 2016.0f, 0.0f};
    } else {
        ofs = (Vec){0.0f, -2016.0f, 0.0f};
    }
    effitemget_cam_move(camera, ofs);
    return EVT_RETURN_DONE;
}
