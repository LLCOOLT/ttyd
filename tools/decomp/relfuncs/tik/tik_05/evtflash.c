// include: driver/fadedrv.h
// include: mario/mariost.h
// include: dolphin/os.h
// proto: static USER_FUNC(evtflash);
static USER_FUNC(evtflash) {
    s32* args = event->args;
    s32 in = evtGetValue(event, args[0]);
    s32 wait = evtGetValue(event, args[1]);
    s32 out = evtGetValue(event, args[2]);

    if (isFirstCall) {
        event->userdata[2] = 0;
    }
    switch (event->userdata[2]) {
        case 0: {
            GXColor color = {0xFF, 0xFF, 0xFF, 0xFF};
            fadeEntry(10, in, color);
            event->userdata[2]++;
        }
        case 1:
            if (fadeIsFinish() != TRUE) {
                return EVT_RETURN_BLOCK;
            }
            event->userdata[0] = wait;
            event->savedTime = (s32)gp->renderTime;
            event->userdata[2]++;
            if (event->userdata[0] == 0) {
                event->userdata[2]++;
            }
            return EVT_RETURN_BLOCK;
        case 2:
            if (OSTicksToMilliseconds((u32)gp->renderTime - (u32)event->savedTime) < (u32)event->userdata[0]) {
                return EVT_RETURN_BLOCK;
            }
            event->userdata[2]++;
            return EVT_RETURN_BLOCK;
        case 3: {
            GXColor color = {0xFF, 0xFF, 0xFF, 0xFF};
            fadeEntry(9, out, color);
            event->userdata[2]++;
        }
        case 4:
            if (fadeIsFinish() != TRUE) {
                return EVT_RETURN_BLOCK;
            }
            return EVT_RETURN_DONE;
    }
    return EVT_RETURN_DONE;
}
