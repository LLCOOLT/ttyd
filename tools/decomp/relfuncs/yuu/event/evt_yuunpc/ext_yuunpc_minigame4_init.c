// include: driver/npcdrv.h
// include: driver/extdrv.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct YuuNpcPose { char name[16]; char anim[8]; u16 field_0x18; f32 frames; f32 jump; s32 start; s32 count; u16 flags; f32 field_0x30; } YuuNpcPose;
// decl: typedef struct YuuNpc { s16 id; u16 flags; s16 state; f32 field_0x8; Vec goal; Vec dest; Vec pos; u8 field_0x30[0xC]; f32 radius; f32 vy; u8 field_0x44[0x10]; s16 poseId; u8 field_0x56[0xA]; NpcEntry* npc; f32 animSpeed; u64 time; } YuuNpc;
// decl: typedef struct YuuNpcWork { u16 flags; s32 numNpc; u8 field_0x8[0xC]; YuuNpc* npcs; s32 basePoseNum; s32 numPoses; s32 chusanPose; s16 hit[6][72]; s16 hitY[72]; YuuNpcPose pose[32]; } YuuNpcWork;
// decl: static YuuNpcWork* yuunpc_wp;
// include: memory.h
// include: string.h
// decl: void ext_yuunpc_minigame4_init_sub(void);
// decl: s32 extGetPoseNum(void);
// proto: void ext_yuunpc_minigame4_init(void);
void ext_yuunpc_minigame4_init(void) {
    yuunpc_wp = _mapAlloc(sizeof(YuuNpcWork));
    memset(yuunpc_wp, 0, sizeof(YuuNpcWork));
    yuunpc_wp->numNpc = extGetPoseNum();
    yuunpc_wp->npcs = _mapAlloc(yuunpc_wp->numNpc * sizeof(YuuNpc));
    memset(yuunpc_wp->npcs, 0, yuunpc_wp->numNpc * sizeof(YuuNpc));
    ext_yuunpc_minigame4_init_sub();
}
