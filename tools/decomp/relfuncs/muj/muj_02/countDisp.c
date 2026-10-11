// include: driver/dispdrv.h
// include: driver/camdrv.h
// decl: void printCount(CameraId camera, void* param);
// include: manager/fontmgr.h
// include: driver/camdrv.h
// include: stdio.h
// decl: void FontDrawStringPitch(f32 x, f32 y, f32 pitch, const char* str);
// decl: void FontDrawScale(f32 scale);
// proto: USER_FUNC(countDisp);
// printCount comes first so the deferred compile emits both functions in the original order
void printCount(CameraId camera, void* param) {
    char buf[36];
    s32 n;

    // %3d回
    n = evtGetValue(NULL, GW(0));
    sprintf(buf, "%3d\x89\xF1", n);
    FontDrawStart();
    FontDrawStringPitch(90.0f, 120.0f, 20.0f, buf);
    // かい
    n = evtGetValue(NULL, GW(0));
    sprintf(buf, "\x82\xA9\x82\xA2", n);
    FontDrawScale(0.55f);
    FontDrawStringPitch(148.0f, 131.0f, 20.0f, buf);
}

USER_FUNC(countDisp) {
    dispEntry(CAMERA_2D, 399.0f, 0, printCount, NULL);
    return EVT_RETURN_BLOCK;
}
