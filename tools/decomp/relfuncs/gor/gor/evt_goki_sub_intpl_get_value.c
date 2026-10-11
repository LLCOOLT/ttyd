// include: system.h
// proto: USER_FUNC(evt_goki_sub_intpl_get_value);
USER_FUNC(evt_goki_sub_intpl_get_value) {
    event->lwData[0] = intplGetValue(event->lwData[9], event->lwData[14], event->lwData[15], event->lwData[10], event->lwData[11]);
    event->lwData[1] = intplGetValue(event->lwData[9], event->lwData[14], event->lwData[15], event->lwData[12], event->lwData[13]);
    event->lwData[14]++;
    return EVT_RETURN_DONE;
}
