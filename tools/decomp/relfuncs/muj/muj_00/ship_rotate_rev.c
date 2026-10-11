// include: manager/evtmgr_cmd.h
// include: system.h
// proto: USER_FUNC(ship_rotate_rev);
USER_FUNC(ship_rotate_rev) {
    s32* args = event->args;
    f32 x1 = evtGetFloat(event, args[0]);
    f32 z1 = evtGetFloat(event, args[1]);
    f32 x2 = evtGetFloat(event, args[2]);
    f32 z2 = evtGetFloat(event, args[3]);

    f32 angle;

    angle = angleABf(x1, -z1, x2, -z2);
    evtSetFloat(event, args[4], 180.0f + (angle - 90.0f));
    return EVT_RETURN_DONE;
}
