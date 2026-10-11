// include: driver/npcdrv.h
// decl: NpcEntry* evtNpcNameToPtr(EventEntry* event, const char* name);
// include: mario/mariost.h
// include: dolphin/os.h
// include: system.h
// proto: USER_FUNC(urouro_fuwafuwa_func);
USER_FUNC(urouro_fuwafuwa_func) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 sx = evtGetValue(event, args[1]);
    f32 sy = evtGetValue(event, args[2]);
    f32 sz = evtGetValue(event, args[3]);
    f32 ex = evtGetValue(event, args[4]);
    f32 ey = evtGetValue(event, args[5]);
    f32 ez = evtGetValue(event, args[6]);
    s32 noDir = evtGetValue(event, args[7]);
    s32 duration = evtGetValue(event, args[8]);
    s32 mode = evtGetValue(event, args[9]);
    NpcEntry* npc = evtNpcNameToPtr(event, name);
    f32 tbl[32] = {
        0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.2f, 2.5f, 2.7f, 2.7f, 2.7f, 2.5f, 2.2f, 2.0f, 1.5f, 1.0f, 0.5f,
        -0.0f, -0.5f, -1.0f, -1.5f, -2.0f, -2.2f, -2.5f, -2.7f, -2.7f, -2.7f, -2.5f, -2.2f, -2.0f, -1.5f, -1.0f, -0.5f,
    };
    s32 t;

    if (isFirstCall) {
        event->savedTime = gp->renderTime;
    }
    t = OSTicksToMilliseconds((u32)gp->renderTime - (u32)event->savedTime);
    if (t < duration) {
        sx = intplGetValue(mode, t, duration, sx, ex);
        sy = intplGetValue(mode, t, duration, sy, ey);
        sz = intplGetValue(mode, t, duration, sz, ez);
        if (!noDir) {
            if (npc->position.x > sx) {
                npc->direction = 270.0f;
            } else {
                npc->direction = 90.0f;
            }
        }
        {
            Vec pos = {0.0f, 0.0f, 0.0f};
            pos.x = sx;
            pos.y = sy + tbl[sysMsec2Frame(t) & 31];
            pos.z = sz;
            npc->prevPosition = pos;
            npc->position = npc->prevPosition;
        }
        return EVT_RETURN_BLOCK;
    }
    if (!noDir) {
        if (npc->position.x > ex) {
            npc->direction = 270.0f;
        } else {
            npc->direction = 90.0f;
        }
    }
    {
        Vec pos = {0.0f, 0.0f, 0.0f};
        pos.x = ex;
        pos.y = ey;
        pos.z = ez;
        npc->prevPosition = pos;
        npc->position = npc->prevPosition;
    }
    return EVT_RETURN_DONE;
}
