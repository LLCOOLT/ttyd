// include: eff/eff_small_star.h
// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(small_star);
USER_FUNC(small_star) {
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);

    effSmallStarEntry(0, 4, x, 12.5f + y, z, 0.0f, -1.0f, 0.0f);
    return EVT_RETURN_DONE;
}
