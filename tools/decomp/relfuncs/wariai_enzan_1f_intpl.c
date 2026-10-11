// include: manager/evtmgr_cmd.h
// include: system.h
// proto: static USER_FUNC(wariai_enzan_1f_intpl);
static USER_FUNC(wariai_enzan_1f_intpl) {
    s32* args = event->args;
    f32 a = evtGetFloat(event, args[0]) - 1.0f;
    f32 b = evtGetFloat(event, args[1]);
    f32 c = evtGetFloat(event, args[2]);
    f32 d = evtGetFloat(event, args[3]);
    s32 out = args[4];
    f32 t = evtGetFloat(event, args[5]);
    f32 r;

    if (t >= 14.0f) {
        t -= 14.0f;
        if (t >= 14.0f) {
            evtSetFloat(event, out, c);
            return EVT_RETURN_DONE;
        }
        r = 1.0f - intplGetValue(t, b - a, b, 1.0f, 0.0f);
    } else {
        r = intplGetValue(t, b - a, b, 0.0f, 1.0f);
    }
    evtSetFloat(event, out, (1.0f - r) * c + r * d);
    return EVT_RETURN_DONE;
}
