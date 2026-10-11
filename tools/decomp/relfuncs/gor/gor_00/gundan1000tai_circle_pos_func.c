// include: system.h
// decl: double sin(double x);
// decl: double cos(double x);
// proto: USER_FUNC(gundan1000tai_circle_pos_func);
USER_FUNC(gundan1000tai_circle_pos_func) {
    s32* args = event->args;
    f32 radius = irand(180) + 120;
    f32 angle = 6.2831855f * irand(360) / 360.0f;
    f32 s = sin(angle);
    f32 c = cos(angle);

    evtSetFloat(event, args[0], 0.9f * (radius * s));
    evtSetFloat(event, args[1], 15.0f);
    evtSetFloat(event, args[2], 0.5f * (radius * c) - 300.0f);
    return EVT_RETURN_DONE;
}
