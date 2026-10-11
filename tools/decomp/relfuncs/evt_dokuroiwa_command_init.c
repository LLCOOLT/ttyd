// include: string.h
// include: memory.h
// decl: s32* command_work;
// proto: USER_FUNC(evt_dokuroiwa_command_init);
USER_FUNC(evt_dokuroiwa_command_init) {
    command_work = _mapAlloc(7 * sizeof(s32));
    memset(command_work, 0, 7 * sizeof(s32));
    return EVT_RETURN_DONE;
}
