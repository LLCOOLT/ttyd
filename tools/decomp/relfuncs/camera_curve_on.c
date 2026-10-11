// proto: USER_FUNC(camera_curve_on);
void camRoadCurveOn(const char* name);

USER_FUNC(camera_curve_on) {
    camRoadCurveOn("|MarioSt_CameraRoad|curve2");
    return EVT_RETURN_DONE;
}
