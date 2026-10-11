// decl: void N_mapDispOn(void);
// decl: void N_mapDispOff(void);
// proto: USER_FUNC(unk_tik_0000247c);
USER_FUNC(unk_tik_0000247c) {
    if (evtGetValue(event, event->args[0])) {
        N_mapDispOn();
    } else {
        N_mapDispOff();
    }
    return EVT_RETURN_DONE;
}
