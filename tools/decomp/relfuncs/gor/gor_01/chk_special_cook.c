// include: manager/evtmgr_cmd.h
// decl: extern s32 special_cook_list[];
// proto: USER_FUNC(chk_special_cook);
USER_FUNC(chk_special_cook) {
    s32* args = event->args;
    s32 item = evtGetValue(event, args[0]);
    s32 found = FALSE;
    s32 i;
    s32 v;

    for (i = 0; (v = special_cook_list[i]) != -1; i++) {
        if (item == v) {
            found = TRUE;
            break;
        }
    }
    evtSetValue(event, args[1], found);
    return EVT_RETURN_DONE;
}
