// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(_leg_smoke_effect);
struct EffectEntry* effKemuri9N64Entry(s32 type, s32 arg1, s32 arg2, f32 x, f32 y, f32 z, f32 arg6, f32 arg7);

USER_FUNC(_leg_smoke_effect) {
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);

    effKemuri9N64Entry(1, 18, 90, x, y, z, 60.0f, 0.0f);
    return EVT_RETURN_DONE;
}
