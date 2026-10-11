// proto: USER_FUNC(camera_curve_off);
void camRoadCurveOff(const char* name);

USER_FUNC(camera_curve_off) {
    camRoadCurveOff("|MarioSt_CameraRoad|curve2");
    return EVT_RETURN_DONE;
}
