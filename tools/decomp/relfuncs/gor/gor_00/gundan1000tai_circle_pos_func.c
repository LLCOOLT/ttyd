// include: system.h
// decl: double sin(double x);
// decl: double cos(double x);
// proto: USER_FUNC(gundan1000tai_circle_pos_func);
USER_FUNC(gundan1000tai_circle_pos_func) {
    f32 radius;
    f32 s;
    f32 c;
    f32 angle;
    s32* args = event->args;

    radius = irand(180) + 120;
    angle = 6.2831855f * irand(360) / 360.0f;
    s = sin(angle);
    c = cos(angle);

    evtSetFloat(event, args[0], 0.9f * (radius * s));
    evtSetFloat(event, args[1], 15.0f);
    evtSetFloat(event, args[2], 0.5f * (radius * c) - 300.0f);
    return EVT_RETURN_DONE;
}
