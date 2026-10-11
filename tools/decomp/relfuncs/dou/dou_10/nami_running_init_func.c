// proto: USER_FUNC(nami_running_init_func);
USER_FUNC(nami_running_init_func) {
    f32* lwf = (f32*)event->lwData;

    lwf[6] = event->lwData[11];
    lwf[7] = event->lwData[12];
    lwf[8] = event->lwData[13];
    return EVT_RETURN_DONE;
}
