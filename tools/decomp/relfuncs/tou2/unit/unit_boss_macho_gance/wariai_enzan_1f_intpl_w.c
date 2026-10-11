// include: manager/evtmgr_cmd.h
// decl: f32 intplGetValue(s32 mode, s32 currStep, f32 start, f32 end, s32 steps);
// proto: USER_FUNC(wariai_enzan_1f_intpl_w);
USER_FUNC(wariai_enzan_1f_intpl_w) {
    s32* args = event->args;
    f32 a = evtGetFloat(event, args[0]) - 1.0f;
    f32 b = evtGetFloat(event, args[1]);
    f32 c = evtGetFloat(event, args[2]);
    f32 d = evtGetFloat(event, args[3]);
    s32 out = args[4];
    f32 t1 = evtGetFloat(event, args[5]);
    f32 t2 = evtGetFloat(event, args[6]);
    f32 r1;
    f32 r2;
    f32 w;

    if (t1 >= 14.0f) {
        t1 -= 14.0f;
        if (t1 >= 14.0f) {
            evtSetFloat(event, out, c);
            return EVT_RETURN_DONE;
        }
        r1 = 1.0f - intplGetValue(t1, b - a, 1.0f, 0.0f, b);
    } else {
        r1 = intplGetValue(t1, b - a, 0.0f, 1.0f, b);
    }
    if (t2 >= 14.0f) {
        t2 = t1 - 14.0f;
        if (t2 >= 14.0f) {
            evtSetFloat(event, out, c);
            return EVT_RETURN_DONE;
        }
        r2 = 1.0f - intplGetValue(t2, b - a, 1.0f, 0.0f, b);
    } else {
        r2 = intplGetValue(t2, b - a, 0.0f, 1.0f, b);
    }
    w = r1 * r2;
    evtSetFloat(event, out, c * (1.0f - w) + d * w);
    return EVT_RETURN_DONE;
}
