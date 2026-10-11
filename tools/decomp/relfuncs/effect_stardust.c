// include: eff/eff_stardust.h
// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(effect_stardust);
USER_FUNC(effect_stardust) {
    s32* args = event->args;
    s32 type = evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);
    f32 arg6 = evtGetFloat(event, args[4]);
    f32 arg7 = evtGetFloat(event, args[5]);
    s32 arg1 = evtGetValue(event, args[6]);
    s32 arg2 = evtGetValue(event, args[7]);

    effStardustEntry(type, arg1, arg2, x, y, z, arg6, arg7);
    return EVT_RETURN_DONE;
}
