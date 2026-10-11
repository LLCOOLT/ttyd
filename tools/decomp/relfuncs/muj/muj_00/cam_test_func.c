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

    evtSetValue(event, args[0], dist * s + 70.0f);
    evtSetValue(event, args[1], 0.0f - dist * c);
    return EVT_RETURN_DONE;
}
