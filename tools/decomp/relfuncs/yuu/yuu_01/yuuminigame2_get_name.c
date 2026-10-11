// include: manager/evtmgr_cmd.h
// decl: extern s32 s_nametbl[];
// decl: extern s32 a_nametbl[];
// decl: extern s32 turn_tbl[];
// proto: USER_FUNC(yuuminigame2_get_name);
USER_FUNC(yuuminigame2_get_name) {
    s32* args = event->args;
    s32 i = evtGetValue(event, args[0]);

    evtSetValue(event, args[1], s_nametbl[i]);
    evtSetValue(event, args[2], a_nametbl[i]);
    evtSetValue(event, args[3], turn_tbl[i]);
    return EVT_RETURN_DONE;
}
