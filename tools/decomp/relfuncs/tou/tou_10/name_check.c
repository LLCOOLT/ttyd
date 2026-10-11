// include: driver/msgdrv.h
// include: string.h
// proto: USER_FUNC(name_check);
USER_FUNC(name_check) {
    s32* args = event->args;

    // a full-width space
    if (strcmp((const char*)evtGetValue(event, args[0]), "\x81\x40") == 0) {
        evtSetValue(event, args[0], (s32)msgSearch("name_party3"));
    }
    return EVT_RETURN_DONE;
}
