// include: seq/seq_demo.h
// include: driver/dispdrv.h
// include: string.h
// decl: void movie_draw(CameraId camera, void* param);
// proto: USER_FUNC(movie);
USER_FUNC(movie) {
    u32 type;

    if (isFirstCall) {
        memset(DIG_WP, 0, 4);
        evtSetValue(event, GF(0), FALSE);
    }
    EXIGetType(0, 2, &type);
    if (type != 0x05070000) {
        if ((u32)*DIG_WP >= THPSimpleGetTotalFrame() - 2) {
            evtSetValue(event, GF(0), TRUE);
        }
    } else if (*DIG_WP >= 300) {
        evtSetValue(event, GF(0), TRUE);
    }
    dispEntry(CAMERA_3D, 0.0f, 3, movie_draw, NULL);
    return EVT_RETURN_BLOCK;
}
