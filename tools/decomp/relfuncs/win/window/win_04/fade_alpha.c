// include: driver/fadedrv.h
// proto: USER_FUNC(fade_alpha);
USER_FUNC(fade_alpha) {
    s32* args = event->args;
    s32 r = evtGetValue(event, args[0]);
    s32 g = evtGetValue(event, args[1]);
    s32 b = evtGetValue(event, args[2]);
    s32 a = evtGetValue(event, args[3]);

    fadeEntry(13, 0, (GXColor){r, g, b, a});
    return EVT_RETURN_DONE;
}
