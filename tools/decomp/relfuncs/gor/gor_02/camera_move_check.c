// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// decl: f32 reviseAngle(f32 angle);
// proto: USER_FUNC(camera_move_check);
USER_FUNC(camera_move_check) {
    f32 angle;

    if (isFirstCall) {
        event->userdataf[0] = -1000.0f;
    }
    angle = reviseAngle((100.0f * camGetPtr(CAMERA_3D)->viewYaw + 5.0f) / 100.0f);
    if (event->userdataf[0] != angle) {
        event->userdataf[0] = angle;
        return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_DONE;
}
