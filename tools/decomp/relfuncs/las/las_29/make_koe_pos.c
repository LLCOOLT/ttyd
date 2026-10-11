// include: manager/evtmgr_cmd.h
// decl: int rand(void);
// proto: USER_FUNC(make_koe_pos);
USER_FUNC(make_koe_pos) {
    s32* args = event->args;
    s32 a = ((rand() >> 1) % 41) * 10;
    s32 b = ((rand() >> 1) % 33) * 10;
    s32 x = a - 200;
    s32 y = b - 190;

    if (x > 0) {
        x += rand() % 10;
    } else {
        x -= rand() % 10;
    }
    if (y > 0) {
        y += rand() % 10;
    } else {
        y += rand() % 10;
    }
    evtSetValue(event, args[0], x);
    evtSetValue(event, args[1], y);
    evtSetValue(event, args[2], 0);
    return EVT_RETURN_DONE;
}
