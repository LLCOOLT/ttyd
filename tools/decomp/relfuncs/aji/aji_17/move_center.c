// include: manager/evtmgr.h
// include: manager/evtmgr_cmd.h
// include: mario/mariost.h
// include: dolphin/os.h
// include: system.h
// decl: typedef struct DanceData { u16 flags; u8 step; u8 movePos; f32 cx; f32 cy; f32 rot; } DanceData;
// decl: DanceData dance_dt;
// proto: USER_FUNC(move_center);
USER_FUNC(move_center) {
    s32* args = event->args;
    f32 x0 = evtGetFloat(event, args[0]);
    f32 z0 = evtGetFloat(event, args[1]);
    f32 x1 = evtGetFloat(event, args[2]);
    f32 z1 = evtGetFloat(event, args[3]);
    s32 frames = evtGetValue(event, args[4]);
    OSTime now = gp->renderTime;
    s32 elapsed;

    if (isFirstCall) {
        dance_dt.flags |= 4;
        event->userdata[0] = ((u64)now >> 32) & 0xFFFFFFFF;
        event->userdata[1] = now & 0xFFFFFFFF;
        return EVT_RETURN_BLOCK;
    }
    elapsed = OSTicksToMilliseconds((u64)(s32)((u32)now - event->userdata[1]));
    if (elapsed < frames) {
        dance_dt.cx = intplGetValue(11, elapsed, frames, x0, x1);
        dance_dt.cy = intplGetValue(11, elapsed, frames, z0, z1);
        return EVT_RETURN_BLOCK;
    }
    dance_dt.cx = x1;
    dance_dt.cy = z1;
    dance_dt.flags &= ~4;
    if (++dance_dt.step >= 3) {
        dance_dt.step = 0;
    }
    return EVT_RETURN_DONE;
}
