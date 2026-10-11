// proto: USER_FUNC(fune_yure_func_init);
USER_FUNC(fune_yure_func_init) {
    *(f32*)&event->lwData[0] = evtGetFloat(event, event->args[0]);
    return EVT_RETURN_DONE;
}
