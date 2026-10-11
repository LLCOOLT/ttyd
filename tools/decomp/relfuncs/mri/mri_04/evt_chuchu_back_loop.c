// include: driver/npcdrv.h
// include: evt/evt_npc.h
// include: mario/mariost.h
// include: system.h
// proto: USER_FUNC(evt_chuchu_back_loop);
USER_FUNC(evt_chuchu_back_loop) {
    s32* args = event->args;
    // チュチュリーナ
    NpcEntry* npc = evtNpcNameToPtr(event, "\x83\x60\x83\x85\x83\x60\x83\x85\x83\x8A\x81\x5B\x83\x69");
    s32 total = evtGetValue(event, args[0]);
    s32 elapsed;

    if (isFirstCall) {
        event->userdata[0] = gp->renderTime;
    }
    elapsed = OSTicksToMilliseconds((u32)gp->renderTime - event->userdata[0]);
    if (elapsed < total) {
        npc->rotation.z = intplGetValue(11, elapsed, total, 0.0f, 360.0f);
        return EVT_RETURN_BLOCK;
    }
    npc->rotation.z = 0.0f;
    return EVT_RETURN_DONE;
}
