// include: manager/evtmgr_cmd.h
// include: mario/mariost.h
// include: dolphin/os.h
// include: evt/evt_npc.h
// include: driver/npcdrv.h
// proto: USER_FUNC(mri_npc_buruburu);
USER_FUNC(mri_npc_buruburu) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    NpcEntry* npc = evtNpcNameToPtr(event, name);
    s32 axis = evtGetValue(event, args[1]);
    f32 amp = evtGetFloat(event, args[2]);
    s32 period = evtGetValue(event, args[3]);
    s32 duration = evtGetValue(event, args[4]);
    f32* work = event->userdataf;
    s32 elapsed;
    f32 v;
    f32 delta;

    if (isFirstCall) {
        event->savedTime = gp->renderTime;
        work[0] = 0.0f;
        work[1] = npc->position.x;
        work[2] = npc->position.y;
        work[3] = npc->position.z;
    }
    elapsed = OSTicksToMilliseconds((u32)gp->renderTime - (u32)event->savedTime);
    if (elapsed % (period * 2) >= period) {
        v = amp;
    } else {
        v = -amp;
    }
    delta = v - work[0];
    switch (axis) {
        case 0:
            npc->position.x += delta;
            npc->prevPosition.x = npc->position.x;
            break;
        case 1:
            npc->position.y += delta;
            npc->prevPosition.y = npc->position.y;
            break;
        case 2:
            npc->position.z += delta;
            npc->prevPosition.z = npc->position.z;
            break;
    }
    work[0] = v;
    if (duration == 0) {
        return EVT_RETURN_BLOCK;
    }
    if (elapsed < duration) {
        return EVT_RETURN_BLOCK;
    }
    {
        Vec pos = {0.0f, 0.0f, 0.0f};
        pos.x = work[1];
        pos.y = work[2];
        pos.z = work[3];
        npc->prevPosition = pos;
        npc->position = npc->prevPosition;
    }
    return EVT_RETURN_YIELD;
}
