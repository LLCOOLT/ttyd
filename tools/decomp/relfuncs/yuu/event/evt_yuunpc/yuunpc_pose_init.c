// include: driver/npcdrv.h
// include: driver/extdrv.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct YuuNpcPose { char name[16]; char anim[8]; u16 field_0x18; f32 frames; f32 jump; s32 start; s32 count; u16 flags; f32 field_0x30; } YuuNpcPose;
// decl: typedef struct YuuNpc { s16 id; u16 flags; s16 state; f32 field_0x8; Vec goal; Vec dest; Vec pos; u8 field_0x30[0xC]; f32 radius; f32 vy; u8 field_0x44[0x10]; s16 poseId; u8 field_0x56[0xA]; NpcEntry* npc; f32 animSpeed; u64 time; } YuuNpc;
// decl: typedef struct YuuNpcWork { u16 flags; s32 numNpc; u8 field_0x8[0xC]; YuuNpc* npcs; s32 basePoseNum; s32 numPoses; s32 chusanPose; s16 hit[6][72]; s16 hitY[72]; YuuNpcPose pose[32]; } YuuNpcWork;
// decl: static YuuNpcWork* yuunpc_wp;
// include: string.h
// decl: typedef struct YuuNpcData { const char* name; const char* anim; f32 frames; } YuuNpcData;
// proto: void yuunpc_pose_init(YuuNpcData* data);
void yuunpc_pose_init(YuuNpcData* data) {
    char name[32];
    char anim[32];
    s32 n = 0;
    s32 start;

    strcpy(name, "");
    strcpy(anim, "");
    yuunpc_wp->numPoses = -1;
    do {
        if (strcmp(data->name, name) != 0) {
            strcpy(name, data->name);
            strcpy(anim, "");
        }
        if (strcmp(data->anim, anim) != 0) {
            strcpy(anim, data->anim);
            start = n;
            yuunpc_wp->numPoses++;
        }
        strcpy(yuunpc_wp->pose[yuunpc_wp->numPoses].name, name);
        strcpy(yuunpc_wp->pose[yuunpc_wp->numPoses].anim, anim);
        yuunpc_wp->pose[yuunpc_wp->numPoses].start = start;
        yuunpc_wp->pose[yuunpc_wp->numPoses].count = n - start + 1;
        n++;
        yuunpc_wp->pose[yuunpc_wp->numPoses].frames += 1.0f;
        yuunpc_wp->pose[yuunpc_wp->numPoses].field_0x18 = 1;
        yuunpc_wp->pose[yuunpc_wp->numPoses].jump = 0.0f;
        yuunpc_wp->pose[yuunpc_wp->numPoses].field_0x30 = 2.0f;
        data++;
    } while (data->name != NULL);
    data++;
    yuunpc_wp->numPoses++;
    yuunpc_wp->basePoseNum = yuunpc_wp->numPoses;
    while (data->name != NULL) {
        strcpy(yuunpc_wp->pose[yuunpc_wp->numPoses].name, data->name);
        strcpy(yuunpc_wp->pose[yuunpc_wp->numPoses].anim, data->anim);
        yuunpc_wp->pose[yuunpc_wp->numPoses].start = start;
        yuunpc_wp->pose[yuunpc_wp->numPoses].count = 1;
        yuunpc_wp->pose[yuunpc_wp->numPoses].frames = data->frames;
        data++;
        yuunpc_wp->pose[yuunpc_wp->numPoses].field_0x18 = 1;
        yuunpc_wp->pose[yuunpc_wp->numPoses].jump = 0.0f;
        yuunpc_wp->pose[yuunpc_wp->numPoses].field_0x30 = 1.0f;
        yuunpc_wp->pose[yuunpc_wp->numPoses].flags |= 1;
        yuunpc_wp->numPoses++;
    }
    for (n = 0; n < yuunpc_wp->basePoseNum; n++) {
        if (strcmp(yuunpc_wp->pose[n].name, "c_tyusan") == 0 && strcmp(yuunpc_wp->pose[n].anim, "CHU_S_1") == 0) {
            yuunpc_wp->chusanPose = n;
            yuunpc_wp->pose[n].frames = 224.0f;
        }
    }
}
