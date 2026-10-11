// include: driver/dispdrv.h
// decl: void icon_disp(CameraId camera, void* param);
// proto: USER_FUNC(evt_sousa_icon);
USER_FUNC(evt_sousa_icon) {
    s32* args = event->args;
    s32 type = evtGetValue(event, args[0]);
    s32 x = evtGetValue(event, args[1]);
    s32 y = evtGetValue(event, args[2]);

    event->userdata[0] = type;
    event->userdata[1] = x;
    event->userdata[2] = y;
    dispEntry(CAMERA_2D, 0.0f, 0, icon_disp, event);
    return EVT_RETURN_YIELD;
}
