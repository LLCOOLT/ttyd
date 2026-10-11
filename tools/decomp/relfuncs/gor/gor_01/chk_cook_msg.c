// include: manager/evtmgr_cmd.h
// decl: s32 chk_cook_eff_type(s32 item);
// proto: USER_FUNC(chk_cook_msg);
USER_FUNC(chk_cook_msg) {
    s32* args = event->args;
    s32 item = evtGetValue(event, args[0]);
    s32 msg;

    if (item == 195 || item == 196) {
        msg = 0;
    } else if ((item >= 193 && item <= 197) || item == 232 || item == 200) {
        msg = 1;
    } else if (item == 182) {
        msg = 2;
    } else {
        msg = chk_cook_eff_type(item) + 3;
    }
    evtSetValue(event, args[1], msg);
    return EVT_RETURN_DONE;
}
