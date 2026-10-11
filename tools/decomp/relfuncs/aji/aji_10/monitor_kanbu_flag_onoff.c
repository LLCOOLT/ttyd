// include: manager/evtmgr_cmd.h
// decl: typedef struct MonitorWork { void* buf; s32 ready; s32 kanbu; } MonitorWork;
// decl: static MonitorWork* monitor_wp;
// proto: USER_FUNC(monitor_kanbu_flag_onoff);
USER_FUNC(monitor_kanbu_flag_onoff) {
    monitor_wp->kanbu = evtGetValue(event, event->args[0]);
    return EVT_RETURN_DONE;
}
