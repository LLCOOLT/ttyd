// proto: USER_FUNC(mugen_kairou_get_list);
USER_FUNC(mugen_kairou_get_list) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);

    evtSetValue(event, args[1], mugen_kairou_list[index]);
    return EVT_RETURN_DONE;
}
