// include: manager/evtmgr_cmd.h
// decl: typedef struct DanceData { u16 flags; u8 step; u8 movePos; f32 cx; f32 cy; f32 rot; } DanceData;
// decl: DanceData dance_dt;
// proto: USER_FUNC(dance_get_step);
USER_FUNC(dance_get_step) {
    evtSetValue(event, event->args[0], dance_dt.step);
    return EVT_RETURN_DONE;
}
