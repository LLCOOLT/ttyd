// include: manager/evtmgr_cmd.h
// decl: void* effMiniGameEntry(s32 type, f32 x, f32 y, f32 z);
// proto: USER_FUNC(eff_call_minigame);
USER_FUNC(eff_call_minigame) {
    s32* args = event->args;
    s32 type = evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);

    effMiniGameEntry(type, x, y, z);
    return EVT_RETURN_DONE;
}
