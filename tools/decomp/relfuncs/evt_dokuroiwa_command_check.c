// decl: s32* command_work;
// proto: USER_FUNC(evt_dokuroiwa_command_check);
USER_FUNC(evt_dokuroiwa_command_check) {
    s32 result;
    s32 i;
    s32* args = event->args;

    for (i = 0; i < 7; i++) {
    }
    result = 2;
    for (i = 0; i < 7; i++) {
        s32 cmd = command_work[i];
        if (cmd == 0) {
            result = 0;
            break;
        }
        if (cmd != command_seikai[i]) {
            result = 1;
            break;
        }
    }
    evtSetValue(event, args[0], result);
    return EVT_RETURN_DONE;
}
