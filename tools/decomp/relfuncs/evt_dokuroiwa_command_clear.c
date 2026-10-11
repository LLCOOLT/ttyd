// include: string.h
// decl: s32* command_work;
// proto: USER_FUNC(evt_dokuroiwa_command_clear);
USER_FUNC(evt_dokuroiwa_command_clear) {
    memset(command_work, 0, 7 * sizeof(s32));
    return EVT_RETURN_DONE;
}
