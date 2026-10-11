// include: driver/camdrv.h
// proto: USER_FUNC(camps25);
USER_FUNC(camps25) {
    f32 fovY = 25.0f;

    camGetPtr(4)->fovY = fovY;
    return EVT_RETURN_DONE;
}
