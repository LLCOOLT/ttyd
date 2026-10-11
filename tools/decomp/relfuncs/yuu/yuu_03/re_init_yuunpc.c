// include: manager/evtmgr_cmd.h
// decl: void ext_yuunpc_minigame4_init_sub(void);
// proto: USER_FUNC(re_init_yuunpc);
USER_FUNC(re_init_yuunpc) {
    ext_yuunpc_minigame4_init_sub();
    return EVT_RETURN_DONE;
}
