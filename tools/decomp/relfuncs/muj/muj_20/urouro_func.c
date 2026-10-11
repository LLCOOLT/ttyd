// include: driver/npcdrv.h
// decl: NpcEntry* evtNpcNameToPtr(EventEntry* event, const char* name);
// include: mario/mariost.h
// include: dolphin/os.h
// include: system.h
// proto: USER_FUNC(urouro_func);
USER_FUNC(urouro_func) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 sx = evtGetValue(event, args[1]);
    f32 sz = evtGetValue(event, args[2]);
    f32 ex = evtGetValue(event, args[3]);
    f32 ez = evtGetValue(event, args[4]);
    s32 noDir = evtGetValue(event, args[5]);
    s32 duration = evtGetValue(event, args[6]);
    s32 mode = evtGetValue(event, args[7]);
    NpcEntry* npc = evtNpcNameToPtr(event, name);
    s32 t;

    if (isFirstCall) {
        event->savedTime = gp->renderTime;
    }
    t = OSTicksToMilliseconds((u32)gp->renderTime - (u32)event->savedTime);
    if (t < duration) {
        sx = intplGetValue(mode, t, duration, sx, ex);
        sz = intplGetValue(mode, t, duration, sz, ez);
        if (!noDir) {
            if (npc->position.x > sx) {
                npc->direction = 270.0f;
            } else {
                npc->direction = 90.0f;
            }
        }
        npc->position.x = npc->prevPosition.x = sx;
        npc->position.z = npc->prevPosition.z = sz;
        return EVT_RETURN_BLOCK;
    }
    if (!noDir) {
        if (npc->position.x > ex) {
            npc->direction = 270.0f;
        } else {
            npc->direction = 90.0f;
        }
    }
    npc->position.x = npc->prevPosition.x = ex;
    npc->position.z = npc->prevPosition.z = ez;
    return EVT_RETURN_DONE;
}
