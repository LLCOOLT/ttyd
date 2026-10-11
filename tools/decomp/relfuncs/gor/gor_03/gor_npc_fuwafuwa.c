// include: evt/evt_npc.h
// include: mario/mariost.h
// include: system.h
// include: dolphin/os.h
// proto: USER_FUNC(gor_npc_fuwafuwa);
USER_FUNC(gor_npc_fuwafuwa) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    NpcEntry* npc = evtNpcNameToPtr(event, name);
    f32 speed = evtGetFloat(event, args[1]);
    s32 duration = evtGetValue(event, args[2]);
    f32 table[40] = {0.0f, 0.5f, 1.0f, 1.4f, 1.8f, 2.0f, 2.3f, 2.5f, 2.6f, 2.7f, 2.7f, 2.7f, 2.6f, 2.5f, 2.3f, 2.0f, 1.8f, 1.4f, 1.0f, 0.5f,
                     -0.0f, -0.5f, -1.0f, -1.4f, -1.8f, -2.0f, -2.3f, -2.5f, -2.6f, -2.7f, -2.7f, -2.7f, -2.6f, -2.5f, -2.3f, -2.0f, -1.8f, -1.4f, -1.0f, -0.5f};
    Vec* base = (Vec*)&event->userdataf[1];
    s32 elapsed;
    s32 frame;
    f32 y;

    if (isFirstCall) {
        event->savedTime = gp->renderTime;
        base->x = npc->position.x;
        base->y = npc->position.y;
        base->z = npc->position.z;
    }
    elapsed = OSTicksToMilliseconds((u32)gp->renderTime - (u32)event->savedTime);
    frame = (0.5f + sysMsec2FrameFloat(elapsed)) * speed;
    y = base->y;
    y += table[(u32)frame % 40];
    npc->position.y = npc->prevPosition.y = y;
    if (duration == 0) {
        return EVT_RETURN_BLOCK;
    }
    if (elapsed < duration) {
        return EVT_RETURN_BLOCK;
    }
    npc->position.y = npc->prevPosition.y = base->y;
    return EVT_RETURN_YIELD;
}
