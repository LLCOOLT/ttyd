// include: manager/evtmgr_cmd.h
// decl: f32 sinfd(f32 degrees);
// decl: f32 reviseAngle(f32 angle);
// proto: USER_FUNC(evt_box_pukapuka);
USER_FUNC(evt_box_pukapuka) {
    s32* args = event->args;
    f32 y;

    if (isFirstCall) {
        event->userdata[0] = 0;
        event->userdata[1] = 0;
    }
    y = 1.5f * sinfd(event->userdata[0]) - 1.5f + (0.7f * sinfd(event->userdata[1]) - 0.7f);
    event->userdata[0] = reviseAngle(event->userdata[0] + 2);
    event->userdata[1] = reviseAngle(event->userdata[1] + 1);
    y -= 25.0f;
    evtSetFloat(event, args[0], y);
    return EVT_RETURN_BLOCK;
}
