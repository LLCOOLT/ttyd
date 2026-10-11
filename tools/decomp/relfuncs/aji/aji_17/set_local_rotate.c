// include: manager/evtmgr_cmd.h
// decl: typedef struct DanceData { u16 flags; u8 step; u8 movePos; f32 cx; f32 cy; f32 rot; } DanceData;
// decl: DanceData dance_dt;
// proto: USER_FUNC(set_local_rotate);
USER_FUNC(set_local_rotate) {
    f64 rot = evtGetFloat(event, event->args[0]);
    f32 r = rot;

    dance_dt.rot = rot;
    if (r > 6.2831855f) {
        dance_dt.rot = r - 6.2831855f;
    }
    if (dance_dt.rot < 0.0f) {
        dance_dt.rot += 6.2831855f;
    }
    return EVT_RETURN_DONE;
}
