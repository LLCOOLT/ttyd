// proto: USER_FUNC(unk_gor_00000104);
USER_FUNC(unk_gor_00000104) {
    unk_gor_bss00000004 = evtGetValue(event, event->args[0]);
    return EVT_RETURN_DONE;
}
