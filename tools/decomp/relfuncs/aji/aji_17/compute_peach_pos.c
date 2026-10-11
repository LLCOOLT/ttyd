// include: manager/evtmgr_cmd.h
// decl: typedef struct DanceData { u16 flags; u8 step; u8 movePos; f32 cx; f32 cy; f32 rot; } DanceData;
// decl: DanceData dance_dt;
// decl: double sin(double x);
// decl: double cos(double x);
// proto: USER_FUNC(compute_peach_pos);
USER_FUNC(compute_peach_pos) {
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 z = evtGetFloat(event, args[1]);
    f32 s = sin(dance_dt.rot);
    f32 c = cos(dance_dt.rot);

    evtSetFloat(event, args[2], x + 5.5f * s);
    evtSetFloat(event, args[3], z - 5.5f * c);
    return EVT_RETURN_DONE;
}
