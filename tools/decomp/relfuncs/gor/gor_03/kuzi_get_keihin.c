// proto: USER_FUNC(kuzi_get_keihin);
USER_FUNC(kuzi_get_keihin) {
    s32* args = event->args;
    s32 item;

    switch (evtGetValue(event, args[0])) {
        case 0:
            if (!evtGetValue(NULL, GSWF(1238))) {
                item = 0x104;
                evtSetValue(NULL, GSWF(1238), 1);
            } else {
                item = 0xC4;
            }
            break;
        case 1:
            if (!evtGetValue(NULL, GSWF(1239))) {
                item = 0x12F;
                evtSetValue(NULL, GSWF(1239), 1);
            } else {
                item = 0xC2;
            }
            break;
        case 2:
            item = 0x96;
            break;
        case 3:
            item = 0x97;
            break;
        default:
            item = 0x94;
            break;
    }
    evtSetValue(event, args[1], item);
    return EVT_RETURN_DONE;
}
