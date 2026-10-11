// include: driver/camdrv.h
// include: mario/mariost.h
// decl: double sin(double x);
// decl: double cos(double x);
// proto: static USER_FUNC(cam_kaiten_set_direct);
static USER_FUNC(cam_kaiten_set_direct) {
    CameraEntry* camera = camGetPtr(4);
    f32 s = sin(6.2831855f * ckpw->angle / 360.0f);
    f32 c = cos(6.2831855f * ckpw->angle / 360.0f);

    ckpw->pos.x = ckpw->dist * s + ckpw->target.x;
    ckpw->pos.z = ckpw->target.z - ckpw->dist * c;
    camera->presetPos = camera->cameraPos;
    camera->presetAt = camera->cameraAt;
    camera->storedPos = ckpw->pos;
    camera->storedAt = ckpw->target;
    camera->startTimeA = gp->renderTime;
    camera->durationA = 0;
    camera->stateA = 3;
    camera->curveA = 11;
    return EVT_RETURN_DONE;
}
