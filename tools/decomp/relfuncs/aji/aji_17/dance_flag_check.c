// include: manager/evtmgr_cmd.h
// decl: typedef struct DanceData { u16 flags; u8 step; u8 movePos; f32 cx; f32 cy; f32 rot; } DanceData;
// decl: DanceData dance_dt;
// proto: USER_FUNC(dance_flag_check);
USER_FUNC(dance_flag_check) {
    s32* args = event->args;
    s32 mask = evtGetValue(event, args[0]);

    if (dance_dt.flags & mask) {
        evtSetValue(event, args[1], 1);
    } else {
        evtSetValue(event, args[1], 0);
    }
    return EVT_RETURN_DONE;
}
