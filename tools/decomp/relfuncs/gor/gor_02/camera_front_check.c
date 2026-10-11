// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// decl: f32 reviseAngle(f32 angle);
// proto: USER_FUNC(camera_front_check);
USER_FUNC(camera_front_check) {
    s32* args = event->args;
    f32 angle = reviseAngle((100.0f * camGetPtr(CAMERA_3D)->viewYaw + 5.0f) / 100.0f);

    if (angle >= 0.0f && angle < 90.0f) {
        evtSetValue(event, *args++, 1);
    }
    if (angle >= 90.0f && angle < 270.0f) {
        evtSetValue(event, *args++, 0);
    }
    if (angle >= 270.0f && angle < 360.0f) {
        evtSetValue(event, *args++, 1);
    }
    return EVT_RETURN_DONE;
}
