// include: driver/npcdrv.h
// include: driver/extdrv.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct YuuNpcPose { char name[16]; char anim[8]; u16 field_0x18; f32 frames; f32 jump; s32 start; s32 count; u16 flags; f32 field_0x30; } YuuNpcPose;
// decl: typedef struct YuuNpc { s16 id; u16 flags; s16 state; f32 field_0x8; Vec goal; Vec dest; Vec pos; u8 field_0x30[0xC]; f32 radius; f32 vy; u8 field_0x44[0x10]; s16 poseId; u8 field_0x56[0xA]; NpcEntry* npc; f32 animSpeed; u64 time; } YuuNpc;
// decl: typedef struct YuuNpcWork { u16 flags; s32 numNpc; u8 field_0x8[0xC]; YuuNpc* npcs; s32 basePoseNum; s32 numPoses; s32 chusanPose; s16 hit[6][72]; s16 hitY[72]; YuuNpcPose pose[32]; } YuuNpcWork;
// decl: static YuuNpcWork* yuunpc_wp;
// include: stdlib.h
// decl: s32 yuunpc_pose_check(const char* name, const char* anim);
// decl: void yuunpc_pose_change(YuuNpc* npc, s16 id, f32 speed, f32 frame);
// proto: void yuunpc_pose_change2(YuuNpc* npc, const char* name, const char* anim, f32 speed);
void yuunpc_pose_change2(YuuNpc* npc, const char* name, const char* anim, f32 speed) {
    f32 frame = rand() / 32767.0f;

    yuunpc_pose_change(npc, yuunpc_pose_check(name, anim), speed, frame);
}
