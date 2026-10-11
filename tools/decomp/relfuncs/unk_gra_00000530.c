// proto: USER_FUNC(unk_gra_00000530);
s32 unk_8009fcbc(void);

USER_FUNC(unk_gra_00000530) {
    s32* args = event->args;
    evtSetValue(event, args[0], unk_8009fcbc() == 0);
    return EVT_RETURN_DONE;
}
