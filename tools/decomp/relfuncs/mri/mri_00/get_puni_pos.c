// include: stdlib.h
// proto: USER_FUNC(get_puni_pos);
USER_FUNC(get_puni_pos) {
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 x;
    s32 z;

    x = (id % 15) * 20 - 280 + rand() % 10;
    z = 180 - ((id / 15) * 20 + rand() % 30 - 15);
    evtSetValue(event, args[1], x);
    evtSetValue(event, args[2], z);
    return EVT_RETURN_DONE;
}
