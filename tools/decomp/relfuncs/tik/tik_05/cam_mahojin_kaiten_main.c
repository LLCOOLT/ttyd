// include: mario/mariost.h
// include: system.h
// include: dolphin/os.h
// proto: USER_FUNC(cam_mahojin_kaiten_main);
USER_FUNC(cam_mahojin_kaiten_main) {
    s32 frames;
    s32 msec;
    s32* args = event->args;
    f32 start = evtGetFloat(event, args[0]);
    f32 end = evtGetFloat(event, args[1]);
    s32 cont;
    f32 cur;
    f32 total;
    f32 speed;
    s32 elapsed;
    s32 i;

    msec = evtGetValue(event, args[2]);
    frames = sysMsec2Frame(msec);
    cont = 1;

    if (event->lwData[15] == 0) {
        event->lwData[14] = 0;
        event->lwData[15] = 1;
        event->savedTime = gp->renderTime;
    }
    total = 0.0f;
    speed = total;
    for (i = 0; i < frames; i++) {
        if (i <= frames * 20 / 100) {
            speed += 1.0f;
        } else if (i >= frames * 80 / 100) {
            speed -= 1.0f;
        }
        total += speed;
        if (i == event->lwData[14]) {
            cur = total;
        }
    }
    elapsed = OSTicksToMilliseconds((u32)gp->renderTime - (u32)event->savedTime);
    if (elapsed > msec) {
        elapsed = msec;
    }
    event->lwData[14] = sysMsec2Frame(elapsed);
    if (frames == event->lwData[14]) {
        cont = 0;
    }
    evtSetFloat(event, args[3], start + cur * (end - start) / total);
    evtSetValue(event, args[4], cont);
    return EVT_RETURN_DONE;
}
