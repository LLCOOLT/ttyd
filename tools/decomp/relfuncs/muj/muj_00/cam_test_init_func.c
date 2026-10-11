// include: manager/evtmgr_cmd.h
// include: dolphin/mtx.h
// decl: double atan2(double y, double x);
// proto: USER_FUNC(cam_test_init_func);
USER_FUNC(cam_test_init_func) {
    s32* args = event->args;
    Vec a;
    Vec b;
    f32 dist;

    a.x = evtGetValue(event, args[0]);
    a.y = 110.0f;
    a.z = evtGetValue(event, args[1]);
    b.x = 70.0f;
    b.y = 110.0f;
    b.z = 0.0f;
    dist = PSVECDistance(&a, &b);
    evtSetFloat(event, args[2], 57.29579f * (f32)atan2(-(b.x - a.x), b.z - a.z));
    evtSetFloat(event, args[3], dist);
    return EVT_RETURN_DONE;
}
