// include: evt/evt_npc.h
// include: party.h
// include: mario/mariost.h
// include: manager/evtmgr_cmd.h
// include: dolphin/os.h
// proto: USER_FUNC(tik_npc_buruburu);
USER_FUNC(tik_npc_buruburu) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    NpcEntry* npc = evtNpcNameToPtr(event, name);
    s32 axis = evtGetValue(event, args[1]);
    f32 amplitude = evtGetFloat(event, args[2]);
    s32 period = evtGetValue(event, args[3]);
    s32 duration = evtGetValue(event, args[4]);
    PartyEntry* party = partyGetPtr(1);
    Vec* base = (Vec*)&event->userdataf[1];
    s32 elapsed;
    f32 offset;
    f32 delta;

    if (isFirstCall) {
        event->savedTime = gp->renderTime;
        event->userdataf[0] = 0.0f;
        if (npc == (NpcEntry*)-2) {
            base->x = party->position.x;
            base->y = party->position.y;
            base->z = party->position.z;
        } else {
            base->x = npc->position.x;
            base->y = npc->position.y;
            base->z = npc->position.z;
        }
    }
    elapsed = OSTicksToMilliseconds((u32)gp->renderTime - (u32)event->savedTime);
    if (elapsed % (period * 2) >= period) {
        offset = amplitude;
    } else {
        offset = -amplitude;
    }
    delta = offset - event->userdataf[0];
    switch (axis) {
        case 0:
            if (npc == (NpcEntry*)-2) {
                party->position.x += delta;
            } else {
                npc->position.x += delta;
                npc->prevPosition.x = npc->position.x;
            }
            break;
        case 1:
            if (npc == (NpcEntry*)-2) {
                party->position.y += delta;
            } else {
                npc->position.y += delta;
                npc->prevPosition.y = npc->position.y;
            }
            break;
        case 2:
            if (npc == (NpcEntry*)-2) {
                party->position.z += delta;
            } else {
                npc->position.z += delta;
                npc->prevPosition.z = npc->position.z;
            }
            break;
    }
    event->userdataf[0] = offset;
    if (duration == 0) {
        return EVT_RETURN_BLOCK;
    }
    if (elapsed < duration) {
        return EVT_RETURN_BLOCK;
    }
    if (npc == (NpcEntry*)-2) {
        party->position = (Vec){base->x, base->y, base->z};
    } else {
        npc->prevPosition = (Vec){base->x, base->y, base->z};
        npc->position = npc->prevPosition;
    }
    return EVT_RETURN_YIELD;
}
