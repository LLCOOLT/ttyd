// proto: USER_FUNC(evt_flower_end);
USER_FUNC(evt_flower_end) {
    FlowerWork* wp = (FlowerWork*)event->lwData[10];
    Flower* fl = wp->flowers;
    s32 i;

    for (i = 0; i < wp->count; i++, fl++) {
        fl->state = 0;
    }
    return EVT_RETURN_DONE;
}
