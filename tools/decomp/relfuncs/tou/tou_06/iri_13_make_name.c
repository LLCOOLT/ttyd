// include: stdio.h
// decl: s32* tbl;
// proto: USER_FUNC(iri_13_make_name);
USER_FUNC(iri_13_make_name) {
    static char name[8];
    s32* args = event->args;

    sprintf(name, "pants%02d", evtGetValue(event, args[0]));
    evtSetValue(event, args[1], (s32)name);
    return EVT_RETURN_DONE;
}
