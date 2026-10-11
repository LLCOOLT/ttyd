// include: driver/camdrv.h
// proto: USER_FUNC(camps30);
USER_FUNC(camps30) {
    f32 fovY = 30.0f;

    camGetPtr(4)->fovY = fovY;
    return EVT_RETURN_DONE;
}
