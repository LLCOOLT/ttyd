// include: manager/evtmgr_cmd.h
// decl: typedef struct DanceData { u16 flags; u8 step; u8 movePos; f32 cx; f32 cy; f32 rot; } DanceData;
// decl: DanceData dance_dt;
// proto: USER_FUNC(dance_data_init);
USER_FUNC(dance_data_init) {
    dance_dt.flags = 0;
    dance_dt.cx = 0.0f;
    dance_dt.cy = -80.0f;
    dance_dt.rot = -0.4712389f;
    dance_dt.step = 0;
    dance_dt.movePos = 0;
    return EVT_RETURN_DONE;
}
