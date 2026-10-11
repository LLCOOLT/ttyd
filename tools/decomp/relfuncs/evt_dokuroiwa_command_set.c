// decl: s32* command_work;
// proto: USER_FUNC(evt_dokuroiwa_command_set);
USER_FUNC(evt_dokuroiwa_command_set) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);

    if (index < 7) {
        command_work[index] = evtGetValue(event, args[1]);
    }
    return EVT_RETURN_DONE;
}
