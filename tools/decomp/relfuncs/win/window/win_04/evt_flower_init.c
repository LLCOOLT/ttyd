// include: memory.h
// proto: USER_FUNC(evt_flower_init);
USER_FUNC(evt_flower_init) {
    FlowerWork* wp = _mapAlloc(sizeof(FlowerWork));

    wp->count = 55;
    wp->flowers = _mapAlloc(wp->count * sizeof(Flower));
    event->lwData[10] = (s32)wp;
    return EVT_RETURN_DONE;
}
