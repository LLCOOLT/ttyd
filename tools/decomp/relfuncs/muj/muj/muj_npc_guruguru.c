// include: evt/evt_npc.h
// include: mario/mariost.h
// include: system.h
// include: pmario_sound.h
// include: manager/evtmgr_cmd.h
// include: dolphin/os.h
// decl: s32 psndSFXOnEx_3D(const char* name, Vec* position, s32 vol, s32 pan, s32 pitch, s32 flags);
// proto: USER_FUNC(muj_npc_guruguru);
USER_FUNC(muj_npc_guruguru) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    NpcEntry* npc = evtNpcNameToPtr(event, name);
    f32 cx = evtGetFloat(event, args[1]);
    f32 cz = evtGetFloat(event, args[2]);
    s32 dir = evtGetValue(event, args[3]);
    f32 speed = evtGetFloat(event, args[4]);
    s32 duration = evtGetValue(event, args[5]);
    s32 elapsed;
    f32 x;
    f32 z;
    f32 y;
    f32 angle;

    if (isFirstCall) {
        event->savedTime = gp->renderTime;
        event->userdataf[1] = angleABf(cx, cz, npc->position.x, npc->position.z);
        event->userdataf[2] = distABf(cx, cz, npc->position.x, npc->position.z);
    }
    elapsed = OSTicksToMilliseconds((u32)gp->renderTime - (u32)event->savedTime);
    angle = speed * (s32)(0.5f + sysMsec2FrameFloat(elapsed)) + event->userdataf[1];
    x = cx;
    y = npc->position.y;
    z = cz;
    movePos(&x, &z, event->userdataf[2], angle);
    if (dir == 0) {
        if (npc->position.x > x) {
            npc->direction = 270.0f;
        } else {
            npc->direction = 90.0f;
        }
    }
    npc->prevPosition = (Vec){x, y, z};
    npc->position = npc->prevPosition;
    if (npc->footstepAccum > npc->footstepStride / npc->moveSpeed) {
        if (npc->footstepToggle != 0) {
            if (npc->footstepSfxA != NULL) {
                psndSFXOnEx_3D(npc->footstepSfxA, &npc->position, 255, 255, 0, 8);
            }
        } else if (npc->footstepSfxB != NULL) {
            psndSFXOnEx_3D(npc->footstepSfxB, &npc->position, 255, 255, 0, 8);
        }
        npc->footstepAccum = 0.0f;
        npc->footstepToggle = (s8)(1 - npc->footstepToggle);
    }
    if (npc->footstepSfxB != NULL || npc->footstepToggle != 0) {
        npc->footstepAccum = 1000.0f * npc->moveDt + npc->footstepAccum;
    }
    if (elapsed < duration) {
        return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_YIELD;
}
