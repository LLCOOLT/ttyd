// proto: USER_FUNC(kpa_get_level);
s32 kpaGetLevel(void);

USER_FUNC(kpa_get_level) {
    s32* args = event->args;
    evtSetValue(event, args[0], kpaGetLevel());
    return EVT_RETURN_DONE;
}
