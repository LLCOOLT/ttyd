// include: driver/msgdrv.h
// proto: USER_FUNC(get_password);
USER_FUNC(get_password) {
    s32* args = event->args;

    evtSetValue(event, args[0], (s32)msgSearch("stg7_aji_password"));
    return EVT_RETURN_DONE;
}
