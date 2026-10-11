// proto: USER_FUNC(majinaisi_ryokin_kaisu);
USER_FUNC(majinaisi_ryokin_kaisu) {
    s32* args = event->args;
    s32 idx = evtGetValue(event, args[0]);
    evtSetValue(event, args[1], majinaisi_ryokin_kaisu_tbl[idx * 2]);
    evtSetValue(event, args[2], majinaisi_ryokin_kaisu_tbl[idx * 2 + 1]);
    return EVT_RETURN_DONE;
}
