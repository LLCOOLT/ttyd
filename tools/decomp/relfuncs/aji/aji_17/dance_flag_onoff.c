// include: manager/evtmgr_cmd.h
// decl: typedef struct DanceData { u16 flags; u8 step; u8 movePos; f32 cx; f32 cy; f32 rot; } DanceData;
// decl: DanceData dance_dt;
// proto: USER_FUNC(dance_flag_onoff);
USER_FUNC(dance_flag_onoff) {
    s32* args = event->args;
    s32 mask = evtGetValue(event, args[0]);
    s32 on = evtGetValue(event, args[1]);

    if (on) {
        dance_dt.flags |= mask;
    } else {
        dance_dt.flags &= ~mask;
    }
    return EVT_RETURN_DONE;
}
