// include: manager/evtmgr_cmd.h
// include: driver/npcdrv.h
// include: driver/animdrv.h
// include: driver/effdrv.h
// include: driver/camdrv.h
// include: system.h
// decl: typedef struct StarStoneWork { u8 field_0x0[8]; Vec pos; u8 field_0x14[8]; f32 rot; } StarStoneWork;
// decl: EffectEntry* effStarStoneEntry(s32 type, f32 x, f32 y, f32 z, f32 scale);
// decl: static s32 champion_belt_onoff;
// proto: USER_FUNC(tou_champion_belt_27_text_34);
USER_FUNC(tou_champion_belt_27_text_34) {
    NpcEntry* npc = npcNameToPtr((const char*)evtGetValue(event, event->args[0]));
    EffectEntry* eff;
    AnimationPose* pose;
    Vec* positions;
    s32 idx;
    f32 angle;

    if (isFirstCall) {
        eff = effStarStoneEntry(9, 0.0f, 0.0f, 0.0f, 0.6f);
        animPoseWorldPositionEvalOn(npc->poseId);
        event->userdatap[0] = eff;
        champion_belt_onoff = 0;
    }
    pose = animPoseGetAnimPosePtr(npc->poseId);
    positions = *pose->worldPositions;
    idx = animPoseGetGroupIdx(npc->poseId, "locator8");
    angle = reviseAngle(camGetRy() - pose->rotationY);
    eff = event->userdatap[0];
    ((StarStoneWork*)eff->userdata)->pos.x = positions[idx].x;
    ((StarStoneWork*)eff->userdata)->pos.y = positions[idx].y;
    ((StarStoneWork*)eff->userdata)->pos.z = positions[idx].z;
    if ((angle > 90.0f && angle <= 270.0f) || (angle < -90.0f && angle >= -270.0f)) {
        ((StarStoneWork*)eff->userdata)->rot = 8.0f - (angle + camGetPtr(CAMERA_3D)->viewYaw);
    } else {
        ((StarStoneWork*)eff->userdata)->rot = -(angle + camGetPtr(CAMERA_3D)->viewYaw) - 8.0f;
    }
    if (npc->position.y <= -1000.0f) {
        ((StarStoneWork*)eff->userdata)->pos.x = 0.0f;
        ((StarStoneWork*)eff->userdata)->pos.y = -1000.0f;
        ((StarStoneWork*)eff->userdata)->pos.z = 0.0f;
    }
    if (champion_belt_onoff) {
        ((StarStoneWork*)eff->userdata)->pos.x = 0.0f;
        ((StarStoneWork*)eff->userdata)->pos.y = -1000.0f;
        ((StarStoneWork*)eff->userdata)->pos.z = 0.0f;
    }
    return EVT_RETURN_BLOCK;
}
