// include: manager/evtmgr_cmd.h
// decl: typedef struct DanceData { u16 flags; u8 step; u8 movePos; f32 cx; f32 cy; f32 rot; } DanceData;
// decl: DanceData dance_dt;
// proto: USER_FUNC(get_center);
USER_FUNC(get_center) {
    s32* args = event->args;

    evtSetFloat(event, args[0], dance_dt.cx);
    evtSetFloat(event, args[1], dance_dt.cy);
    return EVT_RETURN_DONE;
}
