// include: driver/camdrv.h
// proto: USER_FUNC(shake_reset);
USER_FUNC(shake_reset) {
    CameraEntry* camera = camGetPtr(4);

    camera->viewOffset.z = 0.0f;
    return EVT_RETURN_DONE;
}
