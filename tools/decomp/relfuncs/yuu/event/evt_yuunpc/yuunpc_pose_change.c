// include: driver/npcdrv.h
// include: driver/extdrv.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct YuuNpcPose { char name[16]; char anim[8]; u16 field_0x18; f32 frames; f32 jump; s32 start; s32 count; u16 flags; f32 field_0x30; } YuuNpcPose;
// decl: typedef struct YuuNpc { s16 id; u16 flags; s16 state; f32 field_0x8; Vec goal; Vec dest; Vec pos; u8 field_0x30[0xC]; f32 radius; f32 vy; u8 field_0x44[0x10]; s16 poseId; u8 field_0x56[0xA]; NpcEntry* npc; f32 animSpeed; u64 time; } YuuNpc;
// decl: typedef struct YuuNpcWork { u16 flags; s32 numNpc; u8 field_0x8[0xC]; YuuNpc* npcs; s32 basePoseNum; s32 numPoses; s32 chusanPose; s16 hit[6][72]; s16 hitY[72]; YuuNpcPose pose[32]; } YuuNpcWork;
// decl: static YuuNpcWork* yuunpc_wp;
// include: dolphin/os.h
// include: mario/mariost.h
// include: driver/animdrv.h
// proto: void yuunpc_pose_change(YuuNpc* npc, s16 id, f32 speed, f32 frame);
void yuunpc_pose_change(YuuNpc* npc, s16 id, f32 speed, f32 frame) {
    YuuNpcPose* cur = &yuunpc_wp->pose[npc->poseId];
    YuuNpcPose* pose = &yuunpc_wp->pose[id];

    if (speed <= 0.0f) {
        npc->flags |= 4;
        npc->poseId = id;
        npc->animSpeed = 1.0f;
        npc->time = OSMillisecondsToTicks(1000.0f * (frame * (pose->frames * npc->animSpeed)) / 60.0f);
    } else {
        npc->flags &= ~4;
        if (npc->poseId == id) {
            frame = npc->animSpeed;
            if (frame != speed) {
                if (npc->flags & 4) {
                    frame = 60.0f * OSTicksToMilliseconds(npc->time) / 1000.0f / (pose->frames * frame);
                } else {
                    frame = 60.0f * OSTicksToMilliseconds(gp->renderTime - npc->time) / 1000.0f / (cur->frames * frame);
                }
            } else {
                return;
            }
        } else {
            npc->poseId = id;
        }
        npc->animSpeed = speed;
        npc->time = gp->renderTime - OSMillisecondsToTicks(1000.0f * (frame * (pose->frames * npc->animSpeed)) / 60.0f);
    }
    switch (npc->flags & 0x300) {
        case 0:
            break;
        case 0x100:
        case 0x200:
        case 0x300:
            animPoseSetAnim(npc->npc->poseId, pose->anim, TRUE);
            animPoseMain(npc->npc->poseId);
            break;
    }
}
