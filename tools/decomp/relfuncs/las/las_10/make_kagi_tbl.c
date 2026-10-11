// include: mario/mario_pouch.h
// proto: USER_FUNC(make_kagi_tbl);
USER_FUNC(make_kagi_tbl) {
    s32* args = event->args;
    s32 n = 0;
    s32 i;

    for (i = 0; i < 8; i++) {
        if ((s32)pouchCheckItem(i + 0x26) > 0) {
            kagi_tbl[n++] = i + 0x26;
        }
    }
    kagi_tbl[n] = -1;
    evtSetValue(event, args[0], (s32)kagi_tbl);
    evtSetValue(event, args[1], n);
    return EVT_RETURN_DONE;
}
