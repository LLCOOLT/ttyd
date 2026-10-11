// include: manager/evtmgr_cmd.h
// decl: void yuunpc_wp_flag_off(s32 flag);
// proto: USER_FUNC(yuunpc_go);
USER_FUNC(yuunpc_go) {
    yuunpc_wp_flag_off(1);
    return EVT_RETURN_DONE;
}
