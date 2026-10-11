// include: manager/evtmgr_cmd.h
// decl: typedef struct KpaWork { u8 stage; u8 lives; u8 time; } KpaWork;
// decl: KpaWork* kwp;
// proto: USER_FUNC(kpa_status_get_stage);
USER_FUNC(kpa_status_get_stage) {
    evtSetValue(event, event->args[0], kwp->stage);
    return EVT_RETURN_DONE;
}
