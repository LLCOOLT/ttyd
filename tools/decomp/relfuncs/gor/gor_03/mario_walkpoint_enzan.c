// include: dolphin/mtx.h
// proto: USER_FUNC(mario_walkpoint_enzan);
USER_FUNC(mario_walkpoint_enzan) {
    s32* args = event->args;
    Vec a;
    Vec b;
    Vec d;
    f32 dist;

    a.x = evtGetFloat(event, args[0]);
    a.y = 0.0f;
    a.z = evtGetFloat(event, args[1]);
    b.x = evtGetFloat(event, args[2]);
    b.y = 0.0f;
    b.z = evtGetFloat(event, args[3]);
    dist = evtGetFloat(event, args[4]);
    PSVECSubtract(&a, &b, &d);
    PSVECNormalize(&d, &d);
    PSVECScale(&d, &d, dist);
    PSVECAdd(&d, &b, &d);
    evtSetFloat(event, args[5], d.x);
    evtSetFloat(event, args[6], d.z);
    return EVT_RETURN_DONE;
}
