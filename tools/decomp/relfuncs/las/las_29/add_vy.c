// include: manager/evtmgr_cmd.h
// include: driver/npcdrv.h
// proto: USER_FUNC(add_vy);
USER_FUNC(add_vy) {
    s32* args = event->args;
    s32 dir = evtGetValue(event, args[0]);
    s32 n = evtGetValue(event, args[1]);
    f32 base;
    f32 step;
    NpcEntry* npc;

    base = dir ? -0.3f : 0.3f;
    step = dir ? 0.01f : -0.01f;
    npc = npcNameToPtr("\203u\203\211\203b\203N\203s\201[\203`");
    base += step * n;
    npc->moveOffset.y += base;
    return EVT_RETURN_DONE;
}
