// include: manager/evtmgr_cmd.h
// decl: typedef struct KpaWork { u8 stage; u8 lives; u8 time; } KpaWork;
// decl: KpaWork* kwp;
// proto: USER_FUNC(kpa_set_time);
USER_FUNC(kpa_set_time) {
    s32* args = event->args;
    s32 sec = evtGetValue(event, args[0]) / 1000;
    s32 time = 180 - (sec + evtGetValue(event, args[1]) * 10);

    if (time < 0) {
        time = 0;
    }
    kwp->time = time;
    evtSetValue(event, args[2], time);
    return EVT_RETURN_DONE;
}
