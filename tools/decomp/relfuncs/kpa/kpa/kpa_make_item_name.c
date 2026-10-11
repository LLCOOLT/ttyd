// include: manager/evtmgr_cmd.h
// include: stdio.h
// proto: USER_FUNC(kpa_make_item_name);
USER_FUNC(kpa_make_item_name) {
    static char name[16];
    static s32 no;
    s32* args = event->args;

    sprintf(name, "item%2x", no);
    no++;
    evtSetValue(event, args[0], (s32)name);
    return EVT_RETURN_DONE;
}
