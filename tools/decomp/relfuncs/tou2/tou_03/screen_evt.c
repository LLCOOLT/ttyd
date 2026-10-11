// include: driver/dispdrv.h
// decl: static void screen_capture(CameraId cameraId, void* param);
// proto: static USER_FUNC(screen_evt);
static USER_FUNC(screen_evt) {
    dispEntry(CAMERA_2D, 1000.0f, 0, screen_capture, NULL);
    return EVT_RETURN_BLOCK;
}
