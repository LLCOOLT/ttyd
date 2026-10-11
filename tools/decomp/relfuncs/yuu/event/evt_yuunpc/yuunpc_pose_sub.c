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
// decl: f32 yuusintbl[450];
// decl: s32 chusan_mov_tbl[28];
// decl: s32 chusan_act_tbl[8];
// proto: f32 yuunpc_pose_sub(ExtPose* ext, YuuNpc* npc);
f32 yuunpc_pose_sub(ExtPose* ext, YuuNpc* npc) {
    YuuNpcPose* pose = &yuunpc_wp->pose[npc->poseId];
    f32 t;

    if (!(ext->flags & 2)) {
        f32 a = 450.0f - ext->rot;
        f32 s, c;
        if (a >= 360.0f) {
            a -= 360.0f;
        }
        s = yuusintbl[(s32)a];
        c = yuusintbl[(s32)a + 90];
        ext->mtx[0][0] = c;
        ext->mtx[2][2] = c;
        ext->mtx[0][2] = s;
        ext->mtx[2][0] = -s;
    }
    if (npc->flags & 4) {
        t = 60.0f * OSTicksToMilliseconds(npc->time) / 1000.0f / (pose->frames * npc->animSpeed);
    } else {
        OSTime now = gp->renderTime;
        t = (0.5f + 60.0f * OSTicksToMilliseconds(now - npc->time) / 1000.0f) / (pose->frames * npc->animSpeed);
        if (t >= 1.0f) {
            npc->time = now;
            t = 0.0f;
        }
    }
    switch (npc->flags & 0x300) {
        case 0x100:
        case 0x200:
        case 0x300: {
            f32 rot;
            animPoseSetLocalTime(npc->npc->poseId, (s32)(pose->frames * t));
            rot = 3600.0f + (90.0f - ext->rot);
            npc->npc->rotation.y = rot - (s32)(rot / 360.0f) * 360;
            npc->npc->position = npc->pos;
            break;
        }
        case 0:
            if (npc->poseId != yuunpc_wp->chusanPose) {
                ext->frame = pose->start + (s32)(pose->count * t);
            } else {
                s32 k = 224.0f * t;
                ext->frame = pose->start + (chusan_mov_tbl[k >> 3] ? chusan_act_tbl[k & 7] : 0);
            }
            break;
    }
    return t;
}
