// include: driver/npcdrv.h
// include: evt/evt_npc.h
// include: mario/mariost.h
// include: system.h
// proto: USER_FUNC(evt_chuchu_back_loop);
USER_FUNC(evt_chuchu_back_loop) {
    NpcEntry* npc;
    s32* args = event->args;
    OSTime now;
    s32 total;
    s32 elapsed;

    // チュチュリーナ
    npc = evtNpcNameToPtr(event, "\x83\x60\x83\x85\x83\x60\x83\x85\x83\x8A\x81\x5B\x83\x69");
    total = evtGetValue(event, args[0]);
    if (gp->inBattle) {
        now = gp->renderTime;
    } else {
        now = gp->renderFieldTime;
    }
    if (isFirstCall) {
        event->userdata[0] = ((u64)now >> 32) & 0xFFFFFFFF;
        event->userdata[1] = (u64)now & 0xFFFFFFFF;
    }
    elapsed = ((s32)now - event->userdata[1]) / (u64)(OS_TIMER_CLOCK / 1000);
    if (elapsed < total) {
        npc->rotation.z = intplGetValue(11, elapsed, total, 0.0f, 360.0f);
        return EVT_RETURN_BLOCK;
    }
    npc->rotation.z = 0.0f;
    return EVT_RETURN_DONE;
}
