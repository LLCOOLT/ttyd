// proto: USER_FUNC(evt_goki_sub_intpl_init);
USER_FUNC(evt_goki_sub_intpl_init) {
    s32* args = event->args;
    s32 mode = evtGetValue(event, args[0]);
    s32 x0 = evtGetValue(event, args[1]);
    s32 x1 = evtGetValue(event, args[2]);
    s32 y0 = evtGetValue(event, args[3]);
    s32 y1 = evtGetValue(event, args[4]);
    s32 steps = evtGetValue(event, args[5]);

    event->lwData[9] = mode;
    event->lwData[10] = x0;
    event->lwData[11] = x1;
    event->lwData[12] = y0;
    event->lwData[13] = y1;
    event->lwData[14] = 0;
    event->lwData[15] = steps;
    return EVT_RETURN_DONE;
}
