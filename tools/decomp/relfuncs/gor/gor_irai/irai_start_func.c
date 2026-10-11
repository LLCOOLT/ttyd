// include: manager/evtmgr_cmd.h
// decl: void irai_flag_clear(void);
// proto: USER_FUNC(irai_start_func);
USER_FUNC(irai_start_func) {
    irai_flag_clear();
    return EVT_RETURN_DONE;
}
