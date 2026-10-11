// include: evt/evt_npc.h
// include: mario/mariost.h
// include: system.h
// include: dolphin/os.h
// proto: USER_FUNC(muj_npc_fuwafuwa);
USER_FUNC(muj_npc_fuwafuwa) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    NpcEntry* npc = evtNpcNameToPtr(event, name);
    s32 axis = evtGetValue(event, args[1]);
    s32 duration = evtGetValue(event, args[2]);
    f32 table[32] = {0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.2f, 2.5f, 2.7f, 2.7f, 2.7f, 2.5f, 2.2f, 2.0f, 1.5f, 1.0f, 0.5f,
                     -0.0f, -0.5f, -1.0f, -1.5f, -2.0f, -2.2f, -2.5f, -2.7f, -2.7f, -2.7f, -2.5f, -2.2f, -2.0f, -1.5f, -1.0f, -0.5f};
    Vec* base = (Vec*)&event->userdataf[1];
    s32 elapsed;
    s32 frame;
    f32 x;
    f32 y;
    f32 z;

    if (isFirstCall) {
        event->savedTime = gp->renderTime;
        base->x = npc->position.x;
        base->y = npc->position.y;
        base->z = npc->position.z;
    }
    elapsed = OSTicksToMilliseconds((u32)gp->renderTime - (u32)event->savedTime);
    frame = sysMsec2FrameFloat(elapsed) + 0.5f;
    x = base->x;
    y = base->y;
    z = base->z;
    switch (axis) {
        case 0:
            y += table[frame & 31];
            break;
    }
    npc->prevPosition = (Vec){x, y, z};
    npc->position = npc->prevPosition;
    if (elapsed < duration) {
        return EVT_RETURN_BLOCK;
    }
    npc->prevPosition = (Vec){base->x, base->y, base->z};
    npc->position = npc->prevPosition;
    return EVT_RETURN_YIELD;
}
