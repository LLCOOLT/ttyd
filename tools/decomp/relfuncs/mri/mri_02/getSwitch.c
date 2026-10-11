// proto: USER_FUNC(getSwitch);
USER_FUNC(getSwitch) {
    s32* args = event->args;
    s32 on = FALSE;

    if (mri02switch.pos <= -10.0f) {
        on = TRUE;
    }
    evtSetValue(event, args[0], on);
    return EVT_RETURN_DONE;
}
