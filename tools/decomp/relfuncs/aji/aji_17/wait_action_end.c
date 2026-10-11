// include: manager/evtmgr_cmd.h
// decl: typedef struct DanceData { u16 flags; u8 step; u8 movePos; f32 cx; f32 cy; f32 rot; } DanceData;
// decl: DanceData dance_dt;
// proto: USER_FUNC(wait_action_end);
USER_FUNC(wait_action_end) {
    return (dance_dt.flags & 2) ? EVT_RETURN_BLOCK : EVT_RETURN_DONE;
}
