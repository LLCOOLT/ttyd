// decl: void bgTransOffsetOn(void);
// decl: void bgTransOffsetOff(void);
// proto: static USER_FUNC(bgScrollControll);
static USER_FUNC(bgScrollControll) {
    if (evtGetValue(event, event->args[0]) == 0) {
        bgTransOffsetOff();
    } else {
        bgTransOffsetOn();
    }
    return EVT_RETURN_DONE;
}
