// include: manager/evtmgr_cmd.h
// include: stdio.h
// include: party.h
// proto: USER_FUNC(make_koe_label);
USER_FUNC(make_koe_label) {
    static char name[32];
    s32* args = event->args;
    s32 n = evtGetValue(event, args[0]);

    if (n == 18 && !partyChkJoin(7)) {
        n = 1;
        evtSetValue(event, args[0], 1);
    }
    sprintf(name, "stg8_las_148_74_%02d", n + 1);
    evtSetValue(event, args[1], (s32)name);
    return EVT_RETURN_DONE;
}
