// include: system.h
// include: stdlib.h
// include: manager/evtmgr_cmd.h
// decl: f32 sinfd(f32 degrees);
// decl: f32 cosfd(f32 degrees);
// proto: USER_FUNC(_btlgon_get_escape_param);
USER_FUNC(_btlgon_get_escape_param) {
    s32* args = event->args;
    s32 x = evtGetValue(event, args[0]);
    s32 y = evtGetValue(event, args[1]);
    s32 dxVar = args[2];
    s32 dyVar = args[3];
    s32 speedVar = args[4];
    f32 angle = angleABf(100.0f, 205.0f, x, y);
    s32 dx;
    s32 dy;
    f32 speed;

    if (angle > 270.0f && angle < 360.0f) {
        angle = 270.0f;
    }
    if (angle < 90.0f) {
        angle = 90.0f;
    }
    dx = 500.0f * sinfd(angle);
    dy = 500.0f * -cosfd(angle);
    speed = 6.0f + rand() % 6;
    speed = 0.67f * speed;
    evtSetValue(event, dxVar, dx);
    evtSetValue(event, dyVar, dy);
    evtSetFloat(event, speedVar, speed);
    return EVT_RETURN_DONE;
}
