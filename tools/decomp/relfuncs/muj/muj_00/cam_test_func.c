// include: manager/evtmgr_cmd.h
// decl: double sin(double x);
// decl: double cos(double x);
// proto: USER_FUNC(cam_test_func);
USER_FUNC(cam_test_func) {
    s32* args = event->args;
    f32 angle = evtGetFloat(event, args[2]);
    f32 dist = evtGetFloat(event, args[3]);
    f32 rad = 6.2831855f * angle / 360.0f;
    f32 s = sin(rad);
    f32 c = cos(rad);
    Vec center;

    center.x = 70.0f;
    center.y = 110.0f;
    center.z = 0.0f;
    evtSetValue(event, *args++, center.x + dist * s);
    evtSetValue(event, *args++, center.z - dist * c);
    return EVT_RETURN_DONE;
}
