// include: manager/evtmgr_cmd.h
// include: driver/swdrv.h
// decl: typedef struct MonosiriFollow { s32 seq; s32* list; s32 count; } MonosiriFollow;
// decl: #define FOLLOW ((MonosiriFollow*)follow)
// proto: USER_FUNC(monosiri_check);
USER_FUNC(monosiri_check) {
    s32* args = event->args;
    s32 seq = evtGetValue(event, GSW(0));
    u32 i;
    s32 j;
    MonosiriFollow* f = FOLLOW;

    for (i = 0; i < sizeof(follow) / sizeof(MonosiriFollow); i++, f++) {
        if (seq < f->seq) {
            break;
        }
        for (j = 0; j < f->count; j++) {
            if (!swGet(f->list[j] + 0x117A)) {
                evtSetValue(event, args[0], 1);
                evtSetValue(event, args[1], f->list[j]);
                return EVT_RETURN_DONE;
            }
        }
    }
    if (swGet(0x4BD) && !swGet(0x1181)) {
        evtSetValue(event, args[0], 1);
        evtSetValue(event, args[1], 7);
        return EVT_RETURN_DONE;
    }
    if (swGet(0x13DD) && !swGet(0x1225)) {
        evtSetValue(event, args[0], 1);
        evtSetValue(event, args[1], 0xAB);
        return EVT_RETURN_DONE;
    }
    if (swGet(0x8B2) && !swGet(0x11C6)) {
        evtSetValue(event, args[0], 1);
        evtSetValue(event, args[1], 0x4C);
        return EVT_RETURN_DONE;
    }
    evtSetValue(event, args[0], 0);
    evtSetValue(event, args[1], 0);
    return EVT_RETURN_DONE;
}
