// include: tou2.h
// include: dolphin/types.h
// include: dolphin/mtx.h
// include: dolphin/gx.h
// include: driver/swdrv.h
// include: driver/npcdrv.h
// include: driver/animdrv.h
// include: driver/camdrv.h
// include: driver/effdrv.h
// include: driver/dispdrv.h
// include: driver/windowdrv.h
// include: driver/icondrv.h
// include: driver/msgdrv.h
// include: manager/fontmgr.h
// include: manager/evtmgr_cmd.h
// include: evt/evt_cmd.h
// include: battle/battle_monosiri.h
// include: data/mapdata.h
// include: mario/mario_pouch.h
// include: pmario_sound.h
// include: system.h
// include: memory.h
// include: string.h
// include: stdio.h
// note: tou2.c is hand-maintained (typed data/structs are defined there); this snippet mirrors it
// proto: USER_FUNC(tou_champion_belt_28_text_2A10);
USER_FUNC(tou_champion_belt_28_text_2A10) {
    NpcEntry* npc;
    EffectEntry* eff;
    AnimationPose* pose;
    Vec* positions;
    StarStoneWork** work;
    s32 group;
    f32 angle;

    npc = npcNameToPtr((const char*)evtGetValue(event, event->args[0]));
    if (isFirstCall) {
        eff = effStarStoneEntry(9, 0.0f, 0.0f, 0.0f, 0.6f);
        animPoseWorldPositionEvalOn(npc->poseId);
        event->userdatap[0] = eff;
        champion_belt_onoff = 0;
    }
    pose = animPoseGetAnimPosePtr(npc->poseId);
    positions = *pose->worldPositions;
    group = animPoseGetGroupIdx(npc->poseId, "locator8");
    angle = reviseAngle(camGetRy() - pose->rotationY);
    eff = event->userdatap[0];
    work = (StarStoneWork**)&eff->userdata;
    (*work)->pos.x = positions[group].x;
    (*work)->pos.y = positions[group].y;
    (*work)->pos.z = positions[group].z;
    if ((angle > 90.0f && angle <= 270.0f) || (angle < -90.0f && angle >= -270.0f)) {
        (*work)->rot = 8.0f - (angle + camGetPtr(CAMERA_3D)->viewYaw);
    } else {
        (*work)->rot = -(angle + camGetPtr(CAMERA_3D)->viewYaw) - 8.0f;
    }
    if (npc->position.y <= -1000.0f) {
        (*work)->pos.x = 0.0f;
        (*work)->pos.y = -1000.0f;
        (*work)->pos.z = 0.0f;
    }
    if (champion_belt_onoff) {
        (*work)->pos.x = 0.0f;
        (*work)->pos.y = -1000.0f;
        (*work)->pos.z = 0.0f;
    }
    return EVT_RETURN_BLOCK;
}
