// include: system.h
// proto: USER_FUNC(fune_yure_func);
USER_FUNC(fune_yure_func) {
    s32* args = event->args;
    s32 dir = evtGetValue(event, args[0]);
    f32 amp = evtGetFloat(event, args[1]);
    s32 done;
    f32 step;

    if (0.0f == amp) {
        evtSetFloat(event, args[2], 0.0f);
        evtSetValue(event, args[3], 1);
        return EVT_RETURN_DONE;
    }
    done = 0;
    step = 2.0f * amp / sysMsec2FrameFloat(2000.0f);
    if (dir == 0) {
        *(f32*)&event->lwData[0] += step;
        if (*(f32*)&event->lwData[0] >= amp) {
            *(f32*)&event->lwData[0] = amp;
            done = 1;
        }
    } else {
        *(f32*)&event->lwData[0] -= step;
        if (*(f32*)&event->lwData[0] <= -amp) {
            *(f32*)&event->lwData[0] = -amp;
            done = 1;
        }
    }
    evtSetFloat(event, args[2], *(f32*)&event->lwData[0]);
    evtSetValue(event, args[3], done);
    return EVT_RETURN_DONE;
}
